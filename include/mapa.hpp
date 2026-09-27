#pragma once

#include "auxiliar.hpp"

#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matriz;

class Mapa {

    private:
        Matriz matrix_ = {};
        std::vector<std::vector<bool>> visitados = {};
        Coordenada inicio_;
        Coordenada fin_;

    public:
        Mapa(std::ifstream& file);
        Coordenada getPosInicial() const {return inicio_;}
        Coordenada getFin() const {return fin_;};
        int estadoCasilla(int r, int c) const;
        void nodoRecorrido(int r, int c);
        bool estadoVisitado(int r, int c) const;
        void nodoVisitado(int r, int c);

        void imprimir(std::ostream& os) const;
        void imprimirColor(std::ostream& os) const;
};