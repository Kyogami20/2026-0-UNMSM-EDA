#ifndef __LINKEDCIRCULARLIST_H__
#define __LINKEDCIRCULARLIST_H__

#include <iostream>

#include "linkedlist.h"

using namespace std;

template <typename Traits>
class CLinkedCircularList : CLinkedList<Traits> {

    using Parent = CLinkedList<Traits>;
    using value_type  = typename Parent::value_type;
    using NodeLinkedList = typename Parent::NodeLinkedList;
    
    public:
        CLinkedCircularList() : Parent() {}

        void push_back(value_type &val, ref_type ref) override;
};

template <typename Traits>
void CLinkedCircularList<Traits>::push_back(value_type &val, ref_type ref){
    typename Parent::lock_guard<Parent::mutex> lock(Parent::m_mutex);

    NodeLinkedList *pNewNode = new NodeLinkedList(val, ref);

    if( !Parent::m_pRoot ){ 
        Parent::m_pRoot = pNewNode;
        pNewNode->GetNextRef() = pNewNode;
    } else { 
        Parent::m_pLast->GetNextRef() = pNewNode; 
        pNewNode->GetNextRef() = Parent::m_pRoot; 
    }
    Parent::m_pLast = pNewNode;
    ++Parent::m_nElements;
}

template <typename Traits>
ostream& operator<<(ostream &os, CLinkedCircularList<Traits> &container){
    typename Parent::lock_guard<Parent::mutex> lock(container.m_mutex);

    os << "CLinkedCircularList: size = " << container.getSize() << endl;
    os << "[";

    typename Parent::NodeLinkedList *pCurrent = container.m_pRoot;
    for (size_t i = 0; i < container.getSize(); ++i){
        os << "(" << pCurrent->GetValue() << ", " << pCurrent->GetRef() << ")";
        pCurrent = pCurrent->GetNext();
        if( i < container.getSize() - 1 ) os << ", ";
    }
    
    os << "]" << endl;
    return os;
}


#endif // __LINKEDCIRCULARLIST_H__