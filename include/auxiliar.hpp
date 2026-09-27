#include "busqueda.hpp"
class Busqueda;

struct Nodo {
    int x, y; // Posiciones
    int f, g, h; // Costes
    Nodo *padre = nullptr;

    bool operator<(const Nodo* otro) const {
        if (f != otro->f) return  f < otro->f;
        if (x != otro->x) return x < otro->x;
        return y < otro->y;  
    }

    void actualizarCostes(int estimacion) {
        this->h = estimacion;   
        this->f = this->h + g;
    }

    Nodo(int x, int y, int casilla, Nodo *padre = nullptr) : x(x), y(y), padre(padre) {
        // Si es el nodo inicial, no tendrá coste acumulado
        if (padre == nullptr) this->g = 0; 

        // Si tiene un nodo padre, g es la suma del coste acumulado del padre y el valor de la casilla
        else this->g = padre->g + casilla;
    }
};

struct Coordenada {
    int x, y;
};