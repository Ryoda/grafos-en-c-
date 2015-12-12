
#ifndef LISTA_H
#define LISTA_H

using namespace std;

#ifndef NODO_H
#define NODO_H
template<class T>
class Nodo
{
    private:
        T datos;
        Nodo<T> *siguiente;
    public:
        Nodo(T datos = 0, Nodo<T> *siguiente = NULL){ this->datos = datos; this->siguiente = siguiente;};
        T getDatos() const {return(this->datos);}
        Nodo<T>* getSiguiente() const { return (this->siguiente);}
        void setDatos(T datos) { this->datos = datos;};
        void setSiguiente(Nodo<T>* siguiente) { this->siguiente = siguiente;};
};
#endif // NODO_H

// Metodos de la clase Nodo

template <class T>
class Lista
{
    private:
        Nodo<T> *inicio, *fin;
        int longitud;
    public:
        Lista(Nodo<T> *inicio = NULL, Nodo<T>* fin = NULL, int longitud = 0){ this->inicio = inicio; this->fin = fin; this->longitud = longitud;};
        Lista(Nodo<T> *origen);
        Lista(Lista<T> const & origen);
        Lista<T>& operator=(Lista<T> const& origen);
        Lista<T>& operator=(Nodo<T>* origen);
        ~Lista();
        Nodo<T>* getInicio() const { return (this->inicio);};
        Nodo<T>* getFin() const {return this->fin;};
        int getLongitud() const { return (this->longitud);};
        T consultar(int posicion) const;
        T consultarAlFinal() const;
        bool esVacia() const { return (this->longitud == 0); };
        void subLista(Lista<T>& destino, int i, int j) const;
        void concatenar(Lista<T> lista);
        int localizar(T elem) const ;
        void insertar(T datos,int posicion);
        void agregar(T datos);
        void eliminar(int posicion);
        void reestablecer();
        void concatenar(const Lista<T>& lista);
        void invertir();
        void ordenar();
        template <class ST>
        friend ostream& operator<<(ostream& os, const Lista<ST>& l);
};


//Metodos de la clase Lista

template<class T>
Lista<T>::Lista(Lista<T> const & origen)
{
    Nodo<T>* nodoOrigen, *nodoDestino;

    nodoOrigen = origen.getInicio();
    this->longitud = origen.getLongitud();
    if(!origen.esVacia())
    {
        nodoDestino = new Nodo<T>;
        nodoDestino->setDatos(nodoOrigen->getDatos());
        this->inicio = nodoDestino;
        this->fin = nodoDestino;
        nodoOrigen = nodoOrigen->getSiguiente();
        while(nodoOrigen != NULL)
        {
            nodoDestino = new Nodo<T>;
            this->fin->setSiguiente( nodoDestino );
            nodoDestino->setDatos(nodoOrigen->getDatos());
            this->fin = this->fin->getSiguiente();
            nodoOrigen = nodoOrigen->getSiguiente();
        }
        this->fin->setSiguiente(NULL);
    }

}

template<class T>
Lista<T>::Lista(Nodo<T> *origen)
{
    Nodo<T> *aux;

    if(origen != NULL)
    {
        while(origen != NULL)
        {
            this->insertar(origen->getDatos());
            origen = origen->getSiguiente();
        }
    }

}

template<class T>
Lista<T>& Lista<T>::operator = (const Lista<T>& origen)
{
    Nodo<T>* pOrigen;
    if(!this->esVacia())
    {
        this->reestablecer();
    }
    if(!origen.esVacia())
    {
      pOrigen = origen.getInicio();
      this->agregar(pOrigen->getDatos());
      pOrigen = pOrigen->getSiguiente();
      while(pOrigen != NULL)
      {
          this->agregar(pOrigen->getDatos());
          pOrigen = pOrigen->getSiguiente();
      }
    }
    return *this;
}

template<class T>
Lista<T>& Lista<T>::operator=(Nodo<T>* origen)
{
    if(!this->esVacia())
    {
        this->reestablecer();
    }
    while(origen != NULL)
    {
      this->agregar(origen->getDatos());
      origen = origen->getSiguiente();
    }
    return *this;
}


template<class T>
Lista<T>::~Lista()
{
    //dtor
    this->reestablecer();
}

template<class T>
void Lista<T>::reestablecer()
{
    if(!this->esVacia())
    {
        while(!this->esVacia())
        {
            this->eliminar();
        }
    }
}

template <class T>
T Lista<T>::consultar(int posicion = 1) const
{
    Nodo<T> *indice;
    if(posicion < 1 || posicion > this->longitud)
    {
        if((posicion < 1 || posicion > this->longitud) && !this->esVacia())
            std::cout << "Error: Lista::consultar(): posicion fuera de rango" << std::endl;
        if(this->esVacia())
            std::cout << "Error: Lista::consultar(): la lista esta vacia" << std::endl;
    }else
    {
        if(posicion == this->longitud)
        {
            indice = this->fin;
        }else
        {
            indice = this->inicio;

            for(int i = 1; i < posicion; i++)
            {
                indice = indice->getSiguiente();
            }
        }
    }


    return(indice->getDatos());

}

