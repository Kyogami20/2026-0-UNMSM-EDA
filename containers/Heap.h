#pragma once

#include <iostream>
#include <mutex>
#include <vector>

using namespace std;

namespace hpq{

    template<typename T>
    struct heap_traits{
        using value_type = T;
        using size_t = size_t;
        using comparator_type = greater<T>;
        using container_type = vector<T>
    };
      
    namespace detail{


    }
    
}