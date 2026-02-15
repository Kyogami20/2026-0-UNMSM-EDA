#include <iostream>
#include <sstream>
#include "../containers/doublelinkedlist.h"

using namespace std;

// Tipo de dato para las pruebas
using T1 = int;

// ===== FUNCIONES AUXILIARES =====

template <typename T>
void Print(T &val) {
    cout << val << " ";
}

template <typename T>
void Duplicate(T &val) {
    val *= 2;
}

template <typename T>
bool IsEven(T &val) {
    return val % 2 == 0;
}

// ===== DEMO DOUBLE LINKED LIST =====

void DemoDoubleLinkedList() {
    cout << "========================================" << endl;
    cout << "       CDoubleLinkedList DEMO           " << endl;
    cout << "========================================\n" << endl;

    // ===== PUSH BACK =====
    cout << "Crear lista e insertar elementos con push_back:" << endl;
    CDoubleLinkedList<T1> lista;
    lista.push_back(10, 1);
    lista.push_back(20, 2);
    lista.push_back(30, 3);
    cout << lista << endl;

    // ===== FOREACH IMPRIMIR =====
    cout << "Foreach - Imprimir elementos:" << endl;
    cout << "   ";
    lista.Foreach(Print<T1>);
    cout << "\n" << endl;

    // ===== FOREACH DUPLICAR =====
    cout << "Foreach - Duplicar elementos:" << endl;
    lista.Foreach(Duplicate<T1>);
    cout << lista << endl;

    // ===== FIRSTTHAT =====
    cout << "FirstThat - Buscar primer par:" << endl;
    auto it = lista.FirstThat(IsEven<T1>);
    if(it != lista.end()) {
        cout << "   Encontrado: " << *it << endl;
    } else {
        cout << "   No encontrado" << endl;
    }
    cout << endl;

    // ===== ITERADOR HACIA ADELANTE =====
    cout << "Recorrer hacia adelante:" << endl;
    cout << "   ";
    for(auto iter = lista.begin(); iter != lista.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << "\n" << endl;

    // ===== ITERADOR HACIA ATRAS =====
    cout << "Recorrer hacia atras:" << endl;
    cout << "   ";
    auto iter = lista.end();
    while(iter != lista.begin()) {
        --iter;
        cout << *iter << " ";
    }
    cout << "\n" << endl;

    // ===== CONSTRUCTOR COPIA =====
    cout << "Constructor de copia:" << endl;
    CDoubleLinkedList<T1> copia(lista);
    cout << "   Original: " << lista;
    cout << "   Copia:    " << copia << endl;

    // ===== CONSTRUCTOR MOVIMIENTO =====
    cout << "Constructor de movimiento:" << endl;
    CDoubleLinkedList<T1> movida(std::move(lista));
    cout << "   Movida:           " << movida;
    cout << "   Original (vacia): " << lista << endl;

    cout << "=== FIN DEL DEMO ===" << endl;
}