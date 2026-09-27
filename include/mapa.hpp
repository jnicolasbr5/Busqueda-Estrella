#pragma once

#include "auxiliar.hpp"

#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Matriz;

class Mapa {

    private:
        Matriz matrix_ = {};
        Coordenada inicio_;
        Coordenada fin_;

    public:
        Mapa(std::ifstream& file);
        Coordenada getPosInicial() const {return inicio_;}
        Coordenada getFin() const {return fin_;};
        int estadoCasilla(int r, int c) const;
        void nodoVisitado(int r, int c);

        friend std::ostream& operator<<(std::ostream& os, const Mapa& mapa);
};

std::ostream& operator<<(std::ostream& os, const Mapa& mapa);