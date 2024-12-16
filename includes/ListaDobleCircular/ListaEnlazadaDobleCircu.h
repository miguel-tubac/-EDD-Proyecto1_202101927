//
// Created by tubac on 16/12/2024.
//

#ifndef LISTAENLAZADADOBLE_H
#define LISTAENLAZADADOBLE_H

#include "../Clases/Transacciones.h"

//Esta es la calase del nodo de la lista
class Node3 {
public:
    Transacciones* data;
    Node3* next;
    Node3* prev;
    std::string ID;

    Node3(std::string ID, Transacciones* data) : ID(ID), data(data), next(nullptr), prev(nullptr) {}//Este es el constructor
};


//Esta es la clase de la lista doble
class ListaEnlazadaDobleCircu {
private:
    Node3* inicio;

public:
    ListaEnlazadaDobleCircu();
    void agregar(std::string ID, Transacciones* transaccion);
    void ordenarAscendente();
    void ordenarDesendente();
    void graficar();
};

#endif //LISTAENLAZADADOBLE_H
