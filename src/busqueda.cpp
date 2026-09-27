#include "busqueda.hpp"
#include "auxiliar.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <print>

Busqueda::Busqueda(std::ifstream& file) : mapa_(file) {}

void Busqueda::mostrarDatos(int it) {
    std::println("Iteración {}", it);
    std::println("-----------");
    
    // Mostrar nodos abiertos
    std::print("Abiertos = ");
    size_t i = 0;
    for (const auto& nodo : abiertos) {
        std::print("({}, {})", nodo->x, nodo->y);
        if (++i != abiertos.size()) std::print(", ");
    }
    std::cout << "\n";

    // Mostrar nodos cerrados
    std::print("Cerrados = ");
    for (int j = 0; j < cerrados.size(); j++) {
        std::print("({}, {})", cerrados[j]->x, cerrados[j]->y);
        if (j != cerrados.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    std::println("------------------------\n");
}

void Busqueda::mostrarSolucion(Nodo *n) {
    std::print("\nCamino: ");
    std::vector<Coordenada> vec = {};
    int coste = n->f;
    while (n != nullptr) {
        vec.push_back({n->x, n->y});
        mapa_.nodoRecorrido(n->x, n->y);
        n = n->padre;
    }

    for (int i = vec.size() - 1; i >= 0; i--) {
        std::print("({}, {})", vec[i].x, vec[i].y);
        if (i != 0) std::print(" -> ");
    }

    std::println("\nCoste: {}\n", coste);
}

// Calcula la función heurística h(s)
int Busqueda::funcionHeuristica(int r, int c) const {
    return 2 * (std::abs(mapa_.getFin().x - r) + std::abs(mapa_.getFin().y - c));
}

Nodo* Busqueda::crearNodo(int x, int y, int casilla, Nodo* n) {
    // Creo el nodo en el heap
    Nodo *nodo = new Nodo(x, y, casilla, n);

    // Obtengo la estimación del nodo y actualizo los costes
    int h = funcionHeuristica(x, y);
    nodo->actualizarCostes(h);
    return nodo;
}

void Busqueda::iniciarBusqueda() {
    int x = mapa_.getPosInicial().x, y = mapa_.getPosInicial().y;
    Nodo *inicial = crearNodo(x, y, mapa_.estadoCasilla(x, y));
    abiertos.insert(inicial);
    mapa_.nodoVisitado(x, y);
    mostrarDatos(0);
}

void Busqueda::addNodosAbiertos(Nodo *n) {
    // Derecha, arriba, izquierda, abajo
    const int filas[] = {0, 1, 0, -1};
    const int columnas[] = {1, 0, -1, 0};

    for (int i =  0; i < 4; i++) {
        const int x = n->x + filas[i];
        const int y = n->y + columnas[i];
        int casilla = mapa_.estadoCasilla(x, y);

        // Si la casilla no es un obstáculo o no está fuera del mapa
        if (casilla > 0) {

            // Si el nodo no ha sido explorado
            if (mapa_.estadoVisitado(x, y) == false) {
                if (n->padre == nullptr ||n->padre->x != x || n->padre->y != y) {
                    Nodo *nuevo_nodo = crearNodo(x, y, casilla, n);
                    abiertos.insert(nuevo_nodo);
                    mapa_.nodoVisitado(x, y);
                }
            }
        }
    }
}

void Busqueda::run() {
    // Nodo inicial
    iniciarBusqueda();
    int i = 1;

    while (true) {
        if (abiertos.empty()) {
            std::println("\nNo se ha podido encontrar ningún camino.");
            return;
        }

        // Se visita el nodo con mejor función
        auto it = abiertos.begin();
        Nodo *aux = *it;
        abiertos.erase(it);
        cerrados.push_back(aux);
        std::println("Nodo elegido: ({}, {})", aux->x, aux->y); 

        // Comprobar si es el nodo final
        if (aux->h == 0)    {
            mostrarSolucion(aux);
            return;
        }     

        // Añadir los nodos abiertos
        addNodosAbiertos(aux);

        // Mostrar cada iteración
        mostrarDatos(i);
        i++;

    }
}