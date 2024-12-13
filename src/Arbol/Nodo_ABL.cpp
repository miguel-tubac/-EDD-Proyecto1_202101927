//
// Created by tubac on 12/12/2024.
//
#include "../../includes/Arbol/Nodo_ABL.h"

Nodo_AVL::Nodo_AVL(int valor) {

    this->valor = valor;
    this->izq = nullptr;
    this->der = nullptr;
    this->factorEq = 0; //Inicializamos el factor de equilibro a cero ya que es el valor estandar
}

