#pragma once

#include "mapa.hpp"
#include "auxiliar.hpp"

#include <fstream>
#include <set>
#include <vector>

class Busqueda {
    private: 
        std::set<Nodo*, CompararNodos> abiertos = {};
        std::vector<Nodo*> cerrados = {};

        int funcionHeuristica(int r, int c) const;
        Nodo* crearNodo(int x, int y, int casilla, Nodo* n=nullptr);
        void iniciarBusqueda();
        void addNodosAbiertos(Nodo *n);

    public: 
        Mapa mapa_;
        Busqueda(std::ifstream& file);
        void mostrarDatos(int it);
        void mostrarSolucion(Nodo *n);
        
        void run();

};