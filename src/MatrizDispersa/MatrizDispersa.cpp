//
// Created by tubac on 9/12/2024.
//
#include "../../includes/MatrizDispersa/MatrizDispersa.h"

//Este es el constructor
MatrizDispersa::MatrizDispersa() {
    this->horizontal = nullptr;
    this->vertical = nullptr;
}


//Estos son los metodos que declare en la cabecera .h

NodoMatriz *MatrizDispersa::existecabeHorizontal(int valor) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = horizontal;//vamos a recorrer las cabeceras horizontales
    while (aux != nullptr) {
        if (aux->valor == valor) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return nullptr;
}

NodoMatriz *MatrizDispersa::existecabeVertical(int valor) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = vertical;//vamos a recorrer las cabeceras verticales
    while (aux != nullptr) {
        if (aux->valor == valor) {
            return aux;
        }
        aux = aux->abajo;
    }
    return nullptr;
}


bool MatrizDispersa::estaVacia() {
    return this->horizontal == nullptr && this->vertical == nullptr; //Retorna true o false
}


NodoMatriz *MatrizDispersa::insertarCabeHorizontal(int valor) {
    NodoMatriz *nuevaCabe = new NodoMatriz(valor);

    //Esto es cuando es el primer nodo horizontal
    if (horizontal == nullptr) {
        horizontal = nuevaCabe;
        return nuevaCabe;
    }

    NodoMatriz *aux = horizontal;
    while (aux->siguiente != nullptr) {
        aux = aux->siguiente;
    }

    aux->siguiente = nuevaCabe;
    nuevaCabe->anterior = aux;

    return nuevaCabe;//Retornamos el nodo de la nueva cabecera
}

NodoMatriz *MatrizDispersa::insertarCabeVertical(int valor) {
    NodoMatriz *nuevaCabe = new NodoMatriz(valor);

    //Esto es cuando es el primer nodo horizontal
    if (vertical == nullptr) {
        vertical = nuevaCabe;
        return nuevaCabe;
    }

    NodoMatriz *aux = vertical;
    while (aux->abajo != nullptr) {
        aux = aux->abajo;
    }

    aux->abajo = nuevaCabe;
    nuevaCabe->arriba = aux;

    return nuevaCabe;//Retornamos el nodo de la nueva cabecera
}



void MatrizDispersa::insertarValor(int valor, int cabHorizontal, int cabVertical) {
    //Si esta vacia se incertan las cabeceras es el caso mas cencillo
    if (estaVacia()) {
        //Aca ya tengo los nodos
        NodoMatriz *cabeHorizontal = insertarCabeHorizontal(cabHorizontal);
        NodoMatriz *cabeVertical = insertarCabeVertical(cabVertical);

        //Aca se generan las conexiones con la matriz
        insertarAlfinal(valor, cabeHorizontal, cabeVertical);
    }
}


void MatrizDispersa::insertarAlfinal(int valor, NodoMatriz *cabHorizontal, NodoMatriz *cabVertical) {
    NodoMatriz *usuarioNuevo = new NodoMatriz(valor);

    NodoMatriz *auxH = horizontal;
    NodoMatriz *auxV = vertical;

    while (auxH->abajo != nullptr) {
        auxH = auxH->abajo;
    }

    auxH->abajo = usuarioNuevo;
    usuarioNuevo->arriba = auxH;

    while (auxV->siguiente != nullptr) {
        auxV = auxV->siguiente;
    }

    auxV->siguiente = usuarioNuevo;
    usuarioNuevo->anterior = auxV;
}





