#ifndef ITERATORS_H_
#define ITERATORS_H_

#include "../containers/GeneralIterator.h"
#include "../general/types.h"

template <typename Container>
class ArrayForwardIterator : public GeneralIterator<Container>
{ 
  using Parent = GeneralIterator<Container>;
  public:
    ArrayForwardIterator(Container *pContainer, Size pos=0)       : Parent(pContainer, pos){}
    ArrayForwardIterator(ArrayForwardIterator<Container> &another):  Parent(another){}

    ArrayForwardIterator<Container> &operator++(){
        if( Parent::m_pos < Parent::m_pContainer->getSize() )
            ++Parent::m_pos;
        return *this;
    }
};

template <typename Container>
class ArrayBackwardIterator :  public GeneralIterator<Container>
{ 
  using Parent = GeneralIterator<Container>;
  public:
    ArrayBackwardIterator(Container *pContainer, Size pos=0)          : Parent(pContainer, pos){}
    ArrayBackwardIterator(ArrayBackwardIterator<Container> &another)  :  Parent(another){}

    ArrayBackwardIterator<Container> &operator++(){
        if( Parent::m_pos > -1 )
            --Parent::m_pos;
        return *this;
    }
};

#endif //ITERATOS_H_