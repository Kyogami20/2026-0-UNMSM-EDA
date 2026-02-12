#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <ostream>
#include <iostream>
#include <utility>
#include <mutex>

#include "../general/types.h"
#include "../Others/util.h"
#include "../Iterators/Iterators.h"

using namespace std;

template <typename T, typename _Func>
struct ListTrait{
    using value_type = T;
    using Func       = _Func;
};

template <typename T>
struct AscendingTrait : 
    public ListTrait<T, std::greater<T> >{
};

template <typename T>
struct DescendingTrait : 
    public ListTrait<T, std::less<T> >{
};

template <typename Traits>
class NodeLinkedList{
    using  value_type  = typename Traits::value_type;

    private:
    value_type m_data;
    ref_type   m_ref;
    NodeLinkedList *m_pNext = nullptr;

    public:
        NodeLinkedList(){}
        NodeLinkedList( value_type _value, ref_type _ref = -1)
            : m_data(_value), m_ref(_ref)
        {}
    
        value_type  GetValue   () const { return m_data; }
        value_type &GetValueRef() { return m_data; }

        ref_type    GetRef     () const { return m_ref;   }
        ref_type   &GetRefRef  () { return m_ref;   }

        NodeLinkedList   * GetNext     () const { return m_pNext;   }
        NodeLinkedList   *&GetNextRef  () { return m_pNext;   }

        NodeLinkedList &operator=(const NodeLinkedList &another){
            m_data = another.GetValue();
            m_ref   = another.GetRef();
            return *this;
        }

        bool operator==(const NodeLinkedList &another) const
        { return m_data == another.GetValue();   }
        bool operator<(const NodeLinkedList &another) const
        { return m_data < another.GetValue();   }
};


template <typename Traits>
class CLinkedList {
    
    using  value_type  = typename Traits::value_type;
    using  forward_iterator  = LinkedListForwardIterator<CLinkedList<Traits>>;
    friend forward_iterator;
    using  NodeLinkedList = NodeLinkedList<Traits>;
    using  Node = NodeLinkedList;
    friend LinkedListIterator<CLinkedList<Traits>>; 
    friend GeneralIterator<CLinkedList<Traits>>; 

    NodeLinkedList *m_pRoot;
    NodeLinkedList *m_pLast;
    size_t m_nElements;
    mutable mutex m_mutex;
    
    public:
        //Constructor por defecto
        CLinkedList(): m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0){}

        //Constructor Copia
        CLinkedList(const CLinkedList<Traits> &another): 
            m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0) {
            lock_guard<mutex> lock(another.m_mutex);
            
            NodeLinkedList *pCurrent = another.m_pRoot;
            while(pCurrent) {
                value_type val = pCurrent->GetValue();
                ref_type ref = pCurrent->GetRef();
                push_back(val, ref);
                pCurrent = pCurrent->GetNext();
            }
        }

        //Constructor de movimiento
        CLinkedList(CLinkedList<Traits> &&another) noexcept: 
            m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0) {
            lock_guard<mutex> lock(another.m_mutex);
            
            m_pRoot = exchange(another.m_pRoot, nullptr);
            m_pLast = exchange(another.m_pLast, nullptr);
            m_nElements = exchange(another.m_nElements, 0);
        }

        //Destructor seguro
        virtual ~CLinkedList() {
            lock_guard<mutex> lock(m_mutex);
            
            NodeLinkedList *pCurrent = m_pRoot;
            while(pCurrent) {
                NodeLinkedList *pNext = pCurrent->GetNext();
                delete pCurrent;
                pCurrent = pNext;
            }
            m_pRoot = nullptr;
            m_pLast = nullptr;
            m_nElements = 0;
        }

        //Iterators
        forward_iterator begin()
        { return forward_iterator(this, m_pRoot); }
        forward_iterator end()
        { return forward_iterator(this, nullptr); }

        void push_back(value_type &val, ref_type ref);
        void Insert(const value_type &val, ref_type ref);
        size_t getSize(){ return m_nElements;  };

        friend ostream &operator<<(ostream &os, CLinkedList<Traits> &container){
            lock_guard<mutex> lock(container.m_mutex);
            os << "CLinkedList: size = " << container.getSize() << endl;
            os << "[";
            
            NodeLinkedList *pCurrent = container.m_pRoot;
            while( pCurrent ){
                os << "(" << pCurrent->GetValue() << ", " << pCurrent->GetRef() << ")";
                pCurrent = pCurrent->GetNext();
                if( pCurrent ) os << ", ";
            }
            
            os << "]" << endl;
            return os;
        }

        friend istream &operator>>(istream &is, CLinkedList<Traits> &container) {
            lock_guard<mutex> lock(container.m_mutex);
            
            value_type val;
            ref_type ref;

            if(is >> val >> ref) { container.push_back(val, ref); }
            
            return is;
        }

        value_type &operator[](Size index);

        template <typename ObjFunc, typename ...Args>
        auto FirstThat(ObjFunc of, Args... args){
            return ::FirstThat(*this, of, args...);
        }

        template <typename ObjFunc, typename ...Args>
        void Foreach(ObjFunc of, Args... args){
            ::Foreach(*this, of, args...);
        }

    private:
        void InternalInsert(NodeLinkedList *&rParent, const value_type &val, ref_type ref);
};

template <typename Traits>
typename Traits::value_type &CLinkedList<Traits>::operator[](Size index){
    lock_guard<mutex> lock(m_mutex);

    if( index >= m_nElements ) throw out_of_range("Fuera del rango de la lista");
    NodeLinkedList *pCurrent = m_pRoot;

    for (Size i = 0; i < index; ++i) {
        pCurrent = pCurrent->GetNext();
    }
    return pCurrent->GetValueRef();
}

template <typename Traits>
void CLinkedList<Traits>::push_back(value_type &val, ref_type ref){
    lock_guard<mutex> lock(m_mutex);
    NodeLinkedList *pNewNode = new NodeLinkedList(val, ref);

    if( !m_pRoot ){ m_pRoot = pNewNode;
    } else { m_pLast->GetNextRef() = pNewNode; }
    m_pLast = pNewNode;
    ++m_nElements;
}

template <typename Traits>
void CLinkedList<Traits>::InternalInsert(NodeLinkedList *&rParent, const value_type &val, ref_type ref){
    if( !rParent || rParent->GetValueRef() > val ){
        NodeLinkedList *pNew = new NodeLinkedList(val, ref);
        pNew->GetNextRef() = rParent;
        rParent = pNew;
        ++m_nElements;
        
        if ( !m_pLast || !pNew->GetNext()) m_pLast = pNew;
        
        return;
    }
    InternalInsert(rParent->GetNextRef(), val, ref);
}

template <typename Traits>
void CLinkedList<Traits>::Insert(const value_type &val, ref_type ref){
    lock_guard<mutex> lock(m_mutex);
    InternalInsert(m_pRoot, val, ref);
}

#endif // __LINKEDLIST_H__
