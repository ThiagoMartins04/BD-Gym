#pragma once
#include <string>

using namespace std;

class Pessoa {
private:
    int id;
    string nome;
    string cpf;
    string dataNascimento;
    char sexo;
    string telefone;
    string email;

public:
    Pessoa (int id, string nome, string cpf, string dataNascimento, char sexo, string telefone, string email) {
        this->id = id;
        this->nome = nome;
        this->cpf = cpf;
        this->sexo = sexo;
        this->telefone = telefone;
        this->email = email;
    }
    Pessoa() {}
    int getId();
    string getNome();
    string getCpf();
    char getSexo();
    string getTelefone();
    string getEmail();

    bool setNome(string nome);
    bool setCpf(string cpf);
    bool setSexo(char sexo);
    bool setTelefone(string telefone);
    bool setEmail(string email);
};
