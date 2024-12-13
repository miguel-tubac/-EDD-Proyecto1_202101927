#include "../../includes/Clases/Usuarios.h"
#include "../../includes/Arbol/ClassABL.h"
//
// Created by tubac on 10/12/2024.
//
Usuarios::Usuarios(std::string usuar, std::string nombre, std::string pasword, ClassABL* arbol) {
    this->usuar = usuar;
    this->pasword = pasword;
    this->nombre = nombre;
    this->arbol = arbol;
}

