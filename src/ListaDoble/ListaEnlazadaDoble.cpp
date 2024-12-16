//
// Created by tubac on 16/12/2024.
//
#include "../../includes/ListaDoble/ListaEnlazadaDoble.h"

#include <iostream>
#include <fstream>
#include <cstdlib>//esta nos permite acceder al sistema y ejucar comandos como si fuera la consola
#include <string>
//using namespace std;

ListaEnlazadaDoble::ListaEnlazadaDoble() : inicio(nullptr), fin(nullptr) {}

void ListaEnlazadaDoble::agregar(std::string ID, Transacciones *transaccion) {
    Node3* newNode = new Node3(ID, transaccion);
    if (fin == nullptr) {
        inicio = fin = newNode;
    } else {
        fin->next = newNode;
        newNode->prev = fin;
        fin = newNode;
    }
}

bool ListaEnlazadaDoble::isEmpty() const {
    return inicio == nullptr;
}

void ListaEnlazadaDoble::graficar(){
    if (isEmpty()){
        std::cout << "La Lista Enlazada Doble esta vacia." << std::endl;
        return;
    }

    //Ahora empezamos a concatenar los datos del ast
    std::string dot ="digraph G { randir = LR;";
    dot += "\n\tlabel = \"Lista Enlazada Doble\";"; // Título de la gráfica
    dot += "\n\tlabelloc = \"t\";"; // Posición del título (t = top)
    dot += "\n\tfontsize = 20;"; // Tamaño de la fuente del título

    //Ahora aqui se agregaran los nodos:
    Node3* actual = inicio;
    Node3* repaldo = nullptr;
    while (actual != nullptr) {
        dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
        actual = actual->next;
        //Esto es para el ultimo nodo
        if (actual != nullptr){
            dot += "->";
        }

    }
    actual = fin;
    //cout << "Vuelo: " <<actual->data->vuelo <<endl;
    while (actual != nullptr) {
        dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
        actual = actual->prev;
        //Esto es para el ultimo nodo
        if (actual != nullptr){
            dot += "->";
        }
    }

    //Aca se cierra el archivo .dot
    dot += "\n}";

    // Escribir el archivo DOT
    std::ofstream file;
    file.open("../src/Reportes/lista_doble.dot");

    if (file.is_open()) {
        file << dot;
        file.close();
    }

    int resultado = std::system("dot -Tpng ../src/Reportes/lista_doble.dot -o ../src/Reportes/lista_doble.png");
    if (resultado == 0) {
        std::cout << "Imagen lista_doble.png generada exitosamente." << std::endl;
    } else {
        std::cout << "Error al generar la imagen lista_doble.png" << std::endl;
    }

}



