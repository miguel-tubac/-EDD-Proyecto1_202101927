//
// Created by tubac on 9/12/2024.
//
#include "../../includes/MatrizDispersa/MatrizDispersa.h"

#include <stddef.h>

//Este es el constructor
MatrizDispersa::MatrizDispersa() {
    this->horizontal = nullptr;
    this->vertical = nullptr;
}


//Estos son los metodos que declare en la cabecera .h

NodoMatriz *MatrizDispersa::existecabeHorizontal(int valor) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = horizontal;//vamos a recorrer las cabeceras horizontales
    while (aux != nullptr) {
        if (aux->valor == valor) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return nullptr;
}

NodoMatriz *MatrizDispersa::existecabeVertical(int valor) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = vertical;//vamos a recorrer las cabeceras verticales
    while (aux != nullptr) {
        if (aux->valor == valor) {
            return aux;
        }
        aux = aux->abajo;
    }
    return nullptr;
}


bool MatrizDispersa::estaVacia() {
    return this->horizontal == nullptr && this->vertical == nullptr; //Retorna true o false
}


NodoMatriz *MatrizDispersa::insertarCabeHorizontal(int valor) {
    NodoMatriz *nuevaCabe = new NodoMatriz(valor);

    //Esto es cuando es el primer nodo horizontal
    if (this->horizontal == nullptr) {
        this->horizontal = nuevaCabe;
        return nuevaCabe;
    }

    NodoMatriz *aux = horizontal;
    while (aux->siguiente != nullptr) {
        aux = aux->siguiente;
    }

    aux->siguiente = nuevaCabe;
    nuevaCabe->anterior = aux;

    return nuevaCabe;//Retornamos el nodo de la nueva cabecera
}

NodoMatriz *MatrizDispersa::insertarCabeVertical(int valor) {
    NodoMatriz *nuevaCabe = new NodoMatriz(valor);

    //Esto es cuando es el primer nodo horizontal
    if (this->vertical == nullptr) {
        this->vertical = nuevaCabe;
        return nuevaCabe;
    }

    NodoMatriz *aux = vertical;
    while (aux->abajo != nullptr) {
        aux = aux->abajo;
    }

    aux->abajo = nuevaCabe;
    nuevaCabe->arriba = aux;

    return nuevaCabe;//Retornamos el nodo de la nueva cabecera
}



void MatrizDispersa::insertarValor(int valor, int cabHorizontal, int cabVertical) {
    //Si esta vacia se incertan las cabeceras es el caso mas cencillo
    NodoMatriz *cabeHorizontal = nullptr;
    NodoMatriz *cabeVertical = nullptr;
    NodoMatriz *usuarioNuevo = new NodoMatriz(valor);

    if (estaVacia()) {
        //Aca ya tengo los nodos
        cabeHorizontal = insertarCabeHorizontal(cabHorizontal);
        cabeVertical = insertarCabeVertical(cabVertical);

        //Aca se generan las conexiones con la matriz
        insertarAlfinal(usuarioNuevo, cabeHorizontal, cabeVertical);

        //Retornamos para finalizar el proceso
        return;
    }

    //Aca es cuando la cabezaras ya existen
    cabeHorizontal = existecabeHorizontal(cabHorizontal); //Se busca el nodo
    cabeVertical = existecabeVertical(cabVertical);

    //Aca se comprueba si los dos son nulas, es decir no existen
    if (cabeHorizontal == nullptr && cabeVertical == nullptr) {
        cabeHorizontal = insertarCabeHorizontal(cabHorizontal);
        cabeVertical = insertarCabeVertical(cabVertical);

        //Aca se generan las conexiones con la matriz
        insertarAlfinal(usuarioNuevo, cabeHorizontal, cabeVertical);

        //Retornamos para finalizar el proceso
        return;
    }

    //Aca se verifica si no existe la cabecera horizontal se agrega
    if (cabeHorizontal == nullptr) {
        cabeHorizontal = insertarCabeHorizontal(cabHorizontal);
        insertarAlfinal(usuarioNuevo, cabeHorizontal, cabeVertical);
        return;
    }

    //Aca se verifica si no existe la cebecera vertical y se agrega
    if (cabeVertical == nullptr) {
        cabeVertical = insertarCabeVertical(cabVertical);
        insertarAlfinal(usuarioNuevo, cabeHorizontal, cabeVertical);
        return;
    }

    //Aca se validan cuado todas las cabeceras son existentes
    NodoMatriz *auxH = cabeHorizontal->abajo;
    NodoMatriz *userCabV;
    bool abajo = false;

    while (auxH !=  nullptr) {
        userCabV = enCabeceraV(auxH); //Aca se busca el nodo de la cabecera Horizontal
        abajo = masAbajo(userCabV, cabVertical);

        if (!abajo) break;

        auxH = auxH->abajo;
    }

    if (abajo) {
        insertarAlfinalH(usuarioNuevo, cabeHorizontal);
    }else {
        insertarAlMedioH(usuarioNuevo, auxH);
    }

    NodoMatriz *auxV = cabeVertical->siguiente;
    NodoMatriz *userCabH;
    bool siguiente = false;

    while (auxV != nullptr) {
        userCabH = enCabeceraH(auxV);
        siguiente = masDerecho(userCabH, cabHorizontal);

        if (!siguiente) break;//Esto es para que no avance al siguiente nodo el cual no nos inetresa

        auxV = auxV->siguiente;
    }
    if (siguiente) {//Si es falso se incera en medio de la lista vertical
        insertarAlfinalV(usuarioNuevo, cabeVertical);//Aca se incerta al medio
    }else {
        insertarAlMedioV(usuarioNuevo, auxV);
    }


}


