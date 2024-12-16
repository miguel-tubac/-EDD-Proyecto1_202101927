//
// Created by tubac on 16/12/2024.
//

#ifndef TRANSACCIONES_H
#define TRANSACCIONES_H
#include <string>

class Transacciones {
    public:
    std::string idActivo;
    std::string usuario;
    std::string departamento;
    std::string empresa;
    std::string fecha;
    int timpoRenta;

    Transacciones(std::string idActivo, std::string usuario, std::string departamento,std::string empresa, std::string fecha, int timpoRenta);
};

#endif //TRANSACCIONES_H
