#pragma once

#include "robot.hpp"
#include "mapa.hpp"
#include "auxiliar.hpp"

#include <list>

class Busqueda {
    private: 
        Mapa mapa_;
        Robot robot_;
        std::list<Nodo> abiertos = {};
        std::list<Nodo> cerrados = {};
        int funcionHeuristica(int r, int c);
        bool nodoAdyacente(int r, int c);
        int valorEstado(int r, int c);

    public: 
        Busqueda(std::ifstream& file);
        void mostrarDatos(int it);
        void mostrarSolucion();
        
        void run();

};