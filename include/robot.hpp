#pragma once

#include "auxiliar.hpp"

class Robot {    
    private:
    Coordenada pos_;

    public:
        Robot() : pos_{0 , 0} {}
        void setInicio(Coordenada pos) {pos_ = pos;}
        Coordenada getPos() {return pos_;}
        void avanzar_izq();
        void avanzar_der();
        void avanzar_arriba();
        void avanzar_abajo();
};