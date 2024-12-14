//
// Created by tubac on 9/12/2024.
//
#include "../../includes/MatrizDispersa/NodoMatriz.h"

NodoMatriz::NodoMatriz(std::string cabecera) {
    this->cabecera = cabecera;
    this->valor = nullptr;

    this->siguiente = nullptr;
    this->anterior = nullptr;

    this->arriba = nullptr;
    this->abajo = nullptr;

    this->adelante = nullptr;
    this->atras = nullptr;
}



NodoMatriz::NodoMatriz(Usuarios* valor) {
    this->valor = valor;
    this->cabecera = "";

    this->siguiente = nullptr;
    this->anterior = nullptr;

    this->arriba = nullptr;
    this->abajo = nullptr;

    this->adelante = nullptr;
    this->atras = nullptr;
}


