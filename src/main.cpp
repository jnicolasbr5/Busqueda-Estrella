#include "busqueda.hpp"
#include "mapa.hpp"

#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    Busqueda busqueda(file);
    busqueda.run();
    std::ofstream salida("../output.txt");
    busqueda.mapa_.imprimir(salida);
    busqueda.mapa_.imprimirColor(std::cout);
    return 0;
}