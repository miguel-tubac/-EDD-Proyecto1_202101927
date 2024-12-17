#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <random>
#include <ctime>

using namespace std; //Esto es para evitar colocar delante de cada variable std ::


#include "includes/MatrizDispersa/MatrizDispersa.h"
#include "includes/Clases/Usuarios.h"
#include "includes/Arbol/ClassAVL.h"
#include "includes/Clases/Activos.h"
#include "includes/ListaDobleCircular/ListaEnlazadaDobleCircu.h"
#include "includes/Clases/Transacciones.h"


MatrizDispersa *matrizGeneral = new MatrizDispersa();//Esta sera la matris general
ListaEnlazadaDobleCircu *listaGeneral = new ListaEnlazadaDobleCircu();

//Son los datos del usuario logeado
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
    cin.ignore();
    std::getline(cin, departamento);
    departamento = to_lower(departamento);
    matrizGeneral->generarGraficasDepartamento(departamento);
}


void reporte_activos_empresa() {
    string empresa;
    cout << "\n---------------- Reporte Activos Disponibles de un Empresa ---------------" << endl;
    cout << "\nIngresar nombre de la Empresa: ";
    cin.ignore();
    std::getline(cin, empresa);
    empresa = to_lower(empresa);
    matrizGeneral->generarGraficasEmpresa(empresa);
}


void reporte_activos_usuario() {
    string usuario;
    cout << "\n---------------- Reporte Activos de un Usuario ---------------" << endl;
    cout << "\nIngresar username: ";
    cin >> usuario;
    matrizGeneral->generarGraficaUsuario(usuario);
}

void reporte_activos_rentados_usuario() {
    string usuario;
    cout << "\n---------------- Activos rentados por un Usuario ---------------" << endl;
    cout << "\nIngresar username: ";
    cin >> usuario;
    listaGeneral->graficarUsuario(usuario);
}


void ordenar_transacciones() {
    int opcion = 0;
    cout << "\n------------------------ Ordenar Transacciones -----------------------" << endl;
    cout << "1. Acendente" << endl;
    cout << "2. Decendente" << endl;
    cout << "\nIngresar opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        listaGeneral->ordenarAscendente();
        cout << "...La lista se Ordeno de manera Acendete Correctamnte..." << endl;
    }else if (opcion == 2) {
        listaGeneral->ordenarDesendente();
        cout << "...La lista se Ordeno de manera Decendente Correctamnte..." << endl;
    }
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
                    reporte_activos_empresa();
                    break;
                case 5:
                    cout << "Reporte Transacciones..." << endl;
                    listaGeneral->graficar();
                    break;
                case 6:
                    cout << "Reporte Activos de un Usuario..." << endl;
                    reporte_activos_usuario();
                    break;
                case 7:
                    cout << "Activos rentados por un Usuario..." << endl;
                    reporte_activos_rentados_usuario();
                    break;
                case 8:
                    cout << "Ordenar Transacciones" << endl;
                    ordenar_transacciones();
                    break;
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


