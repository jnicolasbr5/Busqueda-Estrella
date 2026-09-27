#include "busqueda.hpp"
#include "mapa.hpp"

#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    Busqueda busqueda(file);
    busqueda.run();
    
    return 0;
}