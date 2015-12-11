#include <iostream>
#include "NodoV.hpp"
#include "NodoA.hpp"
#include "Lista.hpp"
#include "Cola.hpp"
#ifndef GRAFO_H
#define GRAFO_H

template <class T, class C = int>
class Grafo
{
    private:
        NodoV<T,C>* g, *tail;
        int n, a;
    public:
        //constructor
        Grafo(NodoV<T,C>* g = NULL, int n = 0, int a = 0) : this->g(g), this->n(n), this->a(a) {};
        ~Grafo();
        //Consultores
        int cantidadDeVertices() const;
        int cantidadDeAristas() const;
        bool existeVertice(T) const;
        bool existeArco(T,T) const;
        bool esVacio() const {return this->g == NULL;};
        void copiar(const Grafo&) const;
        Lista<T> sucesores(T) const;
        void sucesores(T, Lista<T>&) const;
        Lista<T> predecesores(T) const;
        void predecesores(T, Lista<T>&) const;
        //modificadores
        void addVertice(T);
        void addArco(T, T, C);
        void eliminarVertice(T);
        void eliminarArco(T,T);
        Grafo(const Grafo&);
    private:
        NodoV<T,C>* localizarApuntadorV(T u) const;
};

//Constructores

template <class T, class C>
Grafo<T,C> Grafo<T,C>::operator=(Grafo<T,C> &g)
{
    if(!this->esVacio())
    {
        this->copiar(g);
    }else
    {
        this->
    }
}

//consultores

template <class T, class C>
bool Grafo<T,C>::esVacio()
{
    return (this->cantidadDeVertices() == 0);
}


template <class T, class C>
int Grafo<T,C>::cantidadDeVertices()
{
    return this->n;
}

template <class T, class C>
int Grafo<T,C>::cantidadDeAristas()
{
    return this->a;
}

template <class T, class C> //retorna un bool: verdadero si existe el vertice en el grafo y falso en el caso contrario
bool Grafo<T,C>::existeVertice(T v) const
{
    NodoV<T,C>* indice = this->g;
    bool encontrado = false;
    while(indice != NULL && !encontrado)
    {
        if(indice->getInfo() == v)
            encontrado = true;
        indice = indice->getProx();
    }
    return encontrado;
}
template <class T, class C>
bool Grafo<T,C>::existeArco(T v, T w) const
{
    NodoV<T,C>*verticeV, *verticeW, *indice = this->g;
    NodoA<T,C>* indiceA;
    bool encontrado = false;
    int encontrados = 0;
    if(!this->esVacio())
    {
        while(indice != NULL && encontrados < 2) // ciclo para la comprobacion de la existencia de los vertices v y w, (ExisteVertice() tambien funciona pero es un poco menos eficiente)
        {
            if(indice->getInfo() == v || indice->getInfo() == w)
            {
                if(indice->getInfo() == v)
                    verticeV = indice;
                if(indice->getInfo() == w)
                    verticeW = indice;
                encontrados++;
            }
            indice = indice->getProx();
        }
        indiceA = verticeV->getPrimerArista();
        while(indiceA != NULL && !encontrado)
        {
            if(indiceA->getTerminal() == verticeW)
                encontrado = true;
            indiceA = indiceA->getProx();
        }
    }
    return encontrado;
}
template <class T, class C>
void Grafo<T,C>::addVertice(T v) const
{
    NodoV<T,C>* nuevo;
    NodoV<T,C>* indice;
    if(!this->existeVertice(v))
    {
        nuevo = new NodoV<T,C>(v);
        if(this->esVacio())
        {
            this->g = nuevo;
        }else
        {
            indice = this->g;
            while(indice->getProx() != NULL)
            {
                indice = indice->getProx();
            }
            indice->setProx(nuevo);
        }
        this->n++;
    }else
        std::cout << "agregarV(): el vertice ya existe" << endl;
}
template <class T, class C>
void Grafo<T,C>::addArco(T v, T w, C costo)
{
    NodoA<T,C>* nuevo, *indiceA;
    NodoV<T,C>* verticeV, *verticeW, *indice = this->g;
    bool encontrado = false;

    if(!this->esVacio())
    {
        if(this->existeVertice(v) && this->existeVertice(w) && !this->existeArco(v, w))
        {
            verticeV = this->localizarApuntadorV(v);
            verticeW = this->localizarApuntadorV(w);
            indiceA = verticeV->getPrimerArista();
            nuevo = new NodoA(verticeW, costo);

            if(indiceA != NULL)
            {
                while( indiceA->getProx() != NULL)
                {
                    indiceA = indiceA->getProx();
                }
                indiceA->setProx(nuevo);
            }else
            {
                verticeV->setPrimeraArista(nuevo);
            }

            this->a++;

        }else
        {
            std::cout << "addArco(): O alguno o ambos vertices no existen en el grafo, O ya hay un arco entre ambos vertices" << endl;
        }
    }else
    {
        std::cout << "addArco(): no se puede insertar un arco en un grafo vacio, inserte primero los vertices" << endl;
    }
}
template <class T, class C>
void Grafo<T,C>::sucesores(T u, Lista<T>& sucesores)
{
    NodoV<T,C> *indiceV;
    NodoA<T,C> *indiceA;

    if(!sucesores.esVacia())
    {
        sucesores.
    }

    if(!this->esVacio())
    {
        indiceV = this->g;
        while(indiceV->getInfo() != u && indiceV != NULL)
        {
            indiceV = indiceV->getProx();
        }
        if(indiceV != NULL)
        {
            indiceA = indiceV->getPrimerArista();
            while(indiceA != NULL)
            {
                sucesores.insertar(indiceA->getTerminal()->getInfo());
                indiceA = indiceA->getProx();
            }
        }
    }
}

