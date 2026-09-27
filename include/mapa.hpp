#pragma once

#include "auxiliar.hpp"

#include <fstream>
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
        int estadoCasilla(int r, int c) const;
        Coordenada getFin() const {return fin_;};
};