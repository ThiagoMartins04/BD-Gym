#pragma once
#include <cstdlib>
#include <string>

#include "conexaoBD.h"
#include "usuario.h"
#include "aluno.h"
#include <regex>


class Menu {
public:
    // Vincula usuário
    Usuario menuRegistro(MYSQL* conexao);
    Usuario menuLogin(MYSQL* conexao);
    void menuCadastro(MYSQL* conexao);

    // Menu para cada tipo de usuário
    void menuAluno(Usuario usuario, MYSQL* conexao);
    void menuProfessor(Usuario usuario);
    void menuPrincipal(Usuario usuario, MYSQL* conexao);

    // Geral
    int selecionarProfessor(MYSQL* conexao);
    bool inserirTreino(MYSQL* conexao, int idProfessor, Usuario usuario, string data);
    void mostrarTreino(MYSQL* conexao, Usuario usuario);
    void mostrarMensalidades(MYSQL* conexao, Usuario usuario);
    bool formatoDataValido(const string& data);
    bool dataValida(const string& data);
    string converterDataParaSQL(const string& data);
    bool verificaSeLoginJaExiste(MYSQL* conexao, string login);
};

