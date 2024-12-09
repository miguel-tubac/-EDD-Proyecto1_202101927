//
// Created by tubac on 9/12/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"

class MatrizDispersa {
    public:
    //Va a tener dos cabeceras
    NodoMatriz *horizontal;
    NodoMatriz *vertical;

    //Este es el constructor
    MatrizDispersa();

    //********************* Aca van los metodos de la matriz **********
    //Para revisar si la lista esta vacia
    bool estaVacia();

    //Para ver si existe la cavecera
    NodoMatriz *existecabeHorizontal(int valor);
    NodoMatriz *existecabeVertical(int valor);

    //Para insertar el valor
    void insertarValor(int valor, int cabHorizontal, int cabVertical);

    //Para insertar las cabeceras
    NodoMatriz *insertarCabeHorizontal(int valor);
    NodoMatriz *insertarCabeVertical(int valor);

    //Para insertar un nodo a la matriz
    void insertarAlfinal(int valor, NodoMatriz *cabHorizontal, NodoMatriz *cabVertical);

};



#endif //MATRIZDISPERSA_H
