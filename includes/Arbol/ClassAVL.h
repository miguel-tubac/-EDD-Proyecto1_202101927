//
// Created by tubac on 12/12/2024.
//

#ifndef CLASSABL_H
#define CLASSABL_H

#include "Nodo_AVL.h"
#include "../Clases/Activos.h"

class ClassAVL {
    private:
        void insertar(Nodo_AVL *valor, Nodo_AVL* &raiz);
        void eliminar(std::string id, Nodo_AVL *&raiz);
        void mostrarActivos(Nodo_AVL* nodo);
    public:

        Nodo_AVL *raiz;

        ClassAVL();//Constructor

        void insertar(std::string id, Activos *activo);

        int alturaMax (Nodo_AVL *nodo);
        int factEquilibrio(Nodo_AVL *nodo); // altura hijo derecho - altura hijo izquierdo.

        //Estas son las rotaciones simples
        void rotacionDer(Nodo_AVL *&nodo);
        void rotacionIzq(Nodo_AVL *&nodo);

        //Estas son las rotaciones dobles
        void rotacionDobleDerIzq(Nodo_AVL *&nodo);
        void rotacionDobleIzqDer(Nodo_AVL *&nodo);

        //Esto es para eliminar el nodo del arbol
        void eliminar(std::string id);

        //Esta funcion sirve para movernos entre los nodos y saber donde elimnar
        Nodo_AVL* masALaDerecha(Nodo_AVL* &nodo);

        //Esto es para saber si es una hoja el nodo
        bool esHoja(Nodo_AVL *nodo);

        void mostrarActivos();
};

#endif //CLASSABL_H