void MatrizDispersa::insertarAlfinal(NodoMatriz *valor, NodoMatriz *cabHorizontal, NodoMatriz *cabVertical) {
    insertarAlfinalH(valor, cabHorizontal);
    insertarAlfinalV(valor, cabVertical);
}


//Con estos metodos se utilizaran para insertar en medio o al final, segun el caso:
void MatrizDispersa::insertarAlfinalH(NodoMatriz *valor, NodoMatriz *cabHorizontal) {
    NodoMatriz *aux = cabHorizontal;

    while (aux->abajo != nullptr) {
        aux = aux->abajo;
    }

    aux->abajo = valor;
    valor->arriba = aux;
}

void MatrizDispersa::insertarAlfinalV(NodoMatriz *valor, NodoMatriz *cabVertical) {
    NodoMatriz *aux = cabVertical;

    while (aux->siguiente != nullptr) {
        aux = aux->siguiente;
    }

    aux->siguiente = valor;
    valor->anterior = aux;
}

void MatrizDispersa::insertarAlMedioV(NodoMatriz *valor, NodoMatriz *vertical) {
    vertical->anterior->siguiente = valor;
    valor->siguiente = vertical;

    valor->anterior = vertical->anterior;
    vertical->anterior = valor;
}

void MatrizDispersa::insertarAlMedioH(NodoMatriz *valor, NodoMatriz *horizontal) {
    horizontal->arriba->abajo = valor;
    valor->abajo = horizontal;

    valor->arriba = horizontal->arriba;
    horizontal->arriba = valor;
}



//Estos son los metododos para encontrar las cabeceras de la matris, para poder insertar un nuevo nodo
NodoMatriz *MatrizDispersa::enCabeceraH(NodoMatriz *nodo) {
    NodoMatriz *aux = nodo;

    while (aux->arriba != nullptr) {
        aux = aux->arriba;
    }
    return aux;
}

NodoMatriz *MatrizDispersa::enCabeceraV(NodoMatriz *nodo) {
    NodoMatriz *aux = nodo;
    while (aux->anterior != nullptr) {
        aux = aux->anterior; //Aca se recorre las ceveceras horizontales
    }
    return aux;
}


//Con esto compruebo si el nodo que estoy buscando esta mas a la izquierda o abajo
bool MatrizDispersa::masAbajo(NodoMatriz *cabeV, int cabV) {
    NodoMatriz *aux = cabeV;

    while (aux != nullptr) {
        if (aux->valor == cabV) {
            return true;
        }
        aux = aux->abajo;
    }
    return false;
}


bool MatrizDispersa::masDerecho(NodoMatriz *cabeH, int cabH) {
    NodoMatriz *aux = cabeH;

    while (aux != nullptr) {
        if (aux->valor == cabH) {
            return true; //Si este nodo es la cabecera que estoy buscando retorno true
        }

        aux = aux->siguiente;
    }

    return false;//Esto retorna falso si no esta mas a la derecha
}






