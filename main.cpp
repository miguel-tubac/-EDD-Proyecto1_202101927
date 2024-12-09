#include <iostream>

using namespace std; //Esto es para evitar colocar delante de cada variable std ::


#include "includes/MatrizDispersa/MatrizDispersa.h"

int main() {
    /*
     *Ejemplo de como insertar un valor en la matriz
    MatrizDispersa *matriz = new MatrizDispersa();
    matriz->insertarValor(5, 0, 0);*/

    int opcion;
    do {
        cout << "\n------------------------ Renta de Activos -----------------------" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Iniciando sesion..." << endl;
                break;
            case 2:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
        }

        cout << endl;
    } while(opcion != 2);

    return 0;
}




