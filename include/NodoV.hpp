#ifndef NODOV_H
#define NODOV_H
#include <iostream>
#include "NodoA.hpp"

template <class T, class C>
class NodoV
{
    private:
        T info;
        NodoV<T, C>* prox;
        NodoA<T, C>* pri;
    public:
        NodoV(T info = T(), NodoV<T, C>* prox = NULL, NodoA<T, C>* pri = NULL) : info(info),prox(prox), pri(pri) {};
        T getInfo() const { return this->info;};
        NodoV<T, C>* getProx() const {return this->prox;};
        NodoA<T, C>* getPrimerArista() const {return this->pri;};
        void setProx(NodoV<T,C>* prox) { this->prox = prox; };
        void setPrimeraArista(NodoA<T,C>* pri) { this->pri = pri; };
};

#endif // NODOV_H
