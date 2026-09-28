#pragma once

#include "mapa.hpp"
#include "auxiliar.hpp"

#include <fstream>
#include <iostream>
#include <set>
#include <vector>

class Busqueda {
    private: 
        std::set<Nodo*, CompararNodos> abiertos = {};
        std::vector<Nodo*> cerrados = {};

        int funcionHeuristica(int r, int c) const;
        Nodo* crearNodo(int x, int y, int casilla, Nodo* n=nullptr);
        void iniciarBusqueda(std::ostream& os);
        void addNodosAbiertos(Nodo *n);

    public: 
        Mapa mapa_;
        Busqueda(std::ifstream& file);
        void mostrarConjuntos(int it, std::ostream& os);
        void mostrarSolucion(Nodo *n, std::ostream& os);
        
        void run(std::ostream& os);
};