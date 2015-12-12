#ifndef NODOA_H
#define NODOA_H
#include <iostream>
#include "NodoV.hpp"

template <class T, class C>
class NodoV;

template <class T, class C>
class NodoA
{
     private:
        NodoV<T,C>* terminal;
        C costo;
        NodoA<T,C>* prox;
    public:
        NodoA(NodoV<T,C>* terminal = NULL, C costo = C(), NodoA<T,C>* prox = NULL) : terminal(terminal), costo(costo),  prox(prox) {};
        NodoV<T,C>* getTerminal() const { return this->terminal;};
        NodoA<T,C>* getProx() const { return this->prox;};
        C getCost() const;
        void setCost(C cost);
        void setTerminal(NodoV<T,C>* terminal) { this->terminal = terminal; };
        void setProx(NodoA<T,C>* prox) { this->prox = prox; };
};

template <class T, class C>
C NodoA<T,C>::getCost() const
{
    return this->costo;
}
template <class T, class C>
void NodoA<T,C>::setCost(C cost)
{
    this->costo = cost;
}
#endif // NODOA_H
