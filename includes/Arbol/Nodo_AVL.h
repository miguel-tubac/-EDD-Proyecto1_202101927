//
// Created by tubac on 12/12/2024.
//

#ifndef NODO_ABL_H
#define NODO_ABL_H

#include "../Clases/Activos.h"

class Nodo_AVL {
public:

    //int valor;
    std::string id;
    Activos *activo;

    int factorEq;
    Nodo_AVL *izq;
    Nodo_AVL *der;

    Nodo_AVL(std::string id, Activos *activo);
};


//Faltan los geters y seters

#endif //NODO_ABL_H
