#pragma once

struct Nodo {
    int x, y; // Posiciones
    int f, g, h; // Costes
    Nodo *padre = nullptr;


    /**
     * @brief Actualiza los costes h y f
     * 
     * @param estimacion Coste de la función heurística
     */
    void actualizarCostes(int estimacion) {
        this->h = estimacion;   
        this->f = this->h + g;
    }


    /**
     * @brief Construye el nodo
     * 
     * @param x Nº fila
     * @param y Nº columna
     * @param casilla Estado casilla
     * @param padre Puntero del nodo padre
     */
    Nodo(int x, int y, int casilla, Nodo *padre = nullptr) : x(x), y(y), padre(padre) {
        // Si es el nodo inicial, no tendrá coste acumulado
        if (padre == nullptr) this->g = 0; 

        // Si llegas al final, la última casilla vale 2
        else if (casilla == 10) this->g = padre->g + 2;

        // Si tiene un nodo padre, g es la suma del coste acumulado del padre y el valor de la casilla
        else this->g = padre->g + casilla;
    }
};

struct Coordenada {
    int x, y;
};


/**
 * @brief Compara los nodos, primero por f, después por h y finalmente por coordenadas
 * 
 */
struct CompararNodos {
    bool operator()(const Nodo* a, const Nodo* b) const {
        if (a->f != b->f) return a->f < b->f;
        if (a->h != b->h) return a->h < b->h;
        if (a->x != b->x) return a->x < b->x;
        return a->y < b->y;
    }
};