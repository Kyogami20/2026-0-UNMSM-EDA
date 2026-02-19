#ifndef QUEUE_H_
#define QUEUE_H_

#include <iostream>
#include <mutex>
#include <utility>

#include "../general/types.h"
#include "../general/NodoLineal.h"

using namespace std;

template <typename Traits>
class Queue {
    using value_type = Traits;
    using NodoQueue = NodoLineal<Traits>;

    void internalPush(const value_type &value, ref_type ref);
    private: 
        NodoQueue *m_pFront;
        NodoQueue *m_pBack;
        size_t m_nElements;
        mutable mutex m_mutex;

        //Constructor por Defecto
        Queue(): m_pBack(nullptr), m_pFront(nullptr), m_nElements(0) {}

        //Constructor copia
        Queue(const Queue<Traits> &another): Queue(){
            lock_guard<mutex> lock(another.m_mutex);


        }

        //Constructor por movimiento
        Queue(Queue<Traits> &&another){
            lock_guard<mutex> lock(another.m_mutex);

            m_pFront = exchange(another.m_pFront, nullptr);
            m_pBack = exchange(another.m_pBack, nullptr);
            m_nElements = exchange(another.m_nElements, 0);
        }

        size_t getSize() { return m_nElements; }

        void push(const value_type &value, ref_type ref);
        NodoQueue pop(); 

        template <typename T>
        friend ostream &operator<<(ostream &os, Queue<T> &container);

        template <typename T>
        friend istream &operator>>(istream &is, Queue<T> &container);
};

template <typename Traits>
void Queue<Traits>::push(const value_type &value, ref_type ref){
    lock_guard<mutex> lock(m_mutex);
    internalPush(value, ref);
}

template <typename Traits>
void Queue<Traits>::internalPush(const value_type &value, ref_type ref){
    NodoQueue *nuevo = new NodoQueue(value, ref);
    
    (!m_pFront) ? m_pFront = nuevo : m_pBack->GetNextRef() = nuevo;
    m_pBack = nuevo;
    ++m_nElements;
}

template <typename Traits>
NodoLineal<Traits> Queue<Traits>::pop(){
    lock_guard<mutex> lock(m_mutex);

    if (!m_pFront) throw out_of_range("Stack Vacio");

    NodoLineal<Traits> *temp = m_pFront;
    NodoLineal<Traits> salir = *temp;

    m_pFront = m_pFront->GetNext();
    if (!m_pFront) m_pBack = nullptr;

    delete temp;
    --m_nElements;
    return salir;
}

template <typename Traits>
ostream &operator<<(ostream &os, Queue<Traits> &container){

}

#endif //QUEUE_H_