template <class T, class C>
Lista<T> Grafo<T,C>::sucesores(T u)
{
    Lista<T> sucesores = new Lista<T>;

    this->sucesores(u, sucesores);

    return sucesores;
}

template <class T, class C>
void Grafo<T,C>::predecesores(T u, Lista<T>& predecesores)
{
    NodoV<T,C> *indiceV;
    NodoA<T,C> *indiceA;
    bool terminalEncontrado = false;
    if(!this->esVacio())
    {
        indiceV = this->g;
        while(indiceV != NULL)
        {
            terminalEncontrado = false;
            if(indiceV->getInfo() != u)
            {
                indiceA = indiceV->getPrimerArista();
                while(indiceA != NULL && !terminalEncontrado)
                {
                    if(indiceA->getTerminal()->getInfo() == u)
                    {
                        predecesores.insertar(indiceV->getInfo());
                        terminalEncontrado = true;
                    }
                    indiceA = indiceA->getProx();
                }
            }
            indiceV = indiceV->getProx();
        }
    }
}

template <class T, class C>
Lista<T> Grafo<T,C>::predecesores(T u)
{
    Lista<T> predecesores = new Lista<T>;

    this->predecesores(u, predecesores);

    return predecesores;
}

template <class T, class C>
NodoV<T,C>* Grafo<T,C>::localizarApuntadorV(T u)
{
    NodoV<T,C>* indice;
    indice = this->g;
    while(indice != NULL && indice->getInfo() != u)
    {
        indice = indice->getProx();
    }
    return indice;
}

template <class T, class C>
Grafo<T,C>::copiar(Grafo<T,C>& g)
{
    NodoV<T,C>* indicel;
    if(!this->esVacio())
        this->reestablecer();
    indice = g;
    while(indice != NULL && indice->getInfo() != u)
    {

        indice = indice->getProx();
    }
    return indice;
}

template <class T, class C>
void Grafo<T,C>::eliminarVertice(T v)
{
    NodoV<T,C>* indice, *anterior, *arista, *siguiente;
    NodoA<T,C>* terminales;
    bool terminaEnV = false;
    bool encontrado = false;
    if(!this->existeVertice(v))
    {
        cout << "posible error en eliminarVertice(): el vertice a eliminar no existe" << endl;
    }else
    {
        if(this->esVacio())
        {
            cout << "posible error en eliminarVertice(): el grafo esta vacio" << endl;
        }else
        {

            if(this->g->getInfo() == v)  //si el vertice a eliminar es el primero de la lista
            {
                encontrado = true;
                anterior = this->g;
                this->g = this->g->getProx();
            }else
            {
                indice = this->g->getProx();
                while(indice != NULL)
                {
                    if(indice->getInfo() == v)
                    {
                        anterior = indice;
                        encontrado = true;
                    }else
                    {
                        if(this->sucesores(v)->)
                    }

                    indice = indice->getProx();
                }
            }
            //se aisla el NodoV a destruir
            indice = anterior->getProx();
            anterior->setProx(indice->getProx());
            //al final, para eliminar el vertice, primero se eliminan todos los arcos que salen de el
            while(indice->getPrimerArista() != NULL)
            {

            }
            delete vertice;
        }
    }
}

template <class T, class C>
void Grafo<T,C>::eliminarArco(T v, T w)
{
    NodoV<T,C>* indiceV;
    NodoA<T,C>* terminales;
    bool terminaEnW = false;
    if(!this->esVacio())
    {
        if(this->existeArco(v, w))
        {
            indiceV = this->localizarApuntadorV(v);
            terminales = indiceV->getPrimerArista();
            if(terminales != NULL)
            {
                    if(terminales->getTerminal()->getInfo() == w) // caso en que el terminal es la primera arista de la lista
                    {
                        terminaEnW = true;
                        arista = terminales;
                        indice->setPrimeraArista(terminales->getProx());
                    }else  //caso en que no se encuentra o se encuentra en el 2do o mas de la lista
                    {
                        while(terminales->getProx() != NULL && !terminaEnW)
                        {
                            if(terminales->getProx()->getTerminal()->getInfo() == w)
                                terminaEnW == true;
                            else
                                terminales = terminales->getProx();
                        }
                        if(terminaEnW)
                        {
                            arista = terminales->getProx();
                            terminales->setProx(arista->getProx());
                        }
                    }
                    if(terminaEnW)
                        delete arista;
            }
        }
    }
}

template Grafo<T,C>
void Grafo<T,C>::vaciar()
{
    while(!this->esVacio())
    {
        this->eliminarVertice(1);
    }
}

#endif // GRAFO_H
