#ifndef LINKEDCIRCULARLIST_H__
#define LINKEDCIRCULARLIST_H__

#include <iostream>

#include "linkedlist.h"

using namespace std;

template <typename Traits>
class CLinkedCircularList : public CLinkedList<Traits> {

    public:
        using Parent = CLinkedList<Traits>;
        using value_type = typename Traits::value_type;
        using Node = typename Parent::Node;

        //Constructor por defecto
        CLinkedCircularList() : Parent() {}

        //Constructor Copia
        CLinkedCircularList(const CLinkedCircularList<Traits> &another):
            Parent() {
            lock_guard<mutex> lock(another.m_mutex);
            
            Node *pCurrent = another.m_pRoot;
            for (size_t i = 0; i < another.m_nElements; ++i){
                push_back(pCurrent->GetValue(), pCurrent->GetRef());
                pCurrent = pCurrent->GetNext();
            }
        }

        //Constructor de movimiento
        CLinkedCircularList(CLinkedCircularList &&another) noexcept : Parent() {
            lock_guard<mutex> lock(another.m_mutex);

            this->m_pRoot     = exchange(another.m_pRoot, nullptr);
            this->m_pLast     = exchange(another.m_pLast, nullptr);
            this->m_nElements = exchange(another.m_nElements, 0);
        }

        ~CLinkedCircularList() {
            if (this->m_pLast)
                this->m_pLast->GetNextRef() = nullptr;
        }

        void push_back(const value_type &val, ref_type ref) override;

        template <typename T>
        friend ostream& operator<<(ostream &os, CLinkedCircularList<T> &container);
};

template <typename Traits>
void CLinkedCircularList<Traits>::push_back(const value_type &val, ref_type ref){
    lock_guard<mutex> lock(this->m_mutex);

    Node *pNewNode = new Node(val, ref);

    if( !this->m_pRoot ){ 
        this->m_pRoot = pNewNode;
        pNewNode->GetNextRef() = pNewNode;
    } else { 
        this->m_pLast->GetNextRef() = pNewNode; 
        pNewNode->GetNextRef() = this->m_pRoot; 
    }
    this->m_pLast = pNewNode;
    ++this->m_nElements;
}

template <typename Traits>
ostream& operator<<(ostream &os, CLinkedCircularList<Traits> &container){
    lock_guard<mutex> lock(container.m_mutex);

    os << "CLinkedCircularList: size = " << container.getSize() << endl;
    os << "[";

    typename CLinkedList<Traits>::Node *pCurrent = container.m_pRoot;
    for (size_t i = 0; i < container.getSize(); ++i){
        os << "(" << pCurrent->GetValue() << ", " << pCurrent->GetRef() << ")";
        pCurrent = pCurrent->GetNext();
        if( i < container.getSize() - 1 ) os << ", ";
    }
    
    os << "]" << endl;
    return os;
}

#endif // LINKEDCIRCULARLIST_H__