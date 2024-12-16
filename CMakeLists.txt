cmake_minimum_required(VERSION 3.22)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_1 main.cpp
        includes/MatrizDispersa/NodoMatriz.h
        src/MatrizDispersa/NodoMatriz.cpp
        includes/MatrizDispersa/MatrizDispersa.h
        src/MatrizDispersa/MatrizDispersa.cpp
        includes/Clases/Usuarios.h
        src/Clases/Usuarios.cpp
        includes/Arbol/Nodo_AVL.h
        src/Arbol/Nodo_AVL.cpp
        src/Arbol/ClassAVL.cpp
        includes/Arbol/ClassAVL.h
        includes/Clases/Activos.h
        src/Clases/Activos.cpp
        includes/Clases/Transacciones.h
        src/Clases/Transacciones.cpp
        includes/ListaDobleCircular/ListaEnlazadaDobleCircu.h
        src/ListaDobleCircular/ListaEnlazadaDobleCircu.cpp
)
