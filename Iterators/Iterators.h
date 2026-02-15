#ifndef ITERATORS_H_
#define ITERATORS_H_

#include "GeneralIterator.h"
#include "../general/types.h"
#include "general/types.h"

//Iterators para CArray
template <typename Container>
class ArrayIterator :  public GeneralIterator<Container> {

    protected:
    using Parent = GeneralIterator<Container>;
    using value_type = typename Parent::value_type;

    Size m_pos;

    public:
    ArrayIterator(Container *pContainer, Size pos=0) : Parent(pContainer, pContainer->m_data), m_pos(pos){}

    bool operator!=(const ArrayIterator<Container> &another) {
        return this->m_pContainer != another.m_pContainer || m_pos != another.m_pos;
    }

    value_type &operator*() override { return Parent::m_data[m_pos].GetValueRef(); }
};


template <typename Container>
class ArrayForwardIterator : public ArrayIterator<Container>{

    using Parent = ArrayIterator<Container>;

    public:
    ArrayForwardIterator(Container *pContainer, Size pos=0) : Parent(pContainer, pos){}

    Parent &operator++(){
        if( Parent::m_pos < Parent::m_pContainer->getSize() )
            ++Parent::m_pos;
        return *this;
    }
};

template <typename Container>
class ArrayBackwardIterator :  public ArrayIterator<Container>
{ 
  using Parent = ArrayIterator<Container>;

  public:
    ArrayBackwardIterator(Container *pContainer, Size pos=0) : Parent(pContainer, pos){}

    ArrayBackwardIterator<Container> &operator++(){
        if( Parent::m_pos > 0 )
            --Parent::m_pos;
        return *this;
    }
}; 

//Iterators for CLinkedList

template <typename Container>
class LinkedListIterator : public GeneralIterator<Container> {

    protected:
    using Parent = GeneralIterator<Container>;
    using value_type = typename Parent::value_type;
    using Node = typename Container::Node;

    public:
    LinkedListIterator(Container *pContainer, Node *data) : Parent(pContainer, data){}

    bool operator!=(const LinkedListIterator<Container> &another) {
        return this->m_pContainer != another.m_pContainer || Parent::m_data != another.m_data;
    }

    bool operator==(const LinkedListIterator<Container> &another) {
        return !(*this != another);
    }

    value_type &operator*() override { return Parent::m_data->GetValueRef(); }
};

template <typename Container>
class LinkedListForwardIterator : public LinkedListIterator<Container>{

    using Parent = LinkedListIterator<Container>;
    using Node = typename Container::Node;

    public:
    LinkedListForwardIterator(Container *pContainer, Node *data) : Parent(pContainer, data){}

    LinkedListForwardIterator<Container> &operator++(){
        if( this->m_data != nullptr ) this->m_data = this->m_data->GetNext();
        return *this;
    }
};

//ITERATORS FOR DOUBLE LINKED LIST
template <typename Container>
class DoubleLinkedListBidirectionalIterator : public LinkedListIterator<Container> {

    public:
    using Parent = LinkedListIterator<Container>;
    using Node = typename Container::Node;

    DoubleLinkedListBidirectionalIterator(Container* pcontainer, Node* data): Parent(pcontainer, data) {}
    
    DoubleLinkedListBidirectionalIterator<Container>& operator++(){
        if (this->m_data != nullptr) this->m_data = this->m_data->GetNext();
        return *this;
    }

    DoubleLinkedListBidirectionalIterator<Container>& operator--(){
        if (this->m_data == nullptr) {
            if (this->m_pContainer != nullptr) this->m_data = this->m_pContainer->getLastNode();
        }
        else { this->m_data = this->m_data->getPrev(); }
        return *this;
    }
};

#endif //ITERATOS_H_