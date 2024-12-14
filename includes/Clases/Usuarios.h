//
// Created by tubac on 10/12/2024.
//

#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include <iostream>
#include "../Arbol/ClassAVL.h"

class Usuarios {
    public:
    std::string usuar;
    std::string nombre;
    std::string pasword;
    ClassAVL *arbol;

    Usuarios(std::string usuar, std::string nombre, std::string pasword, ClassAVL *arbol);
};



#endif //USUARIOS_H
