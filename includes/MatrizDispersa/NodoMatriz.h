//
// Created by tubac on 9/12/2024.
//

#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H



class NodoMatriz {
    //tiene que tener 6 apuntadores por que es en tres dimenciones
    public:
    int valor;

    NodoMatriz *siguiente;
    NodoMatriz *anterior;

    NodoMatriz *arriba;
    NodoMatriz *abajo;

    NodoMatriz *adelante;
    NodoMatriz *atras;

    //Este es el constructor
    NodoMatriz(int valor);
};



#endif //NODOMATRIZ_H
