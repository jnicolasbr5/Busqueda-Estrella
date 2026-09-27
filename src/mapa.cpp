#include "mapa.hpp"

#include <iostream>
#include <sstream>
#include <vector>

Mapa::Mapa(std::ifstream& file) {
    std::string fila;
    int i = 0, j = 0, numero;
    while (std::getline(file, fila)) {
        j = 0;
        std::stringstream ss(fila);
        std::vector<int> vec = {};
        while (ss >> numero) {
            if (numero == 0) {
                inicio_.x = i; inicio_.y = j;
            }   else if (numero == 10) {
                fin_.x = i; fin_.y = j;
            }
            vec.push_back(numero);
            j++;
        }
        matrix_.push_back(vec);
        i++;
    }   
}

int Mapa::estadoCasilla(int r, int c) const {
    if (r < 0 || c < 0) return -1;
    if (r >= matrix_.size() || c >= matrix_[0].size()) return -1;

    // Si la casilla existe en el mapa
    return matrix_[r][c];
}