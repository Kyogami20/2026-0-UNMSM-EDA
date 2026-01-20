#ifndef __ARRAY_H__
#define __ARRAY_H__
#include <stddef.h>

class CArray{
private:
    int  m_size  = 0;
    int  *m_data = nullptr; // Fixed size for simplicity;
public:
    CArray(int size);
    ~CArray();

    int& operator[](int index);
    int  getSize() const;
};

void DemoArray();

#endif // __ARRAY_H__