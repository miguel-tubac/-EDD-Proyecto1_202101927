//
// Created by tubac on 9/12/2024.
//

#ifndef NODOMATRIZ_H
#define NODOMATRIZ_H

#include "../Clases/Usuarios.h"

class NodoMatriz {
    //tiene que tener 6 apuntadores por que es en tres dimenciones
    public:
    //int valor;
    Usuarios* valor;
    std::string cabecera;

    NodoMatriz *siguiente;
    NodoMatriz *anterior;

    NodoMatriz *arriba;
    NodoMatriz *abajo;

    NodoMatriz *adelante;
    NodoMatriz *atras;

    static int countGroup;
    static int countNode;

    int group;
    int id;

    //Este es el constructor
    NodoMatriz(Usuarios* valor);
    NodoMatriz(std::string cabecera);

    static void crearNuevoGrupo();
};



#endif //NODOMATRIZ_H
