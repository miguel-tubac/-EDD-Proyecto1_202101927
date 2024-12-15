//
// Created by tubac on 12/12/2024.
//

#include "../../includes/Arbol/ClassAVL.h"

#include <iostream>
#include <string>

ClassAVL::ClassAVL() {
    this->raiz = nullptr;
}


void ClassAVL::insertar(std::string id, Activos *activo) {
    Nodo_AVL *nodo = new Nodo_AVL(id,activo);

    insertar(nodo, this->raiz);
}

void ClassAVL::insertar(Nodo_AVL *valor, Nodo_AVL *&raiz) {
    if (raiz == nullptr) {
        raiz = valor;
        raiz->factorEq = factEquilibrio(raiz);
        return;
    }

    if (valor->id < raiz->id) {
        insertar(valor, raiz->izq);
    }else {
        insertar(valor, raiz->der);
    }
    raiz->factorEq = factEquilibrio(raiz);

    //Aca se realizaran las rotaciones
    if (raiz->factorEq < -1) {//El hijo izq es mas grande que el Der
        if (raiz->izq->factorEq > 0) {
            //Estes es el caso cuando es una rotacion doble
            rotacionDobleIzqDer(raiz);
            return;
        }
        //Aca es una rotacion simple
        rotacionDer(raiz);
        return;
    }

    if (raiz->factorEq > 1) {
        if (raiz->der->factorEq < 0) {
            //Aca se realiza la rotacion doble
            rotacionDobleDerIzq(raiz);
            return;
        }
        //De lo contrario es una simple
        rotacionIzq(raiz);
        return;
    }
}



int ClassAVL::alturaMax(Nodo_AVL *nodo) {
    if (nodo == nullptr) {
        return 0;
    }

    int alturaIzq = alturaMax(nodo->izq);
    int alturaDer = alturaMax(nodo->der);

    return alturaIzq > alturaDer ? alturaIzq + 1 : alturaDer + 1;
}

int ClassAVL::factEquilibrio(Nodo_AVL *nodo) {
    return alturaMax(nodo->der) - alturaMax(nodo->izq);
}


