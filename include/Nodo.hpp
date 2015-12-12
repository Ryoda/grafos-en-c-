#include<iostream>
#ifndef NODO_H
#define NODO_H
template<class T>
class Nodo
{
    private:
        T datos;
        Nodo<T> *siguiente;
    public:
        Nodo(){ this->datos = 0; this->siguiente = NULL;};
        Nodo(T datos = 0, Nodo<T> *siguiente = NULL){ this->datos = datos; this->siguiente = siguiente;};
        Nodo(const Nodo& other) {this->dato = other.datos;this->siguiente = other.siguiente;};
        T getDatos() const {return(this->datos);};
        Nodo<T>* getSiguiente() const { return (this->siguiente);};
        void setDatos(T datos){this->datos = datos;};
        void setSiguiente(Nodo<T>* siguiente){this->siguiente = siguiente;};
        void invertir();
};
#endif // NODO_H
