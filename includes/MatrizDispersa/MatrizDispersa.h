//
// Created by tubac on 9/12/2024.
//

#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include "NodoMatriz.h"
#include "../Clases/Usuarios.h"

class MatrizDispersa {
    public:
    //Va a tener dos cabeceras
    NodoMatriz *horizontal;
    NodoMatriz *vertical;

    //Este es el constructor
    MatrizDispersa();

    //********************* Aca van los metodos de la matriz **********
    //Para revisar si la lista esta vacia
    bool estaVacia();

    //Para ver si existe la cavecera
    NodoMatriz *existecabeHorizontal(std::string cabecera);
    NodoMatriz *existecabeVertical(std::string cabecera);

    //Para insertar el valor
    void insertarValor(Usuarios* valor, std::string cabHorizontal, std::string cabVertical);

    //Para insertar las cabeceras
    NodoMatriz *insertarCabeHorizontal(std::string valor);
    NodoMatriz *insertarCabeVertical(std::string valor);

    //Para insertar un nodo a la matriz
    void insertarAlfinal(NodoMatriz *valor, NodoMatriz *cabHorizontal, NodoMatriz *cabVertical);

    //Para insertar en medio de las de la matriz
    void insertarAlfinalH(NodoMatriz *valor, NodoMatriz *cabHorizontal);
    void insertarAlfinalV(NodoMatriz *valor, NodoMatriz *cabVertical);
    void insertarAlMedioH(NodoMatriz *valor, NodoMatriz *horizontal);
    void insertarAlMedioV(NodoMatriz *valor, NodoMatriz *vertical);

    //Esto serviran para encontrar las cebeceras de un usuario en especifico
    NodoMatriz *enCabeceraH(NodoMatriz *nodo);
    NodoMatriz *enCabeceraV(NodoMatriz *nodo);

    //Funcion para saber si el nodo esta mas abajo
    bool masAbajo(NodoMatriz *cabeV, std::string cabV);
    bool masDerecho(NodoMatriz *cabeH, std::string cabH);

    //Funcion para saber el nodo del usuario
    bool existePaswordUser(std::string username, std::string password);

    std::string getNombre();
    Usuarios *getUsuario();

    void generarGrafica();

    void insertarAtras(Usuarios* nuevoUsuario, NodoMatriz* usuarioActual);
    void insertarFrente(Usuarios* nuevoUsuario, NodoMatriz* usuarioActual);

    void generarGraficasDepartamento(std::string departamento);
    void generarImagen(std::string dot);

    void generarGraficasEmpresa(std::string empresa);
    void generarImagenEmpresas(std::string dot);

    void generarGraficaUsuario(std::string usuario);

    void actualizarDatos(NodoMatriz *userActual);
    std::string getDepartamento();
    std::string getEmpresa();
};



#endif //MATRIZDISPERSA_H
