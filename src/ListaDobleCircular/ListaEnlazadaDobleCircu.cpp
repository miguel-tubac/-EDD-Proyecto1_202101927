//
// Created by tubac on 16/12/2024.
//
#include "../../includes/ListaDobleCircular/ListaEnlazadaDobleCircu.h"

#include <iostream>
#include <fstream>
#include <cstdlib>//esta nos permite acceder al sistema y ejucar comandos como si fuera la consola
#include <string>
//using namespace std;

ListaEnlazadaDobleCircu::ListaEnlazadaDobleCircu() : inicio(nullptr) {}

void ListaEnlazadaDobleCircu::agregar(std::string ID, Transacciones *transaccion) {
    Node3* newNode = new Node3(ID, transaccion);
    if (inicio == nullptr) {
        inicio = newNode;
        inicio->next = inicio;
        inicio->prev = inicio;
    } else {
        Node3* cola = inicio->prev;
        cola->next = newNode;
        newNode->prev = cola;
        newNode->next = inicio;
        inicio->prev = newNode;
    }
}





void ListaEnlazadaDobleCircu::ordenarAscendente() {
    if (inicio == nullptr || inicio->next == inicio) {
        // La lista está vacía o tiene un solo nodo, no necesita ordenarse
        return;
    }

    bool swapped;
    Node3* limite = nullptr;

    do {
        swapped = false;
        Node3* actual = inicio;

        // Recorremos la lista hasta el nodo límite o hasta regresar al inicio
        while (actual->next != limite) {
            Node3* siguiente = actual->next;
            if (actual->ID > siguiente->ID) {
                // Intercambiamos los datos de los nodos
                std::swap(actual->ID, siguiente->ID);
                std::swap(actual->data, siguiente->data);
                swapped = true;
            }
            actual = actual->next;

            // Si regresamos al inicio, rompemos el bucle
            if (actual == inicio) {
                break;
            }
        }

        // Actualizamos el límite al último nodo procesado
        limite = actual;
    } while (swapped);
}





void ListaEnlazadaDobleCircu::ordenarDesendente() {
    if (inicio == nullptr || inicio->next == inicio) {
        // La lista está vacía o tiene un solo nodo, no necesita ordenarse
        return;
    }

    bool swapped;
    Node3* limite = nullptr;

    do {
        swapped = false;
        Node3* actual = inicio;

        // Recorremos la lista hasta el nodo límite o hasta regresar al inicio
        while (actual->next != limite) {
            Node3* siguiente = actual->next;
            if (actual->ID < siguiente->ID) {
                // Intercambiamos los datos de los nodos
                std::swap(actual->ID, siguiente->ID);
                std::swap(actual->data, siguiente->data);
                swapped = true;
            }
            actual = actual->next;

            // Si regresamos al inicio, rompemos el bucle
            if (actual == inicio) {
                break;
            }
        }

        // Actualizamos el límite al último nodo procesado
        limite = actual;
    } while (swapped);
}






void ListaEnlazadaDobleCircu::graficar(){
    if (inicio == nullptr) {
        std::cout << "La Lista Curcular Doble esta vacia." << std::endl;
        return;
    }

    //Ahora empezamos a concatenar los datos del ast
    std::string dot = "digraph G { randir = LR;";
    dot += "\n\tlabel = Transacciones;"; // Título de la gráfica
    dot +="\n\tlabelloc = \"t\";"; // Posición del título (t = top)
    dot += "\n\tfontsize = 20;"; // Tamaño de la fuente del título
    //Ahora aqui se agregaran los nodos:
    Node3* actual = inicio;
    do {
        dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
        dot += "->";
        actual = actual->next;
        //Esto es para el ultimo nodo
        if (actual == inicio){
            dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
            dot += "->";
        }
    } while (actual != inicio);

    //Aca lo recorremos hacia atras para generar las flechas que indiquen la direccion contraria:
    actual = actual->prev;
    do {
        dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
        dot += "->";
        actual = actual->prev;
        //Esto es para el ultimo nodo
        if (actual == inicio){
            dot += "\n\"ID: "+actual->ID +"\n\nID Activo: "+ actual->data->idActivo+"\nUsername: "+actual->data->usuario+"\nDepartamento: "+actual->data->departamento+"\nEmpresa: "+actual->data->empresa+"\nFecha: "+actual->data->fecha+"\nTeimpo renta: "+std::to_string(actual->data->timpoRenta)+"\"";
        }
    } while (actual != inicio);


    //Aca se cierra el archivo .dot
    // Cerrar el archivo DOT
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


