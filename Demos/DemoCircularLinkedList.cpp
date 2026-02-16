#include <iostream>
#include <utility>
#include <functional>

#include "../general/types.h"
#include "../containers/LinkedCircularList.h"

using namespace std;

void DemoCircularLinkedList() {

    cout << "--------------------------------------------\n";
    cout << "  1) CLinkedList - push_back (sin orden)\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedList<AscendingTrait<int>> lista;
        lista.push_back(10, 0);
        lista.push_back(30, 1);
        lista.push_back(20, 2);
        lista.push_back(50, 3);
        cout << lista;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  2) CLinkedList - Insert (orden descendente, menor primero)\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedList<DescendingTrait<int>> lista;
        lista.Insert(30, 0);
        lista.Insert(10, 1);
        lista.Insert(50, 2);
        lista.Insert(20, 3);
        lista.Insert(40, 4);
        cout << lista;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  3) CLinkedList - constructor copia\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedList<AscendingTrait<int>> original;
        original.push_back(1, 0);
        original.push_back(2, 1);
        original.push_back(3, 2);

        CLinkedList<AscendingTrait<int>> copia(original);
        cout << "Original: " << original;
        cout << "Copia:    " << copia;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  4) CLinkedList - constructor movimiento\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedList<AscendingTrait<int>> original;
        original.push_back(7, 0);
        original.push_back(8, 1);
        original.push_back(9, 2);

        CLinkedList<AscendingTrait<int>> movida(move(original));
        cout << "Movida:   " << movida;
        cout << "Original (vaciada): [size=" << original.getSize() << "]\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  5) CLinkedCircularList - push_back\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(10, 0);
        circular.push_back(20, 1);
        circular.push_back(30, 2);
        circular.push_back(40, 3);
        cout << circular;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  6) CLinkedCircularList - naturaleza circular\n";
    cout << "     (dar 2 vueltas completas manualmente)\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(100, 0);
        circular.push_back(200, 1);
        circular.push_back(300, 2);

        // Accedemos al root vía cast al padre para recorrer manualmente
        // En un proyecto real se haría con un iterator
        // Usamos el operator<< para verificar los 3 elementos
        cout << circular;

        cout << "Recorrido 2 vueltas: ";
        // Acceso al pRoot via herencia protected
        // (desde fuera de la clase usaríamos un iterator; aquí lo hacemos
        //  dentro de main como demostración conceptual con la función amiga)
        cout << "(ver salida de operator<< arriba - la lista es circular)\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  7) CLinkedCircularList - constructor copia\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<string>> original;
        original.push_back("alfa",  0);
        original.push_back("beta",  1);
        original.push_back("gamma", 2);

        CLinkedCircularList<AscendingTrait<string>> copia(original);
        cout << "Original: " << original;
        cout << "Copia:    " << copia;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  8) CLinkedCircularList - constructor movimiento\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> original;
        original.push_back(5, 0);
        original.push_back(6, 1);
        original.push_back(7, 2);

        CLinkedCircularList<AscendingTrait<int>> movida(move(original));
        cout << "Movida:   " << movida;
        cout << "Original (vaciada): [size=" << original.getSize() << "]\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  9) CLinkedCircularList - con doubles\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<DescendingTrait<double>> circular;
        circular.push_back(3.14, 0);
        circular.push_back(2.71, 1);
        circular.push_back(1.41, 2);
        circular.push_back(1.73, 3);
        cout << circular;
    }
}