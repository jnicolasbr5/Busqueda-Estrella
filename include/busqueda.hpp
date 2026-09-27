#pragma once

#include "mapa.hpp"
#include "auxiliar.hpp"

#include <list>
#include <set>

class Busqueda {
    private: 
        Mapa mapa_;
        std::set<Nodo*> abiertos = {};
        std::vector<Nodo*> cerrados = {};

        int funcionHeuristica(int r, int c) const;
        Nodo* crearNodo(int x, int y, int casilla, Nodo* n=nullptr);
        void iniciarBusqueda();
        void addNodosAbiertos(Nodo *n);

    public: 
        Busqueda(std::ifstream& file);
        void mostrarDatos(int it);
        void mostrarSolucion(Nodo *n);
        
        void run();

};