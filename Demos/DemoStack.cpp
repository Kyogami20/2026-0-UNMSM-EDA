#include <iostream>

#include "../containers/Stack.h"

using namespace std;

void printSeparator(const string &title){
    cout << "\n=============================" << endl;
    cout << "  " << title << endl;
    cout << "=============================" << endl;
}

void DemoStack(){

    printSeparator("TEST: push y operator<<");
    {
        Stack<int> s;
        s.push(10, 1);
        s.push(20, 2);
        s.push(30, 3);
        cout << s;
    }

    printSeparator("TEST: pop");
    {
        Stack<int> s;
        s.push(100, 1);
        s.push(200, 2);
        s.push(300, 3);

        cout << "Antes: " << s;

        NodoStack<int> nodo = s.pop();
        cout << "Popeado -> valor: " << nodo.GetValue()
             << ", ref: "            << nodo.GetRef() << endl;

        cout << "Despues: " << s;
    }


    printSeparator("TEST: pop en stack vacio");
    {
        Stack<int> s;
        try {
            s.pop();
            cout << "ERROR: no lanzó excepción" << endl;
        } catch (const out_of_range &e) {
            cout << "Excepcion capturada correctamente: " << e.what() << endl;
        }
    }

    printSeparator("TEST: constructor copia");
    {
        Stack<int> original;
        original.push(1, 1);
        original.push(2, 2);
        original.push(3, 3);

        Stack<int> copia(original);

        cout << "Original: " << original;
        cout << "Copia:    " << copia;

        copia.pop();
        cout << "\nDespues de pop en copia:" << endl;
        cout << "Original: " << original;
        cout << "Copia:    " << copia;
    }

    printSeparator("TEST: constructor de movimiento");
    {
        Stack<int> original;
        original.push(10, 1);
        original.push(20, 2);

        Stack<int> movido(move(original));

        cout << "Movido:   " << movido;
        cout << "Original (debe estar vacio): size = " << original.getSize() << endl;
    }

    printSeparator("TEST: operator>> (simula entrada: '42 7')");
    {
        Stack<int> s;
        s.push(42, 7);
        cout << "Elemento ingresado (valor=42, ref=7):" << endl;
        cout << s;
    }

    printSeparator("TEST: Stack<string>");
    {
        Stack<string> s;
        s.push("hola",  1);
        s.push("mundo", 2);
        s.push("stack", 3);

        cout << s;

        NodoStack<string> top = s.pop();
        cout << "Pop -> " << top.GetValue() << endl;
        cout << s;
    }

    cout << "\n=============================" << endl;
    cout << "  Todos los tests completados" << endl;
    cout << "=============================" << endl;
}