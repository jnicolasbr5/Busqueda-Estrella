#include "mapa.hpp"

#include <iomanip>
#include <iostream>
#include <print>
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
        visitados.push_back(std::vector<bool>(vec.size(), false));
        i++;
    }
}

int Mapa::estadoCasilla(int r, int c) const {
    if (r < 0 || c < 0) return -1;
    if (r >= matrix_.size() || c >= matrix_[0].size()) return -1;

    // Si la casilla existe en el mapa
    return matrix_[r][c];
}

void Mapa::nodoRecorrido(int r, int c) {
    matrix_[r][c] = -2;
}

bool Mapa::estadoVisitado(int r, int c) const {
    return visitados[r][c];
}

void Mapa::nodoVisitado(int r, int c) {
    visitados[r][c] = true;
}

void Mapa::imprimir(std::ostream& os) const {
    for (size_t i = 0; i < matrix_.size(); i++) {
        for (size_t j = 0; j < matrix_[0].size(); j++) {
            if (matrix_[i][j] == -2) os  << std::setw(3) << "*"; 
            else os << std::setw(3) << matrix_[i][j];
        }
        os << "\n";
    }
}

void Mapa::imprimirColor(std::ostream& os) const {
    const char* ROJO  = "\033[31m";
    const char* AMARILLO = "\033[33m";
    const char* CIAN = "\033[36m";
    const char* GRIS = "\033[90m";
    const char* RESET = "\033[0m"; 
    os << "\n";
    for (size_t i = 0; i < matrix_.size(); i++) {
        for (size_t j = 0; j < matrix_[0].size(); j++) {
            if (matrix_[i][j] == -2) os << AMARILLO << std::setw(3) << "*" << RESET;
            else if (matrix_[i][j] == -1) os << ROJO << std::setw(3) << "|" << RESET;
            else if (matrix_[i][j] == 5) os << CIAN << std::setw(3) << matrix_[i][j] << RESET;
            else if (matrix_[i][j] == 8) os << GRIS << std::setw(3) << matrix_[i][j] << RESET;
            else os << std::setw(3) << matrix_[i][j];
        }
        os << "\n";
    }
}