#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <ostream>
#include <iostream>
#include <utility>

#include "../general/types.h"
#include "../util.h"
#include "general/Iterators.h"

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
    /* using  forward_iterator  = ArrayForwardIterator<CLinkedList<Traits>>;
    friend forward_iterator;
    friend GeneralIterator< CLinkedList<Traits> >; */
    using  NodeLinkedList = NodeLinkedList<Traits>;

    NodeLinkedList *m_pRoot;
    NodeLinkedList *m_pLast;
    size_t m_nElements;
    
    public:
        //Constructor por defecto
        CLinkedList(): m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0){}

        //Constructor Copia
        CLinkedList(CLinkedList<Traits> &another):
            m_pRoot(another.m_pRoot),
            m_pLast(another.m_pLast),
            m_nElements(another.m_pElements)
        {}

        //Constructor de movimiento
        CLinkedList(CLinkedList<Traits> &&another) noexcept:
            m_pRoot(exchange(another.mm_pRoot, nullptr)),
            m_pLast(exchange(another.m_pLast, nullptr)),
            m_nElements(exchange(another.m_nElements, 0))
        {}

        //Destructor seguro
        virtual ~CLinkedList(){};

        void push_back(value_type &val, ref_type ref);
        void Insert(const value_type &val, ref_type ref);
        size_t getSize(){ return m_nElements;  }

    private:
        void InternalInsert(NodeLinkedList *&rParent, const value_type &val, ref_type ref);

        friend ostream &operator<<(ostream &os, CLinkedList<Traits> &container){

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
};

template <typename Traits>
void CLinkedList<Traits>::push_back(value_type &val, ref_type ref){
    NodeLinkedList *pNewNode = new NodeLinkedList(val, ref);
    if( !m_pRoot ) m_pRoot = pNewNode;
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
    InternalInsert(m_pRoot, val, ref);
}

#endif // __LINKEDLIST_H__
