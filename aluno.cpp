#include "aluno.h"

// GETTERS
int Aluno::getId() {
    return id;
}

double Aluno::getPeso() {
    return peso;
}

double Aluno::getAltura() {
    return altura;
}

int Aluno::getIdPlano() {
    return id_plano;
}

// SETTERS
bool Aluno::setId(int id) {
    if (id <= 0) return false;
    this->id = id;
    return true;
}

bool Aluno::setPeso(double peso) {
    if (peso <= 0) return false;
    this->peso = peso;
    return true;
}

bool Aluno::setAltura(double altura) {
    if (altura <= 0) return false;
    this->altura = altura;
    return true;
}

bool Aluno::setIdPlano(int id_plano) {
    if (id_plano <= 0) return false;
    this->id_plano = id_plano;
    return true;
}

bool Aluno::alterarAltura(MYSQL* conexao) {
    double alturaNova = 0;
    do {
        system("cls");
        cout << "Digite a altura atual: ";
        cin >> alturaNova;
    } while (!this->setAltura(alturaNova));

    string alturaNovaString = to_string(alturaNova);
    for (char &c : alturaNovaString) {
        if (c == ',') c = '.';
    }

    string vQuery = "UPDATE ALUNO SET ALTURA = " + alturaNovaString + " WHERE ID = " + to_string(this->id);

    if(mysql_query(conexao, vQuery.c_str())) {
        system("cls");
        cout << mysql_error(conexao);
        system("pause");
        return false;
    } else {
        system("cls");
        cout << "Dados inseridos com sucesso!" << endl << endl;
        system("pause");
    }

    return true;
}

bool Aluno::alterarPeso(MYSQL* conexao) {
    double pesoNovo = 0;
    do {
        system("cls");
        cout << "Digite o peso atual: ";
        cin >> pesoNovo;
    } while (!this->setPeso(pesoNovo));

        string pesoNovoString = to_string(pesoNovo);
    for (char &c : pesoNovoString) {
        if (c == ',') c = '.';
    }

    string vQuery = "UPDATE ALUNO SET PESO = " + pesoNovoString + " WHERE ID = " + to_string(this->id);

    if(mysql_query(conexao, vQuery.c_str())) {
        system("cls");
        cout << mysql_error(conexao);
        system("pause");
        return false;
    } else {
        system("cls");
        cout << "Dados inseridos com sucesso!" << endl << endl;
        system("pause");
    }

    return true;
}
