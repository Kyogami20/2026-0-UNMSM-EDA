#ifndef __DOUBLELINKEDLIST_H__
#define __DOUBLELINKEDLIST_H__

#include <ostream>
#include <iostream>
#include <utility>
#include <mutex>

#include "../general/types.h"
#include "../Others/util.h"
#include "../Iterators/Iterators.h"

using namespace std;

template <typename Traits>
class NodeDoubleLinkedList{
    using value_type  = typename Traits::value_type;

    private:
        value_type m_data;
        ref_type   m_ref;
        NodeDoubleLinkedList *m_pNext = nullptr;
        NodeDoubleLinkedList *m_pPrev = nullptr;

    public:
        NodeDoubleLinkedList() {}
        NodeDoubleLinkedList(value_type valor, ref_type ref = -1):
            m_data(valor), m_ref(ref) 
        {}

        value_type  GetValue   () const { return m_data; }
        value_type &GetValueRef() { return m_data; }

        ref_type    GetRef     () const { return m_ref;   }
        ref_type   &GetRefRef  () { return m_ref;   }

        NodeDoubleLinkedList   * GetNext     () const { return m_pNext;   }
        NodeDoubleLinkedList   *&GetNextRef  () { return m_pNext;   }

        NodeDoubleLinkedList *getPrev     () const { return m_pPrev; }
        NodeDoubleLinkedList *&getPrevRef () { return m_pPrev; }

        NodeDoubleLinkedList &operator=(const NodeDoubleLinkedList &another){
            m_data = another.GetValue();
            m_ref   = another.GetRef();
            return *this;
        }

        bool operator==(const NodeDoubleLinkedList &another) const
        { return m_data == another.GetValue();   }
        bool operator<(const NodeDoubleLinkedList &another) const
        { return m_data < another.GetValue();   }
};

template <typename Traits>
class CDoubleLinkedList  {
    
    NodeDoubleLinkedList<Traits> *m_pRoot;
    NodeDoubleLinkedList<Traits> *m_pLast;
    size_t m_nElements;
    mutable mutex m_mutex;

    public:
        using  value_type  = typename Traits::value_type;
        using Node = NodeDoubleLinkedList<Traits>;
        using NodeDoubleLinkedList = NodeDoubleLinkedList<Traits>;
        using bidirectional_iterator = DoubleLinkedListBidirectionalIterator<CDoubleLinkedList<Traits>>;

        //Constructor por defecto
        CDoubleLinkedList(): m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0) {}

        //Constructor Copia
        CDoubleLinkedList(const CDoubleLinkedList<Traits> &another):
            m_pRoot(nullptr), m_pLast(nullptr), m_nElements(0) {
            lock_guard<mutex> lock(another.m_mutex);

            NodeDoubleLinkedList *pCurrent = another.m_pRoot;
            while(pCurrent) {
                
            }
        }

        //Move COnstructor
        CDoubleLinkedList(CDoubleLinkedList &&another) noexcept: {
            lock_guard<mutex> lock(another.m_mutex);
            
            m_pRoot = exchange(another.m_pRoot, nullptr);
            m_pLast = exchange(another.m_pLast, nullptr);
            m_nElements = exchange(another.m_nElements, 0);
        }

        //Iterators
        forward_iterator begin()
        { return forward_iterator(this, m_pRoot); }
        forward_iterator end()
        { return forward_iterator(this, nullptr); }

};

#endif // __DOUBLELINKEDLIST_H__