#include<iostream>
#include "Nodo.hpp"
//---------------------------------------- COLA --------------------------------------------------
#ifndef COLA_H
#define COLA_H

//la estructura cola depende de la estructura Nodo

template <class T>
class Cola
{
    private:
        Nodo<T>* frente, *fin;
        int cantidad;
    public:
        Cola(Nodo<T>* frente = NULL, Nodo<T>*fin = NULL,int cantidad = 0){ this->frente = frente; this->fin = fin ;this->cantidad = cantidad;};
        Cola<T>& operator= (Cola<T>& c) {Nodo<T> *aux; this->~Cola(); aux = c.getFrente(); while(aux != NULL){ this->encolar(aux->getDatos()); aux = aux->getSiguiente(); } return *this;};
        bool esVacia() const { return cantidad == 0; };
        T getFrente() const { return this->frente->getDatos();}
        T getFin() const {T aux = -1; if(!esVacia()){ aux = this->frente->getDatos(); }else{ cout << "getFin():la cola esta vacia";} return(aux);};
        int getCantidad() const {return(this->cantidad);};
        void reestablecer(){ while(!this->esVacia()){ this->desencolar(); }};
        void encolar(T elem); //implementacion abajo
        void desencolar();  //implementacion abajo
        void invertir();
        void ordenar();
        ~Cola() {this->reestablecer();};
        template <class ST>
        friend std::ostream& operator<<(std::ostream& os, const Cola<ST>& c) {Nodo<ST>* aux = c.frente;while(aux != NULL){os << (aux->getDatos()) << " ";aux = aux->getSiguiente();} return(os);};
};

template <class T>
void Cola<T>::encolar(T elem)
{
    Nodo<T>*aux = new Nodo<T>(elem);
    if(this->cantidad == 0)
    {
        this->frente = aux;
        this->fin = aux;
    }else
    {
        this->fin->setSiguiente(aux);
        this->fin = aux;
    }
    this->cantidad++;
}

template <class T>
void Cola<T>::desencolar()
{
    if(cantidad == 0)
    {
        cout << "Error: se intento desencolar una cola que ya esta vacia" << endl;
    }else
    {
        Nodo<T>* aux;
        aux = this->frente;
        this->frente = this->frente->getSiguiente();
        delete aux;
        this->cantidad--;
    }
}

template <class T>
void Cola<T>::invertir()
{
        Nodo<T>* base, *origen, *siguiente, *inverso;
    if(this->getCantidad() > 1)
    {
            base = this->frente;
            origen = this->frente;
            inverso = base->getSiguiente();
            siguiente = inverso->getSiguiente();

            //primera inversion
            inverso->setSiguiente(base);
            base->setSiguiente(siguiente);

            while(origen->getSiguiente() != NULL)
            {
                base = inverso;
                inverso = siguiente;
                siguiente = siguiente->getSiguiente();

                inverso->setSiguiente(base);
                origen->setSiguiente(siguiente);
            }
            this->frente = inverso;
            this->fin = origen;
    }
}

template <class T>
void Cola<T>::ordenar()
{
     Nodo<T>* cabezeraI, *cabezeraD, *elemento;
    int longitudActual, mezclas, longitudI, longitudD, i;
    bool faltanMezclas = true;
    cabezeraI = this->frente;
    if(cabezeraI != NULL)
    {
        longitudActual = 1;
        while(faltanMezclas)
        {
            cabezeraI = this->frente;
            this->frente = NULL;
            this->fin = NULL;
            mezclas = 0;


            while(cabezeraI != NULL)
            {
                mezclas++;
                cabezeraD = cabezeraI;
                longitudI = 0;
                i = 0;
                while(cabezeraD != NULL && i < longitudActual)
                {
                    cabezeraD = cabezeraD->getSiguiente();
                    longitudI++;
                    i++;
                }

                longitudD = longitudActual;

                while(longitudI > 0 || (longitudD > 0 && cabezeraD != NULL))
                {
                    if(longitudI == 0) // si la lista izquierda esta vacia
                    {
                        elemento = cabezeraD;
                        cabezeraD = cabezeraD->getSiguiente();
                        longitudD--;
                    }else
                    {
                        if(longitudD == 0 || cabezeraD == NULL) // si no, si la lista derecha esta vacia
                        {
                            elemento = cabezeraI;
                            cabezeraI = cabezeraI->getSiguiente();
                            longitudI--;
                        }else
                        {
                            if(cabezeraI->getDatos() < cabezeraD->getDatos()) // si no, si el elemento inicial de la lista izquierda es menor al de la derecha
                            {
                                elemento = cabezeraI;
                                cabezeraI = cabezeraI->getSiguiente();
                                longitudI--;
                            }else // si no, entonces elegimos el primer elemento de la lista derecha que es el menor
                            {
                               elemento = cabezeraD;
                               cabezeraD = cabezeraD->getSiguiente();
                               longitudD--;
                            }
                        }
                    }

                    if(this->fin != NULL)
                    {
                        this->fin->setSiguiente(elemento);
                    }else
                    {
                        this->frente = elemento;
                    }
                    this->fin = elemento;

                }
                //ahora p y q se han movido 'longitudActual' de veces
                cabezeraI = cabezeraD;
            }

             this->fin->setSiguiente(NULL);

                if (mezclas <= 1) //si solo hicimos una mezcla, entonces ya termina
                {
                    faltanMezclas = false;
                }else   //si no, el tamanio de las listas se incrementa por dos
                {
                    longitudActual *= 2;
                }
        }
    }else
    {
        cout << "Error: Ordenar(): lista vacia" << endl;
    }

}
#endif // COLA_H
