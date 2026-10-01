#include "busqueda.hpp"
#include "auxiliar.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <print>


Busqueda::Busqueda(std::ifstream& file) : mapa_(file) {}


/**
 * @brief Muestra el conjuntos de nodos abiertos y cerrados en cada iteración
 * 
 * @param it Nº iteración
 * @param os Archivo al que se envian los datos (os.txt)
 */
void Busqueda::mostrarConjuntos(int it, std::ostream& os) {
    os << "Iteración " << it << "\n";
    os << "-----------\n";

    // Mostrar nodos abiertos
    os << "Abiertos = ";
    size_t i = 0;
    for (const auto& nodo : abiertos) {
        os << "(" << nodo->x << ", " << nodo->y << ")";
        if (++i != abiertos.size()) os << ", ";
    }
    os << "\n";

    // Mostrar nodos cerrados
    os << "Cerrados = ";
    for (int j = 0; j < cerrados.size(); j++) {
        os << "(" << cerrados[j]->x << ", " << cerrados[j]->y << ")";
        if (j != cerrados.size() - 1) os << ", ";
    }
    os << "\n";

    os << "------------------------\n\n";
}


/**
 * @brief Muestra el camino final y su coste 
 * 
 * @param n Nodo final
 * @param os Archivo al que se enviarán los datos (output.txt)
 */
void Busqueda::mostrarSolucion(Nodo *n, std::ostream& os) {
    os << "-----¡CAMINO ENCONTRADO!-----\n";
    std::cout << "\n---¡CAMINO ENCONTRADO!---";
    os << "\nCamino: ";
    std::vector<Coordenada> vec = {};
    int coste = n->f;
    while (n != nullptr) {
        vec.push_back({n->x, n->y});
        mapa_.nodoRecorrido(n->x, n->y);
        n = n->padre;
    }

    for (int i = vec.size() - 1; i >= 0; i--) {
        os << "(" << vec[i].x << ", " << vec[i].y << ")";
        if (i != 0) os << " -> ";
    }

    os << "\nCoste: " << coste << "\n";
}


/**
 * @brief Calcula la función heurística h(s) = 2 * (|rf - ri| + |cf - cj|)
 * 
 * @param r Nº fila
 * @param c Nº columna
 * @return int Valor de la función heurística en esa posición
 */
int Busqueda::funcionHeuristica(int r, int c) const {
    return 2 * (std::abs(mapa_.getFin().x - r) + std::abs(mapa_.getFin().y - c));
}


/**
 * @brief Crea el nodo dada la posición y el estado
 * 
 * @param x Nº fila 
 * @param y Nº columna 
 * @param casilla Estado casilla
 * @param n Nodo padre
 * @return Nodo* Devuelve un puntero del nodo nuevo
 */
Nodo* Busqueda::crearNodo(int x, int y, int casilla, Nodo* n) {
    // Creo el nodo en el heap
    Nodo *nodo = new Nodo(x, y, casilla, n);

    // Obtengo la estimación del nodo y actualizo los costes
    int h = funcionHeuristica(x, y);
    nodo->actualizarCostes(h);
    return nodo;
}


/**
 * @brief Ejecuta la primera iteración- Añade el nodo inicial en 
 * 
 * @param os Fichero de salida donde se mostrará la primera iteración
 */
void Busqueda::iniciarBusqueda(std::ostream& os) {
    int x = mapa_.getPosInicial().x, y = mapa_.getPosInicial().y;
    int xf = mapa_.getFin().x, yf = mapa_.getFin().y;
    std::println("Inicio: ({}, {}), Fin: ({}, {})", x, y, xf, yf);

    // Creo el nodo inicial y lo añado al conjunto de abiertos
    Nodo *inicial = crearNodo(x, y, mapa_.estadoCasilla(x, y));
    abiertos.insert(inicial);
    mapa_.nodoVisitado(x, y);
    mostrarConjuntos(0, os);
}


/**
 * @brief Añade los nodos que no han sido explorados al conjunto de abiertos 
 * 
 * @param n Puntero del nodo que se está ejecutando
 */
void Busqueda::addNodosAbiertos(Nodo *n) {
    // Derecha, abajo, izquierda, arriba
    const int filas[] = {0, 1, 0, -1};
    const int columnas[] = {1, 0, -1, 0};

    for (int i =  0; i < 4; i++) {
        // Obtengo los datos de los posibles nuevos nodos
        const int x = n->x + filas[i];
        const int y = n->y + columnas[i];
        int casilla = mapa_.estadoCasilla(x, y);

        // Si la casilla no es un obstáculo o no está fuera del mapa, y la casilla no ha sido explorada
        if (casilla > 0 && !mapa_.estadoVisitado(x, y)) {
            Nodo *nuevo_nodo = crearNodo(x, y, casilla, n);
            abiertos.insert(nuevo_nodo);
            mapa_.nodoVisitado(x, y);
        }
    
    }
}


/**
 * @brief Ejecuta el algoritmo
 * 
 * @param os Archivo salida (iteraciones)
 */
void Busqueda::run(std::ostream& os) {
    // Nodo inicial
    iniciarBusqueda(os);
    int i = 1;

    while (true) {
        // Si el conjunto de abiertos está vacío, no existe ningún
        if (abiertos.empty()) {
            std::println("\nNo se ha podido encontrar ningún camino.");
            os << "\nNo se ha podido encontrar ningún camino.\n";
            return;
        }

        // Se visita el nodo con mejor función
        auto it = abiertos.begin();
        Nodo *aux = *it;
        abiertos.erase(it);
        cerrados.push_back(aux);

        // Comprobar si es el nodo final
        if (aux->h == 0)    {
            mostrarSolucion(aux, os);
            return;
        }     

        // Añadir los nodos abiertos
        addNodosAbiertos(aux);

        // Mostrar cada iteración
        mostrarConjuntos(i, os);
        i++;

    }
}