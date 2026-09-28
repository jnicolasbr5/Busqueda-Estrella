#include "busqueda.hpp"
#include "mapa.hpp"

#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    Busqueda busqueda(file);
    std::ofstream iteraciones("../iteraciones.txt");
    busqueda.run(iteraciones);
    std::ofstream salida_mapa("../output.txt");
    busqueda.mapa_.imprimir(salida_mapa);
    busqueda.mapa_.imprimirColor(std::cout);
    return 0;
}