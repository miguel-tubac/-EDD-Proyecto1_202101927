cmake_minimum_required(VERSION 3.30)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_1 main.cpp
        includes/MatrizDispersa/NodoMatriz.h
        src/MatrizDispersa/NodoMatriz.cpp
        includes/MatrizDispersa/MatrizDispersa.h
        src/MatrizDispersa/MatrizDispersa.cpp)
