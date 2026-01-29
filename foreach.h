#ifndef __FOREACH_H__
#define __FOREACH_H__

template <typename Iterator, typename FuncObj>
void Foreach(Iterator begin, Iterator end, FuncObj fn){
    auto iter = begin;
    for(; iter != end ; ++iter)
        fn(*iter);
}

template <typename Container, typename FuncObj>
void Foreach(Container &container, FuncObj fn){
    Foreach(container.begin(), container.end(), fn);
}

#endif