#ifndef __SORTING_H__
#define __SORTING_H__
#include "../util.h"
#include "../compareFunc.h"

template <typename T>
void BurbujaRecursivo(T arr[], ContainerRange n, 
                      bool (*pComp)(const T &, const T &) ) {
    if (n <= 1)
        return;
    for (auto j = 1; j < n; ++j)
        if ( pComp(arr[j], arr[0]) )
            intercambiar(arr[0], arr[j]);
    BurbujaRecursivo(arr+1, n-1, pComp);
}

void DemoBurbuja();

#endif // __SORTING_H__