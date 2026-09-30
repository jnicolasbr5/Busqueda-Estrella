#include "busqueda.hpp"
#include "mapa.hpp"

#include <fstream>
#include <print>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::println("Uso: ./busqueda <fichero_entrada>");
        return 1;
    }
    std::ifstream file(argv[1]);
    Busqueda busqueda(file);
    std::ofstream iteraciones("../iteraciones.txt");
    busqueda.run(iteraciones);
    std::ofstream salida_mapa("../output.txt");
    busqueda.mapa_.imprimir(salida_mapa);
    busqueda.mapa_.imprimirColor(std::cout);
    return 0;
}