template <class T>
T Lista<T>::consultarAlFinal() const
{
    return (this->consultar(this->longitud));
}

template <class T>
int Lista<T>::localizar(T elem) const
{
    Nodo<T>* aux = this->inicio;
    int pos = 0;

    while(aux != NULL && aux->getDatos() != elem)
    {
        aux = aux->getSiguiente();
        pos++;
    }
    if(aux == NULL)
    {
        pos = -1;
    }
    return (pos);
}

template <class T>
void Lista<T>::insertar(T datos, int posicion = 1)
{
    Nodo<T> *aux = new Nodo<T>(datos);
    Nodo<T> *indice;
    if(this->longitud + 1 <  posicion || posicion <= 0)
    {
        cout << "error, se intento agregar un elemento en la lista en una posicion inexistente" << endl;
    }else
    {
        if(this->esVacia())
        {
            this->inicio = aux;
            this->fin = aux;
        }else
        {
            if(posicion == 1)
            {
                aux->setSiguiente(this->inicio);
                this->inicio = aux;
            }else
            {
                if(posicion == this->longitud + 1)
                {
                    this->fin->setSiguiente(aux);
                    this->fin = aux;
                }else
                {
                    indice = this->inicio;
                    for(int i = 1; i < posicion - 1; i++)
                    {
                        indice = indice->getSiguiente();
                    }
                    aux->setSiguiente(indice->getSiguiente());
                    indice->setSiguiente(aux);
                }
            }
        }
        this->longitud++;
    }
}

template <class T>
void Lista<T>::agregar(T datos)
{
    this->insertar(datos, this->getLongitud() + 1);
}

template<class T>
void Lista<T>::eliminar(int posicion = 1)
{
    Nodo<T> *aux, *indice;
    if(this->longitud <  posicion || posicion <= 0)
    {
        if(this->longitud < posicion && !this->esVacia())
            std::cout << "error, Lista::eliminar(): posicion fuera de rango" << endl;
        if(this->esVacia())
            std::cout << "error, Lista::eliminar(): la lista esta vacia" << endl;
    }else
    {


        if(posicion == 1)
        {
            aux = this->inicio;
            this->inicio = this->inicio->getSiguiente();
        }else
        {
            indice = this->inicio;
            for(int i = 1; i < posicion - 1; i++)
            {
                indice = indice->getSiguiente();
            }
            aux = indice->getSiguiente();
            indice->setSiguiente(aux->getSiguiente());
        }
        delete aux;
        if(this->getLongitud() == 1)
        {
            this->fin = NULL;
        }
        this->longitud--;
    }
}

template<typename ST>
ostream& operator<<(ostream& os, const Lista<ST>& l)
{
	Nodo<ST>* aux = l.getInicio();
	if(!l.esVacia())
    {
        while(aux != NULL)
        {
            os << (aux->getDatos()) << " ";
            aux = aux->getSiguiente();
        }
    }else
    {
        os << "Lista a imprimir vacia ";
    }

	return os;
}

template <class T>
void Lista<T>::invertir()
{
    Nodo<T>* base, *origen, *siguiente, *inverso;
    if(this->getLongitud() > 1)
    {
            base = this->getInicio();
            origen = this->getInicio();
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
            this->fin = origen;
            this->inicio = inverso;
    }

}

template <class T>
void Lista<T>::concatenar(Lista<T> lista) /* se le pasa una copia de la lista original para que no sea destruida al hacer "eliminar" */
{
  while(!lista.esVacia())
  {
        this->agregar(lista->consultar());
        lista->eliminar();
  }
}

template <class T>
void Lista<T>::ordenar() //MergeSort
{
    Nodo<T>* cabezeraI, *cabezeraD, *elemento;
    int longitudActual, mezclas, longitudI, longitudD, i;
    bool faltanMezclas = true;
    cabezeraI = this->getInicio();
    if(cabezeraI != NULL)
    {
        longitudActual = 1;
        while(faltanMezclas)
        {
            cabezeraI = this->getInicio();
            this->inicio = NULL;
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
                        this->inicio = elemento;
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

/*
 * This file is copyright 2001 Simon Tatham.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL SIMON TATHAM BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

}

template <class T>
void Lista<T>::subLista(Lista<T>& destino,int i, int j) const
{
    Nodo<T> *pOrigen;
    int contador = 1;
    if(!destino.esVacia())
    {
        destino.reestablecer();
    }

    if(j <= this->getLongitud() && i <= j)
    {
        pOrigen = this->getInicio();
        while(contador < i)
        {
            pOrigen = pOrigen->getSiguiente();
            contador++;
        }
        while(contador <= j && j <= this->getLongitud())
        {
            destino.agregar(pOrigen->getDatos());
            pOrigen = pOrigen->getSiguiente();
            contador++;
        }
    }
}

#endif // LISTA_H
