#include <iostream>

using namespace std; //Esto es para evitar colocar delante de cada variable std ::


#include "includes/MatrizDispersa/MatrizDispersa.h"
#include "includes/Clases/Usuarios.h"


MatrizDispersa *matrizGeneral = new MatrizDispersa();//Esta sera la matris general

string name = "";

void registrar_usuario() {
    cout << "\n------------------------ Menu Administrador -----------------------" << endl;
    cout << "------------------------ 1. Registrar Usuario -----------------------" << endl;

    string usuario;
    string pasword;
    string nombre;
    string departamento;
    string empresa;

    cout << "Ingresa Username: ";
    cin >> usuario;
    cin.ignore(); // Limpiar el buffer de entrada para evitar problemas con getline
    cout << "Ingresar Password: ";
    cin >> pasword;
    cin.ignore(); // Limpiar el buffer de entrada para evitar problemas con getline
    cout << "Ingresar Nombre: ";
    std::getline(cin, nombre);
    cout << "Ingresar Departamento: ";
    std::getline(cin, departamento);
    cout << "Ingresar Empresa: ";
    std::getline(cin, empresa);

    // Crear el objeto del usuario
    Usuarios* userNuevo = new Usuarios(usuario, nombre, pasword);

    // Insertar el usuario en la matriz dispersa
    matrizGeneral->insertarValor(userNuevo, departamento, empresa);
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



//Este es el menu del usuario
void menu_user() {
    int opcion;
    name = matrizGeneral->getNombre();
    do {
        cout << "\n------------------------ "<< name <<" -----------------------" << endl;
        cout << "1. Agregar Activo" << endl;
        cout << "2. Eliminar Activo" << endl;
        cout << "3. Modificar Activo" << endl;
        cout << "4. Rentar Activo" << endl;
        cout << "5. Activos Rentados" << endl;
        cout << "6. Mis Activos Rentados" << endl;
        cout << "7. Cerrar Sesion" << endl;
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
                cout << "....Finalizando Sesion....." << endl;
            break;
            default:
                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
        }

        cout << endl;
    }while (opcion != 7);
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

        if (matrizGeneral->existePaswordUser(usuario, contra)) {
            break;
        }

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
    }else {
        menu_user();
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





