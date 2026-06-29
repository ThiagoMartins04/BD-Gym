#pragma once
#include "conexaoBD.h"
#include "pessoa.h"

#include <string>

using namespace std;

class Usuario : public Pessoa {
private:
    int id;
    int id_pessoa;
    string dataCadastro;
    string login;
    string senha;
    char tipo;
public:
    Usuario (int id, int id_pessoa, string dataCadastro, string login, string senha, string nome, string cpf, string dataNascimento, char sexo, string telefone, string email)
    : Pessoa(id_pessoa, nome, cpf, dataNascimento, sexo, telefone, email) {
        this->id = id;
        this->id_pessoa = id_pessoa;
        this->dataCadastro = dataCadastro;
        this->login = login;
        this->senha = senha;
    }
    Usuario() {}
    int getId();
    int getIdPessoa();
    string getDataCadastro();
    string getLogin();
    string getSenha();
    char getTipo();

    bool setId(int id);
    bool setIdPessoa(int idPessoa);
    bool setDataCadastro(string dataCadastro);
    bool setLogin(string login);
    bool setSenha(string senha);
    bool setTipo(MYSQL* conexao);

    bool deleteUsuario (MYSQL* conexao);
};
