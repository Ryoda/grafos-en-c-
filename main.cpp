#include <iostream>
#include <Grafo.hpp>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main()
{
    srand(time(NULL));
    Grafo<int> g;
    for(int i = 1; i < 10; i++)
        g.addVertice(i);
    for(int i = 0; i < 20; i++)
        g.addArco(rand() % 9 + 1, rand() % 9 + 1);

    cout << "Hello world!" << endl;
    cout << g;
    cout << "vertices: " << g.cantidadDeVertices() << endl;
    cout << "aristas: " << g.cantidadDeAristas() << endl;
    int test = rand() % 9 + 1;
    cout << "sucesores de " << test << ": " << g.sucesores(test) << endl;
    cout << "predecesores de " << test << ": " << g.predecesores(test) << endl;
    cout << "dfs: " << g.dfs() << endl;
    return 0;
}
