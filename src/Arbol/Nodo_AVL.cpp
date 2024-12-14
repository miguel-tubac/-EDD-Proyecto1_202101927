//
// Created by tubac on 12/12/2024.
//
#include "../../includes/Arbol/Nodo_AVL.h"

Nodo_AVL::Nodo_AVL(std::string id,Activos *activo) {
    this->id = id;
    this->activo = activo;
    this->izq = nullptr;
    this->der = nullptr;
    this->factorEq = 0; //Inicializamos el factor de equilibro a cero ya que es el valor estandar
}

