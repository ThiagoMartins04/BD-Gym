#include <iostream>
#include <cstdlib>

// Headers
#include "menu.h"
#include "conexaoBD.h"

using namespace std;

int main()
{
    MYSQL* conexao = obterConexao();
    setlocale(LC_CTYPE, "Portuguese");
    setlocale(LC_NUMERIC, "C");

    Menu menu;
    Usuario usuario = Usuario();

    do {
        usuario = menu.menuRegistro(conexao);
    } while (usuario.getId() == 0);


    menu.menuPrincipal(usuario, conexao);


    return 0;
}
