//
// Created by tubac on 9/12/2024.
//
#include "../../includes/MatrizDispersa/NodoMatriz.h"

// Inicialización de las variables estáticas
int NodoMatriz::countGroup = 0;
int NodoMatriz::countNode = 0;

NodoMatriz::NodoMatriz(std::string cabecera) {
    this->cabecera = cabecera;
    this->valor = nullptr;

    this->siguiente = nullptr;
    this->anterior = nullptr;

    this->arriba = nullptr;
    this->abajo = nullptr;

    this->adelante = nullptr;
    this->atras = nullptr;

    // Incrementar el contador de nodos
    id = ++countNode;
    // Asignar grupo a este nodo
    group = countGroup; // Puedes ajustar esto según cómo manejes los grupos
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

    // Incrementar el contador de nodos
    id = ++countNode;
    // Asignar grupo a este nodo
    group = countGroup; // Puedes ajustar esto según cómo manejes los grupos
}


void NodoMatriz::crearNuevoGrupo() {
    ++countGroup; // Incrementar el contador de grupos
}
