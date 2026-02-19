#ifndef STACK_H_
#define STACK_H_

#include <iostream>
#include <mutex>
#include <utility>

#include "../general/types.h"
#include "../general/NodoLineal.h"

using namespace std;

template <typename Traits>
class Stack {
    using value_type = Traits;
    using NodoStack = NodoLineal<Traits>;

    private:
        NodoStack *m_pTop;
        size_t m_nElements;
        mutable mutex m_mutex;  

        void internalPush(const value_type &value, ref_type ref);
    public:

        //Constructor por Defecto
        Stack(): m_pTop(nullptr), m_nElements(0) {}

        //Constructor copia
        Stack(const Stack<Traits> &another): Stack() {
            lock_guard<mutex> lock(another.m_mutex);

            Stack<Traits> temp;
            NodoStack *pCurrent = another.m_pTop;
            while (pCurrent){
                temp.internalPush(pCurrent->GetValue(), pCurrent->GetRef());
                pCurrent = pCurrent->GetNext();
            }

            NodoStack *pTemp = temp.m_pTop;
            while (pTemp) {
                internalPush(pTemp->GetValue(), pTemp->GetRef());
                pTemp = pTemp->GetNext();
            }
        }

        //Constructor de Movimiento
        Stack(Stack<Traits> &&another) noexcept {
            lock_guard<mutex> lock(another.m_mutex);

            m_pTop = exchange(another.m_pTop, nullptr);
            m_nElements = exchange(another.m_nElements, 0);
        }

        size_t getSize() { return m_nElements; }

        void push(const value_type &value, ref_type ref);
        NodoStack pop(); 

        template <typename T>
        friend ostream &operator<<(ostream &os, Stack<T> &container);

        template <typename T>
        friend istream &operator>>(istream &is, Stack<T> &container);
};

template <typename Traits>
void Stack<Traits>::push(const value_type &value, ref_type ref){
    lock_guard<mutex> lock(m_mutex);
    internalPush(value, ref);
}

template<typename Traits>
void Stack<Traits>::internalPush(const value_type &value, ref_type ref){
    NodoStack *nNodo = new NodoStack(value, ref);

    nNodo->GetNextRef() = m_pTop;
    m_pTop = nNodo;
    ++m_nElements;
}

template <typename Traits>
NodoLineal<Traits> Stack<Traits>::pop(){
    lock_guard<mutex> lock(m_mutex);

    if (!m_pTop) throw out_of_range("Stack Vacio");

    NodoStack *temp = m_pTop;
    NodoStack topValue = *temp;

    m_pTop = m_pTop->GetNext();
    delete temp;
    --m_nElements;

    return topValue;
}

template <typename Traits>
ostream &operator<<(ostream &os, Stack<Traits> &container){
    lock_guard<mutex> lock(container.m_mutex);

    os << "Stack: size = " << container.getSize() << endl;
    os << "[";
    
    NodoLineal<Traits> *pCurrent = container.m_pTop;
    while( pCurrent ){
        os << "(" << pCurrent->GetValue() << ", " << pCurrent->GetRef() << ")";
        pCurrent = pCurrent->GetNext();
        if( pCurrent ) os << ", ";
    }
    
    os << "]" << endl;
    return os;
} 

template <typename Traits>
istream &operator>>(istream &is, Stack<Traits> &container){
    lock_guard<mutex> lock(container.m_mutex);

    typename Stack<Traits>::value_type val;
    ref_type ref;

    if(is >> val >> ref) { container.internalPush(val, ref); }
    
    return is;
}

#endif //STACK_H_