// Función que devuelve la fecha actual en formato "AAAA-MM-DD"
std::string obtenerFechaActual() {
    // Obtenemos el tiempo actual
    std::time_t tiempoActual = std::time(nullptr);

    // Convertimos a una estructura tm
    std::tm* fechaLocal = std::localtime(&tiempoActual);

    // Formateamos la fecha como "AAAA-MM-DD"
    char buffer[11]; // Espacio suficiente para "AAAA-MM-DD\0"
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", fechaLocal);

    // Devolvemos la fecha como una cadena
    return std::string(buffer);
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

void agregar_transaccion(std::string idActivo, std::string departamento, std::string empresa, int tiempo) {
    string DI = generarCadenaAlfanumerica();
    string fecha = obtenerFechaActual();
    Transacciones *nuevaTransaccion = new Transacciones(idActivo,logeado->usuar, departamento, empresa,fecha ,tiempo);
    listaGeneral->agregar(DI, nuevaTransaccion);
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
    bool validacion = logeado->arbol->modificarRentaActivo(idActivo, tiemporenta);
    if (validacion) {
        agregar_transaccion(idActivo, matrizGeneral->getDepartamento(), matrizGeneral->getEmpresa(), tiemporenta);
    }
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


void agregar_transaccion_Inicio(std::string idActivo, std::string user, std::string departamento, std::string empresa, int tiempo) {
    string DI = generarCadenaAlfanumerica();
    string fecha = obtenerFechaActual();
    Transacciones *nuevaTransaccion = new Transacciones(idActivo,user, departamento, empresa,fecha ,tiempo);
    listaGeneral->agregar(DI, nuevaTransaccion);
}


void agregar_usuariosIniciales() {
    bool validacion;
    string ID = generarCadenaAlfanumerica();
    //Aqui va un activo ingresado
    ClassAVL *nuevo = new ClassAVL();
    Activos *activoNuevo = new Activos("madera", "madera para albanil");
    nuevo->insertar(ID, activoNuevo);
    validacion = nuevo->modificarRentaActivo(ID, 20);
    agregar_transaccion_Inicio(ID,"elian_estrada", "guatemala", "igss", 20);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo2 = new Activos("martillos", "martillos para madera");
    nuevo->insertar(ID, activoNuevo2);
    validacion = nuevo->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"elian_estrada", "guatemala", "igss", 10);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo3 = new Activos("caladora", "caladora para cortar maderas prefabricadas");
    nuevo->insertar(ID, activoNuevo3);
    validacion = nuevo->modificarRentaActivo(ID, 15);
    agregar_transaccion_Inicio(ID,"elian_estrada", "guatemala", "igss", 15);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo4 = new Activos("barreno", "barreno para concreto");
    nuevo->insertar(ID, activoNuevo4);
    validacion = nuevo->modificarRentaActivo(ID, 5);
    agregar_transaccion_Inicio(ID,"elian_estrada", "guatemala", "igss", 5);
    //Aca se incertan a la matriz dispersa
    Usuarios* userNuevo = new Usuarios("elian_estrada", "Elian Estrada", "1234", nuevo);
    matrizGeneral->insertarValor(userNuevo, "guatemala", "igss");

    //Este es el segundo usuario

    ClassAVL *nuevo2 = new ClassAVL();
    Usuarios* userNuevo2 = new Usuarios("juanito", "Juan Perez", "4567", nuevo2);
    matrizGeneral->insertarValor(userNuevo2, "jutiapa", "max");

    //Este es el Tercer usuario

    //Aqui va un activo ingresado
    ID = generarCadenaAlfanumerica();
    ClassAVL *nuevo3 = new ClassAVL();
    Activos *activoNuevo5 = new Activos("balanza", "balanza con maximo de 25kg");
    nuevo3->insertar(ID, activoNuevo5);
    validacion = nuevo3->modificarRentaActivo(ID, 15);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 15);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo6 = new Activos("canastas", "canastas para frutas y verduras");
    nuevo3->insertar(ID, activoNuevo6);
    validacion = nuevo3->modificarRentaActivo(ID, 45);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 45);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo7 = new Activos("linternas", "linternas para alumbrar cuartos oscuros");
    nuevo3->insertar(ID, activoNuevo7);
    validacion = nuevo3->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 10);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo8 = new Activos("cargadores", "cargadores de telefonos tipo c");
    nuevo3->insertar(ID, activoNuevo8);
    validacion = nuevo3->modificarRentaActivo(ID, 5);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 5);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo9 = new Activos("cables", "cables de todo tipo");
    nuevo3->insertar(ID, activoNuevo9);
    validacion = nuevo3->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 10);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo10 = new Activos("lazos", "lazos para tender ropa");
    nuevo3->insertar(ID, activoNuevo10);
    validacion = nuevo3->modificarRentaActivo(ID, 20);
    agregar_transaccion_Inicio(ID,"casimiro", "guatemala", "max", 20);
    //Aca se incertan a la matriz dispersas
    Usuarios* userNuevo3 = new Usuarios("casimiro", "Carlos Perez", "721896", nuevo3);
    matrizGeneral->insertarValor(userNuevo3, "guatemala", "max");

    //Este es el cuarto usuario

    ClassAVL *nuevo4 = new ClassAVL();
    Usuarios* userNuevo4 = new Usuarios("pedrito", "Pedro Rodriguez", "48956", nuevo4);
    matrizGeneral->insertarValor(userNuevo4, "jalapa", "usac");

    //Este es el quinto usuario

    //Aqui va un activo ingresado
    ID = generarCadenaAlfanumerica();
    ClassAVL *nuevo5 = new ClassAVL();
    Activos *activoNuevo11 = new Activos("audifonos", "audifonos para grabaciones de estudio");
    nuevo5->insertar(ID, activoNuevo11);
    validacion = nuevo5->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"mafer", "peten", "cinepolis", 10);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo12 = new Activos("microfonos", "microfonos de todo tipo");
    nuevo5->insertar(ID, activoNuevo12);
    validacion = nuevo5->modificarRentaActivo(ID, 8);
    agregar_transaccion_Inicio(ID,"mafer", "peten", "cinepolis", 8);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo13 = new Activos("pedestales", "pedestales para microfonos grandes y pequeños");
    nuevo5->insertar(ID, activoNuevo13);
    validacion = nuevo5->modificarRentaActivo(ID, 12);
    agregar_transaccion_Inicio(ID,"mafer", "peten", "cinepolis", 12);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo14 = new Activos("atriles", "atriles para colocar ojas con gancho");
    nuevo5->insertar(ID, activoNuevo14);
    validacion = nuevo5->modificarRentaActivo(ID, 14);
    agregar_transaccion_Inicio(ID,"mafer", "peten", "cinepolis", 14);
    //Aca se incertan a la matriz dispersas
    Usuarios* userNuevo5 = new Usuarios("mafer", "Maria Fernanda", "54312", nuevo5);
    matrizGeneral->insertarValor(userNuevo5, "peten", "cinepolis");

    //Este es el usuario numero sexto

    ClassAVL *nuevo6 = new ClassAVL();
    Usuarios* userNuevo6 = new Usuarios("juanma", "Juan Manuel", "32897", nuevo6);
    matrizGeneral->insertarValor(userNuevo6, "guatemala", "usac");

    //Este es el usuario numero septimo

    //Aqui va un activo ingresado
    ID = generarCadenaAlfanumerica();
    ClassAVL *nuevo7 = new ClassAVL();
    Activos *activoNuevo15 = new Activos("termos", "pequeños termos para bebidas calientes");
    nuevo7->insertar(ID, activoNuevo15);
    validacion = nuevo7->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"fuego03", "jutiapa", "cinepolis", 10);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo16 = new Activos("maletas", "maletas desde pequeñas a grandes");
    nuevo7->insertar(ID, activoNuevo16);
    validacion = nuevo7->modificarRentaActivo(ID, 15);
    agregar_transaccion_Inicio(ID,"fuego03", "jutiapa", "cinepolis", 15);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo17 = new Activos("peliculas", "todo tipo de peliculas de accion");
    nuevo7->insertar(ID, activoNuevo17);
    validacion = nuevo7->modificarRentaActivo(ID, 5);
    agregar_transaccion_Inicio(ID,"fuego03", "jutiapa", "cinepolis", 5);
    //Aca se incertan a la matriz dispersas
    Usuarios* userNuevo7 = new Usuarios("fuego03", "Fernando Mendez", "891346", nuevo7);
    matrizGeneral->insertarValor(userNuevo7, "jutiapa", "cinepolis");

    //Este es el usuario numero octavo

    ClassAVL *nuevo8 = new ClassAVL();
    Usuarios* userNuevo8 = new Usuarios("azurdia", "Alejandra Guzman", "780145", nuevo8);
    matrizGeneral->insertarValor(userNuevo8, "jutiapa", "usac");

    //Esta es el usuario numero noveno
    //Aqui va un activo ingresado
    ID = generarCadenaAlfanumerica();
    ClassAVL *nuevo9 = new ClassAVL();
    Activos *activoNuevo18 = new Activos("casest", "casets con musica de todo tipo");
    nuevo9->insertar(ID, activoNuevo18);
    validacion = nuevo9->modificarRentaActivo(ID, 5);
    agregar_transaccion_Inicio(ID,"incrediboy", "jutiapa", "max", 5);
    //Este es el segundo activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo19 = new Activos("pantallas", "pantallas para proyección");
    nuevo9->insertar(ID, activoNuevo19);
    validacion = nuevo9->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"incrediboy", "jutiapa", "max", 10);
    //Este es el tercer activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo20 = new Activos("cañonera", "cañonera para proyeccion");
    nuevo9->insertar(ID, activoNuevo20);
    validacion = nuevo9->modificarRentaActivo(ID, 10);
    agregar_transaccion_Inicio(ID,"incrediboy", "jutiapa", "max", 10);
    //Este es el cuarto activo
    ID = generarCadenaAlfanumerica();
    Activos *activoNuevo21 = new Activos("toldo", "toldo para eventos al exterior");
    nuevo9->insertar(ID, activoNuevo21);
    validacion = nuevo9->modificarRentaActivo(ID, 5);
    agregar_transaccion_Inicio(ID,"incrediboy", "jutiapa", "max", 5);
    //Aca se incertan a la matriz dispersas
    Usuarios* userNuevo9 = new Usuarios("incrediboy", "Iraldo Martinez", "201598", nuevo9);
    matrizGeneral->insertarValor(userNuevo9, "jutiapa", "max");

    //Este es el usuario decimo

    ClassAVL *nuevo10 = new ClassAVL();
    Usuarios* userNuevo10 = new Usuarios("alcachofa", "Antonio Lopez", "20435", nuevo10);
    matrizGeneral->insertarValor(userNuevo10, "jalapa", "usac");

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





