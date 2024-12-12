cmake_minimum_required(VERSION 3.30)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_1 main.cpp
        includes/MatrizDispersa/NodoMatriz.h
        src/MatrizDispersa/NodoMatriz.cpp
        includes/MatrizDispersa/MatrizDispersa.h
        src/MatrizDispersa/MatrizDispersa.cpp
        includes/Clases/Usuarios.h
        src/Clases/Usuarios.cpp
        includes/Arbol/Nodo_ABL.h
        src/Arbol/Nodo_ABL.cpp
        src/Arbol/ClassABL.cpp
        includes/Arbol/ClassABL.h)
