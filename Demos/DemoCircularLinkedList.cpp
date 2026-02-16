#include <iostream>
#include <utility>
#include <functional>

#include "../general/types.h"
#include "../containers/LinkedCircularList.h"

using namespace std;

void DemoCircularLinkedList() {

    cout << "--------------------------------------------\n";
    cout << "  1) CLinkedCircularList - push_back\n";
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
    cout << "  2) CLinkedCircularList - constructor copia\n";
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
    cout << "  3) CLinkedCircularList - constructor movimiento\n";
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
    cout << "  4) CLinkedCircularList - iterador for-range\n";
    cout << "     (begin/end con CircularLinkedLisForwardtIterator)\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(10, 0);
        circular.push_back(20, 1);
        circular.push_back(30, 2);
        circular.push_back(40, 3);

        cout << "for-range: ";
        for (auto &val : circular)
            cout << val << " ";
        cout << "\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  5) CLinkedCircularList - naturaleza circular\n";
    cout << "     tras una vuelta el siguiente es el primero\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(100, 0);
        circular.push_back(200, 1);
        circular.push_back(300, 2);

        auto it = circular.begin();
        for (size_t i = 0; i < circular.getSize(); ++i, ++it)
            cout << "  vuelta[" << i << "] = " << *it << "\n";

        cout << "  Siguiente tras ultima vuelta (= primero): " << *it << "\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  6) CLinkedCircularList - Foreach\n";
    cout << "      imprime cada elemento multiplicado x2\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(5,  0);
        circular.push_back(10, 1);
        circular.push_back(15, 2);
        circular.push_back(20, 3);

        cout << "Valores x2: ";
        circular.Foreach([](int &val) {
            cout << val * 2 << " ";
        });
        cout << "\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  7) CLinkedCircularList - FirstThat\n";
    cout << "      busca el primer elemento mayor que 25\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(10, 0);
        circular.push_back(30, 1);
        circular.push_back(20, 2);
        circular.push_back(50, 3);

        auto it = circular.FirstThat([](int &val) {
            return val > 25;
        });

        if (it != circular.end())
            cout << "Primer valor > 25: " << *it << "\n";
        else
            cout << "No encontrado\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  8) CLinkedCircularList - con doubles\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<double>> circular;
        circular.push_back(3.14, 0);
        circular.push_back(2.71, 1);
        circular.push_back(1.41, 2);
        circular.push_back(1.73, 3);
        cout << circular;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  9) CLinkedCircularList - operador []\n";
    cout << "      acceso directo por indice\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(111, 0);
        circular.push_back(222, 1);
        circular.push_back(333, 2);
        circular.push_back(444, 3);

        cout << "circular[0] = " << circular[0] << "\n";
        cout << "circular[2] = " << circular[2] << "\n";
        
        circular[1] = 999;
        cout << "Despues de circular[1] = 999:\n";
        cout << circular;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  10) CLinkedCircularList - lista vacia\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> empty;
        cout << empty;
        cout << "Tamanio: " << empty.getSize() << "\n";
        
        cout << "Agregando elemento...\n";
        empty.push_back(42, 0);
        cout << empty;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  11) CLinkedCircularList - con chars\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<DescendingTrait<char>> circular;
        circular.push_back('A', 0);
        circular.push_back('B', 1);
        circular.push_back('C', 2);
        circular.push_back('D', 3);

        cout << "Lista de caracteres:\n";
        cout << circular;
        
        cout << "Iterando: ";
        for (auto &c : circular)
            cout << c << " ";
        cout << "\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  12) CLinkedCircularList - multiples vueltas\n";
    cout << "      iterando 2x el tamanio (demuestra circular)\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(1, 0);
        circular.push_back(2, 1);
        circular.push_back(3, 2);

        cout << "Iterando 6 elementos (2 vueltas completas):\n";
        auto it = circular.begin();
        for (size_t i = 0; i < 6; ++i, ++it) {
            cout << "  pos[" << i << "] = " << *it << "\n";
        }
    }

    cout << "\n--------------------------------------------\n";
    cout << "  13) CLinkedCircularList - copia profunda\n";
    cout << "      modificar copia no afecta original\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> original;
        original.push_back(10, 0);
        original.push_back(20, 1);
        original.push_back(30, 2);

        CLinkedCircularList<AscendingTrait<int>> copia(original);
        
        cout << "Antes de modificar copia:\n";
        cout << "Original: " << original;
        cout << "Copia:    " << copia;
        
        copia.push_back(40, 3);
        copia.push_back(50, 4);
        
        cout << "\nDespues de agregar elementos a la copia:\n";
        cout << "Original: " << original;
        cout << "Copia:    " << copia;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  14) CLinkedCircularList - Foreach con modificacion\n";
    cout << "      duplica cada valor in-place\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(2, 0);
        circular.push_back(4, 1);
        circular.push_back(6, 2);
        circular.push_back(8, 3);

        cout << "Antes: " << circular;
        
        circular.Foreach([](int &val) {
            val *= 2;
        });
        
        cout << "Despues de duplicar cada valor:\n";
        cout << circular;
    }

    cout << "\n--------------------------------------------\n";
    cout << "  15) CLinkedCircularList - FirstThat sin resultado\n";
    cout << "      busca elemento que no existe\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> circular;
        circular.push_back(1, 0);
        circular.push_back(2, 1);
        circular.push_back(3, 2);

        auto it = circular.FirstThat([](int &val) {
            return val > 100;
        });

        if (it != circular.end())
            cout << "Encontrado: " << *it << "\n";
        else
            cout << "No se encontro elemento > 100\n";
    }

    cout << "\n--------------------------------------------\n";
    cout << "  16) CLinkedCircularList - comparación de tamaños\n";
    cout << "--------------------------------------------\n";
    {
        CLinkedCircularList<AscendingTrait<int>> small;
        small.push_back(1, 0);
        small.push_back(2, 1);

        CLinkedCircularList<AscendingTrait<int>> large;
        large.push_back(10, 0);
        large.push_back(20, 1);
        large.push_back(30, 2);
        large.push_back(40, 3);
        large.push_back(50, 4);

        cout << "Lista pequenia (size=" << small.getSize() << "): " << small;
        cout << "Lista grande (size=" << large.getSize() << "): " << large;
    }

    cout << "\n============================================\n";
    cout << "  DEMO COMPLETADO\n";
    cout << "============================================\n";
}