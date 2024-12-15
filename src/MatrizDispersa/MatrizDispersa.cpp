//
// Created by tubac on 9/12/2024.
//
#include "../../includes/MatrizDispersa/MatrizDispersa.h"

using namespace std;

#include <stddef.h>
#include <fstream>
#include <string>

//Este es el constructor
MatrizDispersa::MatrizDispersa() {
    this->horizontal = nullptr;
    this->vertical = nullptr;
}

std::string nombre_usuario = "";
Usuarios *usar;
//Estos son los metodos que declare en la cabecera .h

NodoMatriz *MatrizDispersa::existecabeHorizontal(std::string cabecera) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = horizontal;//vamos a recorrer las cabeceras horizontales
    while (aux != nullptr) {
        if (aux->cabecera == cabecera) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return nullptr;
}

NodoMatriz *MatrizDispersa::existecabeVertical(std::string cabecera) {
    if (estaVacia()) {
        return nullptr;
    }

    NodoMatriz *aux = vertical;//vamos a recorrer las cabeceras verticales
    while (aux != nullptr) {
        if (aux->cabecera == cabecera) {
            return aux;
        }
        aux = aux->abajo;
    }
    return nullptr;
}


bool MatrizDispersa::estaVacia() {
    return this->horizontal == nullptr && this->vertical == nullptr; //Retorna true o false
}


NodoMatriz *MatrizDispersa::insertarCabeHorizontal(std::string cabecera) {
    NodoMatriz *nuevaCabe = new NodoMatriz(cabecera);

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

NodoMatriz *MatrizDispersa::insertarCabeVertical(std::string cabecera) {
    NodoMatriz *nuevaCabe = new NodoMatriz(cabecera);

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



void MatrizDispersa::insertarValor(Usuarios* valor, std::string cabHorizontal, std::string cabVertical) {
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
bool MatrizDispersa::masAbajo(NodoMatriz *cabeV, std::string cabV) {
    NodoMatriz *aux = cabeV;

    while (aux != nullptr) {
        if (aux->cabecera == cabV) {
            return true;
        }
        aux = aux->abajo;
    }
    return false;
}


bool MatrizDispersa::masDerecho(NodoMatriz *cabeH, std::string cabH) {
    NodoMatriz *aux = cabeH;

    while (aux != nullptr) {
        if (aux->cabecera == cabH) {
            return true; //Si este nodo es la cabecera que estoy buscando retorno true
        }

        aux = aux->siguiente;
    }

    return false;//Esto retorna falso si no esta mas a la derecha
}


bool MatrizDispersa::existePaswordUser(std::string username, std::string password) {
    if (estaVacia()) {
        return false; // La matriz está vacía, no hay usuarios.
    }

    // Recorremos las cabeceras horizontales.
    NodoMatriz *cabeHorizontalAux = horizontal;
    while (cabeHorizontalAux != nullptr) {
        // Recorremos cada nodo en la fila correspondiente.
        NodoMatriz *nodoAux = cabeHorizontalAux;
        while (nodoAux != nullptr) {
            if (nodoAux->valor != nullptr &&
                nodoAux->valor->usuar == username &&
                nodoAux->valor->pasword == password) {
                nombre_usuario = nodoAux->valor->nombre;
                usar = nodoAux->valor;
                return true; // Usuario y contraseña encontrados.
                }
            nodoAux = nodoAux->siguiente;
        }
        cabeHorizontalAux = cabeHorizontalAux->abajo;
    }

    return false; // No se encontró ningún nodo con el usuario y contraseña.
}


std::string MatrizDispersa::getNombre() {
    return nombre_usuario;
}


Usuarios *MatrizDispersa::getUsuario() {
    return usar;
}

//(aux->valor != nullptr ? aux->valor->usuar : aux->cabecera)
void MatrizDispersa::generarGrafica(){
	std::string dot = "digraph G {";
    dot += "\n\tlabel=\"Matriz Dispersa\";";
    dot += "\n\tlabelloc=\"t\";";
    dot += "\n\tnode [shape=box width=1.2 ];\n";

    if (estaVacia()) {
        dot += "};";
        return;
    }

    //Creacion de los nodos de los departamentos Horizontales
    NodoMatriz *departamentos = this->horizontal;
    NodoMatriz *users;
    dot += "n0 -> n"+ std::to_string(departamentos->id) + " -> n0 [color=transparent];\n\t";

    std::string ranks = "{ rank=same; n0; ";
    while (departamentos != nullptr) {
        dot += "n" + to_string( departamentos->id) + " [label=\"" + departamentos->cabecera + "\" group=" + to_string( departamentos->group) + "];\n\t";

        users = departamentos->abajo;

        dot += "n" + to_string( departamentos->id) + " -> n" + to_string(users->id) + " -> n" + to_string(departamentos->id) + ";\n\t";
        while (users != nullptr) {
            dot += "n"+to_string(users->id) + " [label = \""+ users->valor->usuar + "\" group=" +to_string(users->group)+"];\n\t";

            if (users->abajo != nullptr) {
                dot += "n"+to_string(users->id) + " -> n" + to_string(users->abajo->id) + " -> n" + to_string(users->id) + ";\n\t";
            }
            users = users->abajo;
        }

        if (departamentos->siguiente != nullptr) {
            dot += "n"+to_string(departamentos->id) + " -> n" +to_string(departamentos->siguiente->id) + " -> n" + to_string(departamentos->id)+ ";\n\t";
        }

        ranks += "n" + to_string(departamentos->id) + "; ";
        departamentos = departamentos->siguiente;
    }

    ranks += "}\n\t";

    //Recorremos las cabeceras verticales (Empresas)
    NodoMatriz *company = this->vertical;
    dot += "n0 -> n"+to_string(company->id) + " -> n0 [color=transparent];\n\t";

    while (company != nullptr) {
        ranks += "{ rank=same; ";
        dot += "n"+to_string(company->id)+ " [label=\""+company->cabecera+ "\" group=" + to_string(company->group) + "];\n\t";
        ranks += "n" + to_string(company->id) + "; ";

        users = company->siguiente;
        dot += "n"+to_string(company->id)+ " -> n"+to_string(users->id)+" -> n"+to_string(company->id)+";\n\t";
        while (users != nullptr) {
            dot += "n"+to_string(users->id)+" [label=\""+users->valor->usuar+"\" group="+to_string(users->group)+ "];\n\t";

            if (users->siguiente != nullptr) {
                dot += "n"+to_string(users->id) + " -> n" + to_string(users->siguiente->id) + " -> n" + to_string(users->id) + ";\n\t";
            }

            ranks += "n"+to_string(users->id) + "; ";
            users = users->siguiente;
        }

        if (company->abajo != nullptr) {
            dot += "n"+to_string(company->id) + " -> n" +to_string(company->abajo->id) + " -> n" + to_string(company->id)+ ";\n\t";
        }

        ranks += "}\n\t";
        company = company->abajo;
    }

    dot += ranks;

    dot += "\n}";

    // Escribir el archivo DOT
    std::ofstream file;
    file.open("../src/Reportes/matriz.dot");

    if (file.is_open()) {
        file << dot;
        file.close();
    }

    int resultado = std::system("dot -Tpng ../src/Reportes/matriz.dot -o ../src/Reportes/matriz.png");
    if (resultado == 0) {
        std::cout << "Imagen matriz.png generada exitosamente." << std::endl;
    } else {
        std::cerr << "Error al generar la imagen matriz.png" << std::endl;
    }
}




