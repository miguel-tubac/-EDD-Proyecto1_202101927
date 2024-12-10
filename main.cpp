#include <iostream>

using namespace std; //Esto es para evitar colocar delante de cada variable std ::


#include "includes/MatrizDispersa/MatrizDispersa.h"


void registrar_usuario() {
    cout << "\n------------------------ Menu Administrador -----------------------" << endl;
    cout << "------------------------ 1. Registrar Usuario -----------------------" << endl;
    string usuario;
    string pasword;
    string departamento;
    string empresa;

    cout << "Ingresar Usuario: ";
    cin >> usuario;
    cout << "Ingresar Password: ";
    cin >> pasword;
    cout << "Ingresar Departamento: ";
    cin >> departamento;
    cout << "Ingresar Empresa: ";
    cin >> empresa;

    /*
     *Ejemplo de como insertar un valor en la matriz
    MatrizDispersa *matriz = new MatrizDispersa();

    insertarValor(int valor, int cabHorizontal, int cabVertical)
    int valor: objeto usuarioss(usuario, pasword)
    matriz->insertarValor(usuarioss, departamento, empresa)

    matriz->insertarValor(5, 0, 0);*/
}


void menu_admin() {
    int opcion;
    do {
        cout << "\n------------------------ Menu Administrador -----------------------" << endl;
        cout << "1. Registrar Usuario" << endl;
        cout << "2. Reporte Matriz Dispersa" << endl;
        cout << "3. Reporte Activos Disponibles de un Departamento " << endl;
        cout << "4. Reporte Activos Disponibles de una Empresa" << endl;
        cout << "5. Reporte Transacciones " << endl;
        cout << "6. Reporte Activos de un Usuario" << endl;
        cout << "7. Activos rentados por un Usuario" << endl;
        cout << "8. Ordenar Transacciones" << endl;
        cout << "9. Finalizar Sesion" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "Registrar Usuario..." << endl;
                registrar_usuario();
                break;
            case 2:
                cout << "Reporte Matriz Dispersa..." << endl;
                break;
            case 3:
                cout << "Reporte Activos Disponibles de un Departamento..." << endl;
                break;
            case 4:
                cout << "Reporte Activos Disponibles de una Empresa..." << endl;
                break;
            case 5:
                cout << "Reporte Transacciones..." << endl;
                break;
            case 6:
                cout << "Reporte Activos de un Usuario..." << endl;
                break;
            case 7:
                cout << "Activos rentados por un Usuario..." << endl;
                break;
            case 8:
                cout << "Ordenar Transacciones" << endl;
            case 9:
                cout << "....Finalizando Sesion....." << endl;
                break;
            default:
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
        }

        cout << endl;
    }while (opcion != 9);
}


void iniciar_sesion() {
    string usuarioAdmin = "admin";
    string contraAdmin = "admin";

    string usuario;
    string contra;

    bool correcto = false;

    do {
        cout << "\n------------------------ Renta de Activos -----------------------" << endl;
        cout << "------------------------ 1. Iniciar Sesion -----------------------" << endl;
        cout << "Ingrese el usuario: " ;
        cin >> usuario;
        cout << "Ingrese la contrasena: ";
        cin >> contra;

        if (usuarioAdmin == usuario && contraAdmin == contra) {
            correcto = true;
            break;
        }
        cout << "\nError: Usuario o contasena incorrectos, intente de nuevo" << endl;
        cout << "Presione Enter para continuar..." << endl;
        cin.ignore(); // Ignorar cualquier entrada previa
        cin.get();    // Esperar hasta que el usuario presione "Enter"
    }while (!correcto);

    if (correcto) {
        menu_admin();
    }
}


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
                //cout << "Iniciando sesion..." << endl;
                iniciar_sesion();
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





