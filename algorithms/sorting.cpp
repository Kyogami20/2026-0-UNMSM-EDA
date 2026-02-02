#include <iostream>
#include "sorting.h"
#include "containers/array.h"
using namespace std;

template <typename T>
void Print(T &p1, T &p2){
    cout << "p1: " << p1 << " p2: " << p2 << endl;
}

template <>
void Print(char &p1, char &p2){
    cout << "char1: " << p1 << " char2: " << p2 << endl;
}

void DemoTemplates(){
    int    a = 5, b = 8;
    double x = 20, y = 30;
    string str1="CS", str2 = "UNI";
    char   c1 = 'X', c2 = 'Y';

    Print(a, b);
    Print(x, y);
    Print(str1, str2);
    Print(c1, c2);
}

