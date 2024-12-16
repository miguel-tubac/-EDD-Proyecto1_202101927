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
        usuarioNuevo->crearNuevoGrupo();
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
        usuarioNuevo->crearNuevoGrupo();
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

    // Verifica si ya existe un nodo en la intersección
    NodoMatriz *auxHH = cabeHorizontal->abajo;
    while (auxHH != nullptr) {
        NodoMatriz *auxVV = auxHH; //Falta revisar en el nodo de frente y atras
        NodoMatriz *aux3D = auxHH;
        while (aux3D != nullptr) {
            if (aux3D->valor->usuar == valor->usuar) {
                std::cout << "Error: Ya existe un usuario en la posición ingresada" << std::endl;
                return;
            }
            aux3D = aux3D->atras;
        }

        while (auxVV != nullptr) {
            if (auxVV->valor == nullptr && auxVV->cabecera == cabVertical) {
                //Aca se tiene que agregar la opcion de al frente o atras
                int opcion;
                bool recorrido = true;
                do {
                    std::cout << "\nEn esta posicion ya existe un usuario, elija donde Insertar al nuevo usuario:" << std::endl;
                    std::cout << "1. Adlante del Usuario" << std::endl;
                    std::cout << "2. Atras del Usuario" << std::endl;
                    std::cout << "\nIngrese una opcion: ";
                    std::cin >> opcion;
                    switch (opcion) {
                        case 1:
                            insertarFrente(valor, auxHH);
                            recorrido = false;
                            break;
                        case 2:
                            insertarAtras(valor, auxHH);
                            recorrido = false;
                            break;
                        default:
                            std::cout << "Opcion incorrecto, intente de nuevo" << std::endl;
                    }
                }while (recorrido);
                return;
            }
            auxVV = auxVV->anterior;
        }

        auxHH = auxHH->abajo;
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



//Metodo para insertar atras de un usuario que ya este en una posición.
void MatrizDispersa::insertarAtras(Usuarios* nuevoUsuario, NodoMatriz* usuarioActual) {
    NodoMatriz* nuevo = new NodoMatriz(nuevoUsuario);

    NodoMatriz* aux = usuarioActual;

    while (aux->atras != nullptr) {
        aux = aux->atras;
    }

    aux->atras = nuevo;
    nuevo->adelante = aux;
}

void MatrizDispersa::insertarFrente(Usuarios* nuevoUsuario, NodoMatriz* usuarioActual) {
    NodoMatriz* nuevo = new NodoMatriz(nuevoUsuario);

    NodoMatriz* aux = usuarioActual;
    NodoMatriz* aux2 = usuarioActual;


    while (aux->atras != nullptr) {
        aux = aux->atras;
    }

    aux->atras = nuevo;
    nuevo->adelante = aux;

    nuevo->valor = aux2->valor;
    usuarioActual->valor = nuevoUsuario;

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
    NodoMatriz *cabeHorizontalAux = horizontal->abajo;
    NodoMatriz *cabeVerticalAux = horizontal->siguiente;
    while (cabeHorizontalAux != nullptr) {
        // Recorremos cada nodo en la fila correspondiente.
        NodoMatriz *nodoAux = cabeHorizontalAux;
        while (nodoAux != nullptr) {
            if (nodoAux->valor != nullptr && nodoAux->valor->usuar == username && nodoAux->valor->pasword == password) {
                nombre_usuario = nodoAux->valor->nombre;
                usar = nodoAux->valor;
                return true; // Usuario y contraseña encontrados.
                }
            nodoAux = nodoAux->atras;
        }

        if (cabeHorizontalAux->abajo ==  nullptr && cabeVerticalAux != nullptr) {
            cabeHorizontalAux = cabeVerticalAux;
            cabeVerticalAux = cabeVerticalAux->siguiente;
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
        dot += "n"+to_string(company->id)+ " [label=\""+company->cabecera+ "\" group=0];\n\t";
        //dot += "n"+to_string(company->id)+ " [label=\""+company->cabecera+ "\" group=" + to_string(company->group) + "];\n\t";
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


//****************************************Con esto genero todas las graficas de los arboles de una columna*******************
void MatrizDispersa::generarGraficasDepartamento(std::string departamento) {
    NodoMatriz *aux = existecabeHorizontal(departamento);
    if (aux == nullptr) {
        std::cout << "Error: No existe la cabecera departamento: "<< departamento << std::endl;
        return;
    }
    aux = aux->abajo;
    std::string dot = "digraph AVLTree {\n";
    dot += "\tlabel=\"Arbol AVL del Departamento = "+departamento+"\";\n";
    dot += "    node [shape=circle];\n";

    while (aux != nullptr) {
        NodoMatriz *aux2 = aux;
        while (aux2 != nullptr) {
            dot += aux2->valor->arbol->retornarDotArbolActivos();
            aux2 = aux2->atras;
        }

        aux = aux->abajo;
    }
    dot += "}\n";
    generarImagen(dot);
}


//*********************************************Esto genera la imagen a partir de un string de los departamentos********************************
void MatrizDispersa::generarImagen(std::string dot) {
    // Escribir el archivo DOT
    std::ofstream file;
    file.open("../src/Reportes/arbol_Dep.dot");

    if (file.is_open()) {
        file << dot;
        file.close();
    }

    int resultado = std::system("dot -Tpng ../src/Reportes/arbol_Dep.dot -o ../src/Reportes/arbol_Dep.png");
    if (resultado == 0) {
        std::cout << "Imagen arbol_Dep.png generada exitosamente." << std::endl;
    } else {
        std::cerr << "Error al generar la imagen arbol_Dep.png" << std::endl;
    }
}



//*********************************************Esto genera el codigo para los arboles de una empresa************************
void MatrizDispersa::generarGraficasEmpresa(std::string empresa) {
    NodoMatriz *aux = existecabeVertical(empresa);
    if (aux == nullptr) {
        std::cout << "Error: No existe la cabecera de la empresa: "<< empresa << std::endl;
        return;
    }
    aux = aux->siguiente;
    std::string dot = "digraph AVLTree {\n";
    dot += "\tlabel=\"Arbol AVL de la empresa = "+empresa+"\";\n";
    dot += "    node [shape=circle];\n";

    while (aux != nullptr) {
        NodoMatriz *aux2 = aux;
        while (aux2 != nullptr) {
            dot += aux2->valor->arbol->retornarDotArbolActivos();
            aux2 = aux2->atras;
        }

        aux = aux->siguiente;
    }
    dot += "}\n";
    generarImagenEmpresas(dot);
}


//*********************************************Esto genera la imagen a partir de un string de las Empresas*********************************
void MatrizDispersa::generarImagenEmpresas(std::string dot) {
    // Escribir el archivo DOT
    std::ofstream file;
    file.open("../src/Reportes/arbol_Emp.dot");

    if (file.is_open()) {
        file << dot;
        file.close();
    }

    int resultado = std::system("dot -Tpng ../src/Reportes/arbol_Emp.dot -o ../src/Reportes/arbol_Emp.png");
    if (resultado == 0) {
        std::cout << "Imagen arbol_Emp.png generada exitosamente." << std::endl;
    } else {
        std::cerr << "Error al generar la imagen arbol_Emp.png" << std::endl;
    }
}


//*************************Esto es para generar la grafica de un solo usuario*******************************************
void MatrizDispersa::generarGraficaUsuario(std::string usuario) {
    if (estaVacia()) {
        std::cout << "Error: la matriz esta vacilla"<< std::endl;
        return; // La matriz está vacía, no hay usuarios.
    }

    // Recorremos las cabeceras horizontales.
    NodoMatriz *cabeHorizontalAux = horizontal->abajo;
    NodoMatriz *cabeVerticalAux = horizontal->siguiente;
    while (cabeHorizontalAux != nullptr) {
        // Recorremos cada nodo en la fila correspondiente.
        NodoMatriz *nodoAux = cabeHorizontalAux;
        while (nodoAux != nullptr) {
            if (nodoAux->valor != nullptr && nodoAux->valor->usuar == usuario) {
                //nombre_usuario = nodoAux->valor->nombre;
                //usar = nodoAux->valor;
                nodoAux->valor->arbol->graficarArbol(usuario);
                return; // Usuario y contraseña encontrados.
            }
            nodoAux = nodoAux->atras;
        }

        if (cabeHorizontalAux->abajo ==  nullptr && cabeVerticalAux != nullptr) {
            cabeHorizontalAux = cabeVerticalAux;
            cabeVerticalAux = cabeVerticalAux->siguiente;
        }
        cabeHorizontalAux = cabeHorizontalAux->abajo;
    }

    std::cout << "Error: El usuario con el username: "<< usuario << " no existe."<< std::endl;
}

