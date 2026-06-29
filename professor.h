#pragma once
#include <string>
using namespace std;

class Professor {
private:
    int id;
    double salario;
    int id_especialidade;
    string turno;

public:
    int getId();
    double getSalario();
    int getIdEspecialidade();
    string getTurno();

    bool setId(int id);
    bool setSalario(double salario);
    bool setIdEspecialidade(int id_especialidade);
    bool setTurno(string turno);
};
