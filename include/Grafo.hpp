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
        NodoV<T,C>* g;
        int n, a;
    public:
        //constructor
        Grafo(NodoV<T,C>* g = NULL, int n = 0, int a = 0) : g(g), n(n), a(a) {};
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
        void imprimir() const;
        Lista<T> dfs() const;
        //modificadores
        void addVertice(T);
        void addArco(T, T, C);
        void eliminarVertice(T);
        void eliminarArco(T,T);
        void vaciar();
        Grafo(const Grafo&);
        //destructor
        ~Grafo();
        //sobrecarga de impresion
        template<class TP,class CP>
        friend std::ostream& operator << (std::ostream& o,const Grafo<TP,CP>&g);
        //sobrecarga de asignacion
        Grafo<T,C> operator=(Grafo<T,C> &g);
        NodoV<T,C>* getG() const {return this->g;};
    private:
        NodoV<T,C>* localizarApuntadorV(T u) const;
        void dfs(T, Lista<T>&) const;

};

//Constructores
//copy constructor (ON PROGRESS)
/*
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
*/
//consultores

template <class T, class C>
int Grafo<T,C>::cantidadDeVertices() const
{
    return this->n;
}

template <class T, class C>
int Grafo<T,C>::cantidadDeAristas() const
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
Lista<T> Grafo<T,C>::dfs() const
{
    NodoV<T,C> *v;
    Lista<T> sucesores;
    Lista<T> marcados;
    T e;
    if(!this->esVacio())
    {
        v = this->getG();
        while(v != NULL)
        {
            if(!marcados.localizar(v->getInfo()))
            {
                marcados.agregar(v->getInfo());
                sucesores = this->sucesores(v->getInfo());
                while(!sucesores.esVacia())
                {
                    e = sucesores.consultar();
                    if(!marcados.localizar(e))
                    {
                        marcados.agregar(e);
                        dfs(e, marcados);
                    }
                    sucesores.eliminar();
                }
            }
             v = v->getProx();
        }
    }else
    {
        std::cout << "dfs(): el grafo esta vacio" << std::endl;
    }
    return marcados;
}

template <class T,class C>
void Grafo<T,C>::dfs(T e, Lista<T>& marcados) const
{
    T u;
    Lista<T> sucesores = this->sucesores(e);
    while(!sucesores.esVacia())
    {
        u = sucesores.consultar();
        sucesores.eliminar();
        if(!marcados.localizar(u))
        {
            marcados.agregar(u);
            this->dfs(u, marcados);
        }
    }
}

//      modificadores
template <class T, class C>
void Grafo<T,C>::addVertice(T v)
{
    NodoV<T,C>* nuevo;
    if(!this->existeVertice(v))
    {
        nuevo = new NodoV<T,C>(v);
        if(this->esVacio())
        {
            this->g = nuevo;
        }else
        {
            nuevo->setProx(this->g);
            this->g = nuevo;
        }
        this->n++;
    }else
        std::cout << "agregarV(): el vertice ya existe" << endl;
}
template <class T, class C>
void Grafo<T,C>::addArco(T v, T w, C costo = 1)
{
    NodoA<T,C>* nuevaArista;
    NodoV<T,C>* verticeV, *verticeW;

    if(!this->esVacio())
    {
        if(this->existeVertice(v) && this->existeVertice(w) && !this->existeArco(v, w) && (v != w))
        {
            verticeV = this->localizarApuntadorV(v);
            verticeW = this->localizarApuntadorV(w);
            nuevaArista = new NodoA<T,C>(verticeW, costo);

            if(verticeV->getPrimerArista() != NULL)
            {
                nuevaArista->setProx(verticeV->getPrimerArista());
                verticeV->setPrimeraArista(nuevaArista);
            }else
            {
                verticeV->setPrimeraArista(nuevaArista);
            }

            this->a++;

        }else
        {
            if(!this->existeVertice(v))
                std::cout << "exepcion en addArco(): el vertice: " << v << " no existe en el grafo" << std::endl;
            if(!this->existeVertice(w))
                std::cout << "exepcion en addArco(): el vertice: " << w << " no existe en el grafo" << std::endl;
            if(this->existeArco(v, w))
                std::cout << "exepcion en addArco(): el arco de " << v << " a " << w << "ya existe" << std::endl;
            if(v == w)
                std::cout << "exepcion en addArco(): vertice origen y destino son iguales" << std::endl;
        }
    }else
    {
        std::cout << "addArco(): no se puede insertar un arco en un grafo vacio, inserte primero los vertices" << endl;
    }
}
template <class T, class C>
void Grafo<T,C>::sucesores(T u, Lista<T>& sucesores) const
{
    NodoV<T,C> *indiceV;
    NodoA<T,C> *indiceA;

    if(!sucesores.esVacia())
    {
        sucesores.reestablecer();
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
                sucesores.agregar(indiceA->getTerminal()->getInfo());
                indiceA = indiceA->getProx();
            }
        }
    }
}

template <class T, class C>
Lista<T> Grafo<T,C>::sucesores(T u) const
{
    Lista<T> sucesores;

    this->sucesores(u, sucesores);

    return sucesores;
}

template <class T, class C>
void Grafo<T,C>::predecesores(T u, Lista<T>& predecesores) const
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
                        predecesores.agregar(indiceV->getInfo());
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
Lista<T> Grafo<T,C>::predecesores(T u) const
{
    Lista<T> predecesores;

    this->predecesores(u, predecesores);

    return predecesores;
}

