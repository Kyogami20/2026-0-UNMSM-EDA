#ifndef ITERATORS_H_
#define ITERATORS_H_

#include "../containers/GeneralIterator.h"
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
    ArrayIterator(Container *pContainer, Size pos=0) : Parent(pContainer), m_pos(pos){}

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
        if( Parent::m_pos > -1 )
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

    public:
    LinkedListIterator(Container *pContainer) : Parent(pContainer){}

    bool operator!=(const LinkedListIterator<Container> &another) {
        return this->m_pContainer != another.m_pContainer || Parent::m_data != another.m_data;
    }

    value_type &operator*() override { return Parent::m_data->GetValueRef(); }
};

template <typename Container>
class LinkedListForwardIterator : public LinkedListIterator<Container>{

    using Parent = LinkedListIterator<Container>;

    public:
    LinkedListForwardIterator(Container *pContainer) : Parent(pContainer){}

    Parent &operator++(){
        if( Parent::m_data != nullptr )Parent::m_data = Parent::m_data->GetNext();
        return *this;
    }
};

#endif //ITERATOS_H_