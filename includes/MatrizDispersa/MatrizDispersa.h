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
    void insertarAlfinal(NodoMatriz *valor, NodoMatriz *cabHorizontal, NodoMatriz *cabVertical);

    //Para insertar en medio de las de la matriz
    void insertarAlfinalH(NodoMatriz *valor, NodoMatriz *cabHorizontal);
    void insertarAlfinalV(NodoMatriz *valor, NodoMatriz *cabVertical);
    void insertarAlMedioH(NodoMatriz *valor, NodoMatriz *horizontal);
    void insertarAlMedioV(NodoMatriz *valor, NodoMatriz *vertical);

    //Esto serviran para encontrar las cebeceras de un usuario en especifico
    NodoMatriz *enCabeceraH(NodoMatriz *nodo);
    NodoMatriz *enCabeceraV(NodoMatriz *nodo);

    //Funcion para saber si el nodo esta mas abajo
    bool masAbajo(NodoMatriz *cabeV, int cabV);
    bool masDerecho(NodoMatriz *cabeH, int cabH);
};



#endif //MATRIZDISPERSA_H
