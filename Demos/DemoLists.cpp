#include <iostream>
#include "containers/linkedlist.h"

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

// ===== DEMO SIMPLE =====

void DemoLists() {
    cout << "CLinkedList\n" << endl;

    cout << "Crear lista e insertar elementos ordenados:" << endl;
    CLinkedList<AscendingTrait<T1>> lista;
    lista.Insert(30, 1);
    lista.Insert(10, 2);
    lista.Insert(20, 3);
    cout << lista << endl;

    cout << "Acceso con operator[]:" << endl;
    cout << "   lista[0] = " << lista[0] << endl;
    cout << "   lista[1] = " << lista[1] << endl;
    lista[1] = 99;
    cout << "   Después de modificar lista[1]:" << endl;
    cout << lista << endl;

    cout << "Foreach - Imprimir elementos:" << endl;
    cout << "   ";
    lista.Foreach(Print<T1>);
    cout << "\n" << endl;

    cout << "Foreach - Duplicar elementos:" << endl;
    lista.Foreach(Duplicate<T1>);
    cout << lista << endl;

    cout << "FirstThat - Buscar primer par:" << endl;
    auto it = lista.FirstThat(IsEven<T1>);
    if(it != lista.end()) {
        cout << "   Encontrado: " << *it << endl;
    } else {
        cout << "   No encontrado" << endl;
    }
    cout << endl;

    cout << "Constructor de copia:" << endl;
    CLinkedList<AscendingTrait<T1>> copia(lista);
    cout << "   Original: " << lista;
    cout << "   Copia:    " << copia << endl;

    cout << "Traits (Ascending vs Descending):" << endl;
    CLinkedList<AscendingTrait<T1>> asc;
    CLinkedList<DescendingTrait<T1>> desc;
    
    asc.Insert(50, 1);
    asc.Insert(20, 2);
    asc.Insert(80, 3);
    
    desc.Insert(50, 1);
    desc.Insert(20, 2);
    desc.Insert(80, 3);
    
    cout << "   Ascending:  " << asc;
    cout << "   Descending: " << desc << endl;

    cout << "=== FIN DEL DEMO ===" << endl;
}