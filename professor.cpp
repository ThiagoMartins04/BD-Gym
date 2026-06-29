#include "professor.h"

// GETTERS
int Professor::getId() {
    return id;
}

double Professor::getSalario() {
    return salario;
}

int Professor::getIdEspecialidade() {
    return id_especialidade;
}

string Professor::getTurno() {
    return turno;
}

// SETTERS
bool Professor::setId(int id) {
    if (id <= 0) return false;
    this->id = id;
    return true;
}

bool Professor::setSalario(double salario) {
    if (salario < 0) return false;
    this->salario = salario;
    return true;
}

bool Professor::setIdEspecialidade(int id_especialidade) {
    if (id_especialidade <= 0) return false;
    this->id_especialidade = id_especialidade;
    return true;
}

bool Professor::setTurno(string turno) {
    if (turno != "MANHA" && turno != "TARDE" && turno != "NOITE")
        return false;

    this->turno = turno;
    return true;
}