void ClassAVL::rotacionDer(Nodo_AVL *&nodo) {
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

void ClassAVL::rotacionIzq(Nodo_AVL *&nodo) {
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


void ClassAVL::rotacionDobleIzqDer(Nodo_AVL *&nodo) {
    rotacionIzq(nodo->izq);
    rotacionDer(nodo);
}


void ClassAVL::rotacionDobleDerIzq(Nodo_AVL *&nodo) {
    rotacionDer(nodo->der);
    rotacionIzq(nodo);
}

//Con este funcion busco el valor mas grande de los menores
Nodo_AVL *ClassAVL::masALaDerecha(Nodo_AVL *&nodo) {
    if (nodo->der == nullptr) {
        return nodo;
    }

    return masALaDerecha(nodo->der);
}

//Esta es el publico que se accede desde el main
void ClassAVL::eliminar(std::string id) {
    eliminar(id, this->raiz);//Con esto mando la raiz
}

void ClassAVL::eliminar(std::string id, Nodo_AVL *&nodo) {
    if (raiz == nullptr) {
        std::cout << "El ID: " + id +" no existe en el arbol" << std::endl;
        return;
    }

    if (id == raiz->id) {//Este es el caso de eliminar la raiz
        if (esHoja(raiz)) { //Esto es cuando eliminamos una hoja
            std::cout << "\nActivo Eliminado;" << std::endl;
            std::cout << "ID: "<< raiz->id << std::endl;
            std::cout << "Nombre: "<< raiz->activo->nombre << std::endl;
            std::cout << "Descripcion: "<< raiz->activo->descripcion << std::endl;
            raiz = nullptr;
            return;
        }

        //Ahora cuando la raiz no es una hoja
        if (raiz->izq == nullptr) {
            std::cout << "\nActivo Eliminado;" << std::endl;
            std::cout << "ID: "<< raiz->id << std::endl;
            std::cout << "Nombre: "<< raiz->activo->nombre << std::endl;
            std::cout << "Descripcion: "<< raiz->activo->descripcion << std::endl;
            raiz = raiz->der;
            return;
        }

        if (raiz->der == nullptr) {
            std::cout << "\nActivo Eliminado;" << std::endl;
            std::cout << "ID: "<< raiz->id << std::endl;
            std::cout << "Nombre: "<< raiz->activo->nombre << std::endl;
            std::cout << "Descripcion: "<< raiz->activo->descripcion << std::endl;
            raiz = raiz->izq;
            return;
        }

        //Este es el caso en donde ninguno de las ramas es nulla, por lo tanto debemos buscar el mas
        // a la derecha del hijo izquierdo
        Nodo_AVL *nodoDerecho = masALaDerecha(raiz->izq);
        raiz->activo = nodoDerecho->activo;

        eliminar(nodoDerecho->id, raiz->izq);
        //Revisar esta parte
        //activo = raiz->activo
        id = raiz->id;//Esto es para mantener el valor
    }

    if (id < raiz->id) {
        //Este es el caso en donde se elimina el lado izquierdo
        eliminar(id, raiz->izq);
    }

    if (id > raiz->id) {
        eliminar(id, raiz->der);
    }

    //Volvemos a recalcular el factor de equilibrio
    raiz->factorEq = factEquilibrio(raiz);
    if (raiz->factorEq < -1) {
        if (raiz->izq->factorEq > 0) {
            rotacionDobleIzqDer(raiz);
            return;
        }

        rotacionDer(raiz);
        return;
    }
    if (raiz->factorEq > 1) {
        if (raiz->der->factorEq < 0) {
            rotacionDobleDerIzq(raiz);
            return;
        }
        rotacionIzq(raiz);
        return;
    }
}


bool ClassAVL::esHoja(Nodo_AVL* nodo) {

    if (nodo != nullptr) {
        return nodo->der == nullptr && nodo->izq == nullptr;
    }

    return false;
}

void ClassAVL::mostrarActivos() {
    mostrarActivos(this->raiz);
}

void ClassAVL::mostrarActivos(Nodo_AVL* nodo) {
    if (nodo == nullptr) {
        return; // Caso base: si el nodo es nulo, no hacemos nada
    }

    // Recorrido inorden: izquierda, nodo, derecha
    mostrarActivos(nodo->izq); // Visita el subárbol izquierdo
    std::cout << "ID: " << nodo->id << " ; Nombre: "<< nodo->activo->nombre <<std::endl; // Muestra el id del nodo actual
    mostrarActivos(nodo->der); // Visita el subárbol derecho
}


Nodo_AVL* ClassAVL::buscar(std::string id) {
    return buscar(id, this->raiz);
}

Nodo_AVL* ClassAVL::buscar(std::string id, Nodo_AVL* nodo) {
    if (nodo == nullptr) {
        return nullptr; // Caso base: si el nodo es nulo, no se encontró el ID
    }

    if (id == nodo->id) {
        return nodo; // Se encontró el nodo con el ID
    }

    if (id < nodo->id) {
        return buscar(id, nodo->izq); // Buscar en el subárbol izquierdo
    } else {
        return buscar(id, nodo->der); // Buscar en el subárbol derecho
    }
}


void ClassAVL::modificarActivo(std::string idActivo, std::string nuevaDescripcion) {
    Nodo_AVL *aux = buscar(idActivo, this->raiz);
    if (aux != nullptr) {
        aux->activo->descripcion = nuevaDescripcion;

        std::cout <<"\nActivo Modificado :"<< std::endl;
        std::cout << "ID: "<< aux->id << std::endl;
        std::cout << "Nombre: "<< aux->activo->nombre << std::endl;
        std::cout << "Descripcion: "<< aux->activo->descripcion << std::endl;
        return;
    }
    std::cout << "El ID: " + idActivo +" no existe en el arbol" << std::endl;
}


