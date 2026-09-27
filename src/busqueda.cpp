#include "busqueda.hpp"
#include "auxiliar.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <print>

Busqueda::Busqueda(std::ifstream& file) : mapa_(file), robot_(), coste_(0) {}

void Busqueda::mostrarDatos(int it) {
    std::println("Iteración {}", it);
    std::println("-----------");
    
    // Mostrar nodos abiertos
    std::print("Abiertos = ");
    for (int i = 0; i < conjunto_abiertos.size(); i++) {
        std::print("({}, {})", conjunto_abiertos[i].x, conjunto_abiertos[i].y);
        if (i != conjunto_abiertos.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    // Mostrar nodos cerrados
    std::print("Cerrados = ");
    for (int j = 0; j < conjunto_cerrados.size(); j++) {
        std::print("({}, {})", conjunto_cerrados[j].x, conjunto_cerrados[j].y);
        if (j != conjunto_cerrados.size() - 1) std::cout << ", ";
    }
    std::cout << "\n";

    std::println("------------------------");
}

void Busqueda::mostrarSolucion() {
    std::print("\nCamino: ");
    for (int i = 0; i < conjunto_cerrados.size(); i++) {
        std::print("({}, {})", conjunto_cerrados[i], conjunto_cerrados[j]);
        if (i != conjunto_cerrados.size() - 1) std::print(" -> ");
    }

    std::println("\nCoste: {}", coste_);
}

int Busqueda::funcionHeuristica(int r, int c) {
    return 2 * (std::abs(mapa_.getFin().x - r) + std::abs(mapa_.getFin().y - c));
}

int Busqueda::valorEstado(int r, int c) {
    return cerrados.back().coste_total + funcionHeuristica(r, c);
}

bool Busqueda::nodoAdyacente(int r, int c) {
    if (std::abs(r - robot_.getPos().x) + std::abs(c - robot_.getPos().y) == 1) return true;
    return false;
}

void Busqueda::run() {
    robot_.setInicio(mapa_.getPosInicial());
    abiertos.emplace_back({{mapa_.getPosInicial()}, 0});
    int it = 0;
    mostrarDatos(it);
    
    while (true) {
        it++;

        // Tomo la posición del robot
        int x = robot_.getPos().x, y = robot_.getPos().y;

        // Añado la posición del robot a la secuencia
        cerrados.push_back({x, y}, ); 

        // Añadir los nodos abiertos
        if (mapa_.estadoCasilla(x, y + 1) > 0) { // Derecha
            abiertos.push_back({x, y + 1}, );
        }

        if (mapa_.estadoCasilla(x + 1, y) > 0) { // Abajo
            abiertos.push_back({x + 1, y}, );
        }

        if (mapa_.estadoCasilla(x, y - 1) > 0) { // Izquierda
            abiertos.push_back({x, y - 1}, );
        }

        if (mapa_.estadoCasilla(x - 1, y) > 0) { // Arriba
            abiertos.push_back({x - 1, y}, );
        }

        // Mostrar la iteración
        mostrarDatos(it);

        // Calcular el mejor nodo al que desplazarse
        int mejor_valor = 64;
        Coordenada prox_nodo = {-1, -1};
        std::multimap<int, Coordenada> nodos;
        for (int i = 0; i < conjunto_abiertos.size(); i++) {

            // Si el robot puede desplazarse a ese nodo
            if (nodoAdyacente(conjunto_abiertos[i].x, conjunto_abiertos[i].y)) {
                int estimacion = valorEstado(conjunto_abiertos[i].x, conjunto_abiertos[i].y);
                if (estimacion <= mejor_valor) {
                    nodos.insert({mejor_valor, conjunto_abiertos[i]});
                    mejor_valor = estimacion;
                } else {
                    // Elimina el nodo del conjunto abierto
                    conjunto_abiertos.erase(conjunto_abiertos.begin() + i);
                }
            }
        }
    }

    mostrarSolucion();
}