template <class T, class C>
NodoV<T,C>* Grafo<T,C>::localizarApuntadorV(T u) const
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
void Grafo<T,C>::copiar(const Grafo<T,C>& g) const
{
    NodoV<T,C>* indice, *nuevo;
    NodoA<T,C>* indiceA;
    if(!this->esVacio() || g.esVacio())
        this->reestablecer();
    if(!g.esVacio())
    {
        indice = g.getG();
        while(indice != NULL)
        {
            this->addVertice(indice->getInfo());
            indice = indice->getProx();
        }
        indice = g.getG();
        while(indice != NULL)
        {
            indiceA = indice->getPrimerArista();
            while(indiceA != NULL)
            {
                this->addArco(indice->getInfo(), indiceA->getTerminal()->getInfo(), indiceA->getCost());
                indiceA = indiceA->getProx();
            }
            indice = indice->getProx();
        }
    }
}

template <class T, class C>
void Grafo<T,C>::eliminarVertice(T v)
{
    NodoV<T,C>* indice, *verticeAnterior;
    NodoA<T,C>* terminalesIndice, *terminalAnterior;
    bool verticeEncontrado = false;
    bool terminalEncontrado = false;
    bool encontradoAlInicio = false;
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
                encontradoAlInicio = true;
                verticeEncontrado = true;
                verticeAnterior = this->g;
                this->g = this->g->getProx();
                delete verticeAnterior;
            }
            indice = this->g;

            while(indice != NULL and indice->getProx() != NULL) //buscando el nodo anterior al nodo que posee el vertice buscado para eliminar
            {
                if(!verticeEncontrado and indice->getProx()->getInfo() == v)
                {
                    verticeAnterior = indice;
                    verticeEncontrado = true;
                }

                if(indice->getPrimerArista() != NULL and indice->getPrimerArista()->getTerminal()->getInfo() == v) //si el primer terminal apunta al vertice buscado para eliminar
                {
                    terminalesIndice = indice->getPrimerArista();
                    indice->setPrimeraArista(indice->getPrimerArista()->getProx());
                    this->a--;
                    delete terminalesIndice;
                }else
                {
                    while(terminalesIndice != NULL and terminalesIndice->getProx() != NULL and !terminalEncontrado) //buscando el terminal anterior al vertice buscado a eliminar
                    {
                        if(terminalesIndice->getProx()->getTerminal()->getInfo() == v)
                        {
                            terminalAnterior = terminalesIndice;
                            terminalEncontrado = true;
                        }
                        terminalesIndice = terminalesIndice->getProx();
                    }
                }

                if(terminalEncontrado)
                {
                    terminalEncontrado = false;
                    terminalAnterior->setProx(terminalesIndice->getProx()); //aislando el terminal que apunta al nodo buscado para eliminarlo
                    delete terminalesIndice;
                    this->a--;
                }
                indice = indice->getProx();
            }
            if(!encontradoAlInicio) //eliminando el vertice y sus terminales
            {
                indice = verticeAnterior->getProx();
                terminalesIndice = indice->getPrimerArista();
                while(terminalesIndice != NULL) //eliminando todos los terminales del vertice
                {
                    terminalAnterior = terminalesIndice;
                    terminalesIndice = terminalesIndice->getProx();
                    delete terminalAnterior;
                    this->a--;
                }
                verticeAnterior->setProx(indice->getProx()); //aislando el vertice a eliminar
                delete indice;
                this->n--;
            }
        }
    }
}

template <class T, class C>
void Grafo<T,C>::eliminarArco(T v, T w)
{
    NodoV<T,C>* indiceV;
    NodoA<T,C>* terminales, *arista;
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
                        indiceV->setPrimeraArista(terminales->getProx());
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

template <class T, class C>
void Grafo<T,C>::vaciar()
{
    NodoV<T,C> *indiceV, *auxV;
    NodoA<T,C> *indiceA, *auxA;
    indiceV = this->g;
    while(!this->esVacio())
    {
        indiceA = indiceV->getPrimerArista();
        while(indiceA != NULL)
        {
            auxA = indiceA;
            indiceV->setPrimeraArista(indiceA->getProx());
            indiceA = indiceA->getProx();
            delete auxA;
            this->a--;
        }
        auxV = indiceV;
        this->g = indiceV->getProx();
        indiceV = indiceV->getProx();
        delete auxV;
        this->n--;
    }
}

//sobrecarga del operador de impresion
template<class TP,class CP>
std::ostream& operator << (std::ostream& o,const Grafo<TP,CP>&g)
{
    NodoV<TP,CP> *indiceV;
    NodoA<TP,CP> *indiceA;
    if(g.esVacio())
    {
        o << "el grafo a imprimir esta vacio" << std::endl;
    }else
    {
        indiceV = g.getG();
        while(indiceV != NULL)
        {
            o << indiceV->getInfo() << " ";
            indiceA = indiceV->getPrimerArista();
            while(indiceA != NULL)
            {
                o << "C(" << indiceA->getTerminal()->getInfo() << "): " << indiceA->getCost() << " ";
                indiceA = indiceA->getProx();
            }
            indiceV = indiceV->getProx();
            o << std::endl;
        }
    }
    return o;
}

//destructor
template <class T,class C>
Grafo<T,C>::~Grafo()
{
    this->vaciar();
}
#endif // GRAFO_H
