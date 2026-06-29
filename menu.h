#pragma once
#include <cstdlib>
#include <string>

#include "conexaoBD.h"
#include "usuario.h"
#include "aluno.h"


class Menu {
public:
    // Vincula usuário
    Usuario menuRegistro(MYSQL* conexao);
    Usuario menuLogin(MYSQL* conexao);
    Usuario menuCadastro(MYSQL* conexao);

    // Menu para cada tipo de usuário
    void menuAluno(Usuario usuario, MYSQL* conexao);
    void menuProfessor(Usuario usuario);
    void menuPrincipal(Usuario usuario, MYSQL* conexao);

    // Geral
    int selecionarProfessor(MYSQL* conexao);
    bool inserirTreino(MYSQL* conexao, int idProfessor, Usuario usuario);
    void mostrarTreino(MYSQL* conexao, Usuario usuario);
};

