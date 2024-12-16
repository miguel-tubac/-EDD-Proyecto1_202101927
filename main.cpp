#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <random>

using namespace std; //Esto es para evitar colocar delante de cada variable std ::


#include "includes/MatrizDispersa/MatrizDispersa.h"
#include "includes/Clases/Usuarios.h"
#include "includes/Arbol/ClassAVL.h"
#include "includes/Clases/Activos.h"


MatrizDispersa *matrizGeneral = new MatrizDispersa();//Esta sera la matris general

string name = "";

Usuarios *logeado;

//Para pasar a minusculas
string to_lower(string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return s;
}




int obtener_opcion() {
    string entrada;
    int opcion;

    try {
        cin >> entrada;

        // Intentar convertir a entero
        opcion = stoi(entrada);

        // Validar rango
        if (opcion < 1 || opcion > 2) {
            throw out_of_range("Opcion fuera de rango. Elija 1 o 2.");
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Entrada invalida. Por favor, ingrese un numero.");
    } catch (const out_of_range& e) {
        throw out_of_range(e.what());
    }

    return opcion;
}


int obtener_opcion2() {
    string entrada;
    int opcion;

    try {
        cin >> entrada;

        // Intentar convertir a entero
        opcion = stoi(entrada);

        // Validar rango
        if (opcion < 1 || opcion > 9) {
            throw out_of_range("Opcion fuera de rango. Elija entre 1 a 9.");
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Entrada invalida. Por favor, ingrese un numero.");
    } catch (const out_of_range& e) {
        throw out_of_range(e.what());
    }

    return opcion;
}


int obtener_opcion3() {
    string entrada;
    int opcion;

    try {
        cin >> entrada;

        // Intentar convertir a entero
        opcion = stoi(entrada);

        // Validar rango
        if (opcion < 1 || opcion > 7) {
            throw out_of_range("Opcion fuera de rango. Elija entre 1 a 7.");
        }
    } catch (const invalid_argument& e) {
        throw invalid_argument("Entrada invalida. Por favor, ingrese un numero.");
    } catch (const out_of_range& e) {
        throw out_of_range(e.what());
    }

    return opcion;
}


void registrar_usuario() {
    //cin.ignore();
    cout << "\n------------------------ Menu Administrador -----------------------" << endl;
    cout << "------------------------ 1. Registrar Usuario -----------------------" << endl;

    string usuario = "";
    string pasword = "";
    string nombre = "";
    string departamento = "";
    string empresa= "";

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

    //Conversion a minusculas
    departamento = to_lower(departamento);
    empresa = to_lower(empresa);

    //Se crea un arbol ABL vacillo para cada objeto de la matriz
    ClassAVL *nuevo = new ClassAVL();
    //nuevo->insertar(10);

    // Crear el objeto del usuario
    Usuarios* userNuevo = new Usuarios(usuario, nombre, pasword, nuevo);

    // Insertar el usuario en la matriz dispersa
    matrizGeneral->insertarValor(userNuevo, departamento, empresa);
}


void reporte_activos_departamento() {
    string departamento;
    cout << "\n---------------- Reporte Activos Disponibles de un Departamento ---------------" << endl;
    cout << "\nIngresar nombre del Departamento: ";
    cin >> departamento;
    departamento = to_lower(departamento);
    matrizGeneral->generarGraficasDepartamento(departamento);

    /*
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->graficarArbol();*/
}


void menu_admin() {
    int opcion = 0;
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

        try {
            opcion = obtener_opcion2();
            switch(opcion) {
                case 1:
                    cout << "Registrar Usuario..." << endl;
                registrar_usuario();
                break;
                case 2:
                    cout << "Reporte Matriz Dispersa..." << endl;
                matrizGeneral->generarGrafica();
                break;
                case 3:
                    cout << "Reporte Activos Disponibles de un Departamento..." << endl;
                    reporte_activos_departamento();
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
            }
        }catch (const exception& e) {
            cout << e.what() << endl;

            // Limpiar el estado del flujo de entrada si hay caracteres extraños
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << endl;
    }while (opcion != 9);
}


std::string generarCadenaAlfanumerica() {
    const std::string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string resultado;

    int longitud = 15;

    // Configurar el generador aleatorio
    std::random_device dispositivo;
    std::mt19937 generador(dispositivo());
    std::uniform_int_distribution<> distribucion(0, caracteres.size() - 1);

    for (int i = 0; i < longitud; ++i) {
        int indiceAleatorio = distribucion(generador); // Índice aleatorio en el rango de caracteres
        resultado += caracteres[indiceAleatorio];
    }

    return resultado;
}



//Este es el menu de agregar activo:
void menu_activos() {
    cout << "\n------------------------ Agregar Activo -----------------------" << endl;

    string nombreAct;
    string descripcion;
    string ID;

    cin.ignore();//Limpiamos el bufer
    cout << "\nIngresa el nombre de Activo: ";
    std::getline(cin, nombreAct);
    cout << "Ingresa la descripcion del Activo: ";
    std::getline(cin, descripcion);

    ID = generarCadenaAlfanumerica();

    //Aca se crea el objeto de activo que ira dentro del arbol
    Activos *activoNuevo = new Activos(nombreAct, descripcion);

    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    //Se obtiene el ArbolABl del Usuario
    ClassAVL *nuevo = logeado->arbol;
    nuevo->insertar(ID, activoNuevo); //Esta es la forma correcta

    //cout << "Este es el ID: " << ID << endl;
}


void eliminar_activos() {
    string idActivo;
    cout << "\n------------------------ Eliminar Activo -----------------------" << endl;
    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->mostrarActivos();
    cout << "\nIngresa el ID del Activo: ";
    cin >> idActivo;
    logeado->arbol->eliminar(idActivo);
}

void modificar_activos() {
    string idActivo;
    string nuevaDescripcion;
    cout << "\n------------------------ Modificar Activo -----------------------" << endl;
    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->mostrarActivos();
    cout << "\nIngresa el ID del Activo: ";
    cin >> idActivo;
    cin.ignore();//Limpiamos el bufer
    cout << "Ingresa la nueva descripcion del Activo: ";
    std::getline(cin, nuevaDescripcion);
    logeado->arbol->modificarActivo(idActivo, nuevaDescripcion);
}


void retar_activos() {
    string idActivo;
    int tiemporenta;
    cout << "\n------------------------ Rentar Activo -----------------------" << endl;
    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->mostrarActivosConTiempo();
    cout << "\nIngresa el ID del Activo a Rentar: ";
    cin >> idActivo;
    cout << "Ingresar los Días por Rentar: ";
    cin >> tiemporenta;
    logeado->arbol->modificarRentaActivo(idActivo, tiemporenta);
}

void retornar_activos() {
    string idActivo;
    cout << "\n------------------------ Devolucion de Activo -----------------------" << endl;
    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->mostrarActivosRentados();
    cout << "\nIngresa el ID del Activo a Devolver: ";
    cin >> idActivo;
    logeado->arbol->modificarDevolucionActivo(idActivo);
}


void mostrar_activos_Rentados() {
    cout << "\n------------------------ Lista de Activos Rentados -----------------------" << endl;
    //Se obtiene el objeto Usuario
    logeado = matrizGeneral->getUsuario();
    logeado->arbol->mostrarActivosRentados();
    cout << "\nPresione Enter para continuar..." << endl;
    cin.ignore(); // Ignorar cualquier entrada previa
    cin.get();    // Esperar hasta que el usuario presione "Enter"
}

//Este es el menu del usuario
void menu_user() {
    int opcion = 0;
    name = matrizGeneral->getNombre();
    do {
        cout << "\n------------------------ Bienvenido: "<< name <<" -----------------------" << endl;
        cout << "1. Agregar Activo" << endl;
        cout << "2. Eliminar Activo" << endl;
        cout << "3. Modificar Activo" << endl;
        cout << "4. Rentar Activo" << endl;
        cout << "5. Devolucion de Activos Rentados" << endl;
        cout << "6. Mis Activos Rentados" << endl;
        cout << "7. Cerrar Sesion" << endl;
        cout << "\nIngrese una opcion: ";
        //cin >> opcion;

        try {
            opcion = obtener_opcion3();
            switch(opcion) {
                case 1:
                    cout << "Agregar Activo..." << endl;
                menu_activos();
                break;
                case 2:
                    cout << "Eliminar Activo..." << endl;
                    eliminar_activos();
                break;
                case 3:
                    cout << "Modificar Activo..." << endl;
                modificar_activos();
                break;
                case 4:
                    cout << "Rentar Activo..." << endl;
                retar_activos();
                break;
                case 5:
                    cout << "Devolucion de Activos Rentados..." << endl;
                retornar_activos();
                break;
                case 6:
                    cout << "Mis Activos Rentados...\n" << endl;
                mostrar_activos_Rentados();
                break;
                case 7:
                    cout << "....Finalizando Sesion....." << endl;
                break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;

            // Limpiar el estado del flujo de entrada si hay caracteres extraños
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        cout << "Ingrese el usuario: ";
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



void agregar_usuariosIniciales() {
    string ID = generarCadenaAlfanumerica();
    //Aqui va un activo ingresado
    ClassAVL *nuevo = new ClassAVL();
    Activos *activoNuevo = new Activos("Televisores", "Son de 32 Pulgadas.");
    nuevo->insertar(ID, activoNuevo);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo2 = new Activos("Relojes", "Relojes marca Rolex.");
    nuevo->insertar(ID, activoNuevo2);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo3 = new Activos("Pelotas", "Pelotas de color rojo.");
    nuevo->insertar(ID, activoNuevo3);
    //Aca se incertan a la matriz dispersa
    Usuarios* userNuevo = new Usuarios("miguel", "Miguel Adrian", "1234", nuevo);
    matrizGeneral->insertarValor(userNuevo, "guate", "max");
}


int main() {
    agregar_usuariosIniciales();
    int opcion = 0;

    do {
        cout << "\n------------------------ Renta de Activos -----------------------" << endl;
        cout << "1. Iniciar Sesion" << endl;
        cout << "2. Salir" << endl;
        cout << "Ingrese una opcion: ";

        try {
            opcion = obtener_opcion();
            switch (opcion) {
                case 1:
                    iniciar_sesion();
                break;
                case 2:
                    cout << "Saliendo del programa..." << endl;
                break;
                default:
                    // Este caso no ocurrirá debido a la validación en obtener_opcion().
                        break;
            }
        } catch (const exception& e) {
            cout << e.what() << endl;

            // Limpiar el estado del flujo de entrada si hay caracteres extraños
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << endl;
    } while (opcion != 2);

    return 0;
}





