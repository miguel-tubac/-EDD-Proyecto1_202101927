//
// Created by tubac on 16/12/2024.
//

#include "../../includes/Clases/Transacciones.h"

Transacciones::Transacciones(std::string idActivo, std::string usuario, std::string departamento, std::string empresa, std::string fecha, int timpoRenta) {
    this->idActivo = idActivo;
    this->usuario = usuario;
    this->departamento = departamento;
    this->empresa = empresa;
    this->fecha = fecha;
    this->timpoRenta = timpoRenta;
}

