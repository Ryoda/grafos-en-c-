#include <iostream>
#include "NodoV.hpp"
#ifndef NODOA_H
#define NODOA_H

template <class T, class C>
class NodoA
{
     private:
        C costo;
        NodoV<T>* terminal;
        NodoA<T,C>* prox;
    public:
        NodoA(NodoV<T>* terminal = NULL, C costo = C(), NodoA<T>* prox = NULL) : this->terminal(terminal), this->costo(costo), this->prox(prox) {};
        NodoV<T>* getTerminal() const { return this->terminal;};
        NodoA<T,C>* getProx() const { return this->prox;};
        void setTerminal(NodoV<T,C>* terminal) { this->terminal = terminal; };
        void setProx(NodoA<T,C>* prox) { this->prox = prox; };
};

#endif // NODOA_H
