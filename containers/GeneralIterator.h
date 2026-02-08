#ifndef __GENERAL_ITERATOR_H__
#define __GENERAL_ITERATOR_H__
#include "util.h"

template <typename Container>
class GeneralIterator{
  public:
  using value_type  = typename Container::value_type;
  using Node        = typename Container::Node;
  
  protected:
    Container  *m_pContainer = nullptr;
    Node       *m_data       = nullptr;

  public:
    GeneralIterator(Container *pContainer) 
         : m_pContainer(pContainer), m_data(pContainer->m_data) {}

    GeneralIterator(GeneralIterator<Container> &another)
         :  m_pContainer(another.m_pContainer), m_data (another.m_data){}
    
    virtual ~GeneralIterator() = default;
    virtual value_type &operator*() = 0;
};

#endif // __GENERAL_ITERATOR_H__
