#pragma once
#include <string>

#include "usuario.h"

using namespace std;

class Aluno {
private:
    int id;
    double peso;
    double altura;
    int id_plano;

public:
    Aluno(Usuario usuario, MYSQL* conexao) {
        MYSQL_RES *resultado;
        MYSQL_ROW row;

        string vQuery = "SELECT * FROM ALUNO WHERE ID = " + to_string(usuario.getId());

        if(mysql_query(conexao, vQuery.c_str()))
        {
            mysql_error(conexao);
        }

        resultado = mysql_store_result(conexao);

        if (resultado == nullptr) {
            mysql_error(conexao);
        }

        while((row = mysql_fetch_row(resultado)) != NULL) {
            string alturaFormatado = row[2];
            string pesoFormatado = row[1];

            for (char &c : alturaFormatado) {
                if (c == '.') c = ',';
            }
            for (char &c : pesoFormatado) {
                if (c == '.') c = ',';
            }

            this->id = atoi(row[0]);
            this->altura = atof(alturaFormatado.c_str());
            this->peso = atof(pesoFormatado.c_str());
            this->id_plano = atoi(row[3]);
        }

        mysql_free_result(resultado);
    }
    Aluno() {};

    int getId();
    double getPeso();
    double getAltura();
    int getIdPlano();

    bool setId(int id);
    bool setPeso(double peso);
    bool setAltura(double altura);
    bool setIdPlano(int id_plano);

    bool alterarPeso(MYSQL* conexao);
    bool alterarAltura(MYSQL* conexao);
};
