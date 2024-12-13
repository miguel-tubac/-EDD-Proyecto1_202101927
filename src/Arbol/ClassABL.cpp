//
// Created by tubac on 12/12/2024.
//

#include "../../includes/Arbol/ClassABL.h"

ClassABL::ClassABL() {
    this->raiz = nullptr;
}


void ClassABL::insertar(int valor) {
    Nodo_AVL *nodo = new Nodo_AVL(valor);

    insertar(nodo, this->raiz);
}

void ClassABL::insertar(Nodo_AVL *valor, Nodo_AVL *&raiz) {
    if (raiz == nullptr) {
        raiz = valor;
        raiz->factorEq = factEquilibrio(raiz);
        return;
    }

    if (valor->valor < raiz->valor) {
        insertar(valor, raiz->izq);
    }else {
        insertar(valor, raiz->der);
    }
    raiz->factorEq = factEquilibrio(raiz);

    //Aca se realizaran las rotaciones
    if (raiz->factorEq < -1) {//El hijo izq es mas grande que el Der
        if (raiz->izq->factorEq > 0) {
            //Estes es el caso cuando es una rotacion doble
            rotacionDobleDerIzq(raiz);
            return;
        }
        //Aca es una rotacion simple
        rotacionIzq(raiz);
        return;
    }

    if (raiz->factorEq > 1) {
        if (raiz->der->factorEq < 0) {
            //Aca se realiza la rotacion doble
            rotacionDobleIzqDer(raiz);
            return;
        }
        //De lo contrario es una simple
        rotacionDer(raiz);
        return;
    }
}



int ClassABL::alturaMax(Nodo_AVL *nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int alturaIzq = alturaMax(nodo->izq);
    int alturaDer = alturaMax(nodo->der);

    return alturaIzq > alturaDer ? alturaIzq + 1 : alturaDer + 1;
}

int ClassABL::factEquilibrio(Nodo_AVL *nodo) {
    return alturaMax(nodo->der) - alturaMax(nodo->izq);
}


void ClassABL::rotacionIzq(Nodo_AVL *&nodo) {
    Nodo_AVL *aux = nodo->izq;

    nodo->izq = aux->der;
    aux->der = nodo;
    nodo = aux;

    //Aca bolvemos a calcular el factor de equilibrio para la comprobacion posterior
    nodo->factorEq = factEquilibrio(nodo);
    nodo->der->factorEq = factEquilibrio(nodo->der);
    if (nodo->izq == nullptr) return;
    nodo->izq->factorEq = factEquilibrio(nodo->izq);
}

void ClassABL::rotacionDer(Nodo_AVL *&nodo) {
    Nodo_AVL *aux = nodo->der;

    nodo->der = aux->izq;
    aux->izq = nodo;
    nodo = aux;

    //Aca bolvemos a calcular el factor de equilibrio para la comprobacion posterior
    nodo->factorEq = factEquilibrio(nodo);
    nodo->izq->factorEq = factEquilibrio(nodo->izq);
    if (nodo->der == nullptr) return;
    nodo->der->factorEq = factEquilibrio(nodo->der);
}


void ClassABL::rotacionDobleDerIzq(Nodo_AVL *&nodo) {
    rotacionDer(nodo->izq);
    rotacionIzq(nodo);
}


void ClassABL::rotacionDobleIzqDer(Nodo_AVL *&nodo) {
    rotacionIzq(nodo->der);
    rotacionDer(nodo);
}


