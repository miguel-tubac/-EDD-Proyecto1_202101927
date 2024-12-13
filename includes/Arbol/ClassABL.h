//
// Created by tubac on 12/12/2024.
//

#ifndef CLASSABL_H
#define CLASSABL_H

#include "Nodo_ABL.h"

class ClassABL {
    private:
        void insertar(Nodo_AVL *valor, Nodo_AVL* &raiz);
    public:

        Nodo_AVL *raiz;

        ClassABL();//Constructor

        void insertar(int valor);

        int alturaMax (Nodo_AVL *nodo);
        int factEquilibrio(Nodo_AVL *nodo); // altura hijo derecho - altura hijo izquierdo.

        //Estas son las rotaciones simples
        void rotacionIzq(Nodo_AVL *&nodo);
        void rotacionDer(Nodo_AVL *&nodo);

        //Estas son las rotaciones dobles
        void rotacionDobleIzqDer(Nodo_AVL *&nodo);
        void rotacionDobleDerIzq(Nodo_AVL *&nodo);
};

#endif //CLASSABL_H
