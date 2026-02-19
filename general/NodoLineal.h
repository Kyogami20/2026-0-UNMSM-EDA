#ifndef NODOLINEAL_H_
#define NODOLINEAL_H_

#include <iostream>
#include <mutex>
#include <utility>

#include "../general/types.h"

using namespace std;

template <typename Traits>
class NodoLineal {
    
    private:
        using value_type = Traits;

        NodoLineal *m_pNext;
        value_type m_data;
        ref_type m_ref;

    public:
        NodoLineal() {}
        NodoLineal(value_type value, ref_type ref): m_pNext(nullptr), m_data(value), m_ref(ref) {}

        value_type  GetValue   () const { return m_data; }
        value_type &GetValueRef() { return m_data; }

        ref_type    GetRef     () const { return m_ref;   }
        ref_type   &GetRefRef  () { return m_ref;   }

        NodoLineal   * GetNext     () const { return m_pNext;   }
        NodoLineal   *&GetNextRef  () { return m_pNext;   }

        NodoLineal &operator=(const NodoLineal &another){
            m_data = another.GetValue();
            m_ref   = another.GetRef();
            return *this;
        }

        bool operator==(const NodoLineal &another) const { return m_data == another.GetValue(); }
        bool operator!=(const NodoLineal &another) const { return !(this->operator==(another)); }
};

#endif //NODOLINEAL_H_