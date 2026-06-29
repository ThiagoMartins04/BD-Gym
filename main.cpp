#include <iostream>
#include <cstdlib>

// Headers
#include "menu.h"
#include "conexaoBD.h"

using namespace std;

int main()
{
    MYSQL* conexao = obterConexao();
    setlocale(LC_ALL, "Portuguese");

    Menu menu;
    Usuario usuario;

    usuario = menu.menuRegistro(conexao);

    menu.menuPrincipal(usuario, conexao);


    return 0;
}
