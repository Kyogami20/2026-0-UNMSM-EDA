#ifndef DOUBLYCIRCULARLINKEDLIST_H_
#define DOUBLYCIRCULARLINKEDLIST_H_

#include <iostream>

#include "DoubleLinkedList.h"

using namespace std;

template <typename Traits>
class DoublyCircularLinkedList : public CDoubleLinkedList<Traits> {

    public:
        using Parent = CDoubleLinkedList<Traits>;
        using value_type = Traits;
        using Node = typename Parent::Node;

        void push_back(const value_type &value, ref_type ref) override;

        //Constructor por defecto
        DoublyCircularLinkedList() : Parent() {}

        //Constructor Copia
        DoublyCircularLinkedList(const DoublyCircularLinkedList &another):
            Parent() {
            lock_guard<mutex> lock(another.m_mutex);
            
            Node* pCurrent = another.m_pRoot;
            for (size_t i = 0; i < another.m_nElements; ++i){
                push_back(pCurrent->GetValue(), pCurrent->GetRef());
                pCurrent = pCurrent->GetNext();
            }
        }

        //Constructor de movimiento
        DoublyCircularLinkedList(DoublyCircularLinkedList &&another) noexcept : Parent() {
            lock_guard<mutex> lock(another.m_mutex);

            this->m_pRoot     = exchange(another.m_pRoot, nullptr);
            this->m_pLast     = exchange(another.m_pLast, nullptr);
            this->m_nElements = exchange(another.m_nElements, 0);
        }
};

template <typename Traits>
void DoublyCircularLinkedList<Traits>::push_back(const value_type &value, ref_type ref){
    lock_guard<mutex> lock(this->m_mutex);

    Node* nuevoNodo = new Node(value, ref);

    if (!this->m_pRoot) { 
        this->m_pRoot = nuevoNodo;
        nuevoNodo->GetNextRef() = nuevoNodo; 
        nuevoNodo->getPrevRef() = nuevoNodo;
    } else {
        this->m_pLast->GetNextRef() = nuevoNodo;
        nuevoNodo->getPrevRef() = this->m_pLast;
        nuevoNodo->GetNextRef() = this->m_pRoot;
        this->m_pRoot->getPrevRef()  = nuevoNodo;
    }
    this->m_pLast = nuevoNodo;
    ++this->m_nElements;
}

template <typename Traits>
ostream &operator<<(ostream &os, CDoubleLinkedList<Traits> &container){
    lock_guard<mutex> lock(container.m_mutex);
    os << "CDoubleLinkedList: size = " << container.getSize() << endl;
    os << "[";
    
    auto *pCurrent = container.m_pRoot;
    for (size_t i = 0; i < container.m_nElements; i++){
        os << "(" << pCurrent->GetValue() << ", " << pCurrent->GetRef() << ")";
        pCurrent = pCurrent->GetNext();
        if( pCurrent ) os << ", ";
    }
    
    os << "]" << endl;
    return os;
}

#endif //DOUBLYCIRCULARLINKEDLIST_H_