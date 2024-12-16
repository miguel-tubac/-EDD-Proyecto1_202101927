//
// Created by tubac on 12/12/2024.
//

#include "../../includes/Arbol/ClassAVL.h"

#include <fstream>
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
    if (nodo == nullptr) {
        std::cout << "El ID: " + id + " no existe en el árbol" << std::endl;
        return;
    }

    if (id < nodo->id) {
        eliminar(id, nodo->izq);
    } else if (id > nodo->id) {
        eliminar(id, nodo->der);
    } else {
        // Nodo encontrado
        if (esHoja(nodo)) {
            std::cout << "\nActivo Eliminado;" << std::endl;
            std::cout << "ID: "<< nodo->id << std::endl;
            std::cout << "Nombre: "<< nodo->activo->nombre << std::endl;
            std::cout << "Descripcion: "<< nodo->activo->descripcion << std::endl;
            delete nodo;
            nodo = nullptr;
        } else if (nodo->izq == nullptr) {
            Nodo_AVL *temp = nodo;
            nodo = nodo->der;
            std::cout << "\nActivo Eliminado Correctamente" << std::endl;
            //std::cout << "ID: "<< temp->id << std::endl;
            //std::cout << "Nombre: "<< temp->activo->nombre << std::endl;
            //std::cout << "Descripcion: "<< temp->activo->descripcion << std::endl;
            delete temp;
        } else if (nodo->der == nullptr) {
            Nodo_AVL *temp = nodo;
            nodo = nodo->izq;
            std::cout << "\nActivo Eliminado Correctamente" << std::endl;
            //std::cout << "ID: "<< temp->id << std::endl;
            //std::cout << "Nombre: "<< temp->activo->nombre << std::endl;
            //std::cout << "Descripcion: "<< temp->activo->descripcion << std::endl;
            delete temp;
        } else {
            // Nodo con dos hijos: buscar el mayor de los menores
            Nodo_AVL *temp = masALaDerecha(nodo->izq);
            nodo->id = temp->id;
            nodo->activo = temp->activo;
            eliminar(temp->id, nodo->izq);
        }
    }

    if (nodo == nullptr) return;

    // Recalcular el factor de equilibrio
    nodo->factorEq = factEquilibrio(nodo);

    // Balancear el árbol si está desbalanceado
    if (nodo->factorEq < -1) {
        if (nodo->izq->factorEq > 0) {
            rotacionDobleIzqDer(nodo);
        } else {
            rotacionDer(nodo);
        }
    } else if (nodo->factorEq > 1) {
        if (nodo->der->factorEq < 0) {
            rotacionDobleDerIzq(nodo);
        } else {
            rotacionIzq(nodo);
        }
    }
}



bool ClassAVL::esHoja(Nodo_AVL* nodo) {

    if (nodo != nullptr) {
        return nodo->der == nullptr && nodo->izq == nullptr;
    }

    return false;
}

//******************************************Esto muestra los activo solo los id y nombres***********************************
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


//****************************************Esto me permite buscar el nodo de un id**************************************
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

//**************************Esto modifica la descripcion de un activo***************************************
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


//*********************************************Esto me permite mostrar los dias de renta**************************************
void ClassAVL::mostrarActivosConTiempo() {
    mostrarActivosConTiempo(this->raiz);
}

void ClassAVL::mostrarActivosConTiempo(Nodo_AVL* nodo) {
    if (nodo == nullptr) {
        return; // Caso base: si el nodo es nulo, no hacemos nada
    }

    // Recorrido inorden: izquierda, nodo, derecha
    mostrarActivosConTiempo(nodo->izq); // Visita el subárbol izquierdo
    std::cout << "ID: " << nodo->id << " ; Nombre: "<< nodo->activo->nombre << " ; Tiempo de Renta = " << nodo->tiempoRenta << " dias;" <<std::endl; // Muestra el id del nodo actual
    mostrarActivosConTiempo(nodo->der); // Visita el subárbol derecho
}

//*******************************Esto modifica los dias de renta****************************************************************
void ClassAVL::modificarRentaActivo(std::string idActivo, int tiemporenta) {
    Nodo_AVL *aux = buscar(idActivo);
    if (aux != nullptr) {
        aux->tiempoRenta = tiemporenta;
        std::cout <<"\nActivo A Rentar :"<< std::endl;
        std::cout << "ID: "<< aux->id << std::endl;
        std::cout << "Nombre: "<< aux->activo->nombre << std::endl;
        std::cout << "Descripcion: "<< aux->activo->descripcion << std::endl;
        std::cout << "Teimpo de Renta: "<< aux->tiempoRenta << std::endl;
        return;
    }
    std::cout << "El ID: " + idActivo +" no existe en el arbol" << std::endl;
}

//**********************************Esto me permite visualizar los activos que si esten rentados unicamente*********************
void ClassAVL::mostrarActivosRentados() {
    mostrarActivosRentados(this->raiz);
}

void ClassAVL::mostrarActivosRentados(Nodo_AVL *nodo) {
    if (nodo == nullptr) {
        return; // Caso base: si el nodo es nulo, no hacemos nada
    }

    // Recorrido inorden: izquierda, nodo, derecha
    mostrarActivosRentados(nodo->izq); // Visita el subárbol izquierdo
    //Unicamente muestra los que si estan rentados
    if (nodo->tiempoRenta > 0) {
        std::cout << "ID: " << nodo->id << " ; Nombre: "<< nodo->activo->nombre << " ; Tiempo de Renta = " << nodo->tiempoRenta << " dias;" <<std::endl;
    }
    mostrarActivosRentados(nodo->der); // Visita el subárbol derecho
}


//********************************Esto modifica los dias de renta a cero**********************************************************
void ClassAVL::modificarDevolucionActivo(std::string idActivo) {
    Nodo_AVL *aux = buscar(idActivo);
    if (aux != nullptr) {
        aux->tiempoRenta = 0;
        std::cout <<"\nActivo Devuelto :"<< std::endl;
        std::cout << "ID: "<< aux->id << std::endl;
        std::cout << "Nombre: "<< aux->activo->nombre << std::endl;
        std::cout << "Descripcion: "<< aux->activo->descripcion << std::endl;
        std::cout << "Teimpo de Renta: "<< aux->tiempoRenta << std::endl;
        return;
    }
    std::cout << "El ID: " + idActivo +" no existe en el arbol" << std::endl;
}



//***********************************Esto es para generar el grafico en Graphiz************************************************
void ClassAVL::graficarArbol() {
    std::string dot = "digraph AVLTree {\n";
    dot += "\tlabel=\"Arbol AVL\";\n";
    dot += "    node [shape=circle];\n";

    // Llamada recursiva para escribir los nodos y conexiones
    generarDot(this->raiz, dot);

    dot += "}\n";

    // Escribir el archivo DOT
    std::ofstream file;
    file.open("../src/Reportes/arbol.dot");

    if (file.is_open()) {
        file << dot;
        file.close();
    }

    int resultado = std::system("dot -Tpng ../src/Reportes/arbol.dot -o ../src/Reportes/arbol.png");
    if (resultado == 0) {
        std::cout << "Imagen arbol.png generada exitosamente." << std::endl;
    } else {
        std::cerr << "Error al generar la imagen arbol.png" << std::endl;
    }
}


//*******************************************Esto sirve para generar el dot del grafico del arbol***************************
void ClassAVL::generarDot(Nodo_AVL* nodo, std::string& archivo) {
    if (nodo == nullptr) return;

    // Escribir el nodo actual
    if (nodo->tiempoRenta > 0) {
        //Aqui rellenar a los nodos de color rojo    color= red, style=filled
        archivo += "    \"" + nodo->id + "\" [color= red, style=filled label=\"" + "ID = " + nodo->id + "\\nNombre = " + nodo->activo->nombre + "\"];\n";
    }else {
        archivo += "    \"" + nodo->id + "\" [label=\"" + "ID = " + nodo->id + "\\nNombre = " + nodo->activo->nombre + "\"];\n";
    }


    // Escribir la conexión hacia el hijo izquierdo (si existe)
    if (nodo->izq != nullptr) {
        archivo += "    \"" + nodo->id + "\" -> \"" + nodo->izq->id + "\";\n";
        generarDot(nodo->izq, archivo);
    }

    // Escribir la conexión hacia el hijo derecho (si existe)
    if (nodo->der != nullptr) {
        archivo += "    \"" + nodo->id + "\" -> \"" + nodo->der->id + "\";\n";
        generarDot(nodo->der, archivo);
    }
}


//**************************************Esto es para generar el dot y retornarlo*******************************************
std::string ClassAVL::retornarDotArbolActivos() {
    std::string dot = "";
    // Llamada recursiva para escribir los nodos y conexiones
    generarDot(this->raiz, dot);

    return dot;
}

