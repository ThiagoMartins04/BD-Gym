#include "conexaoBD.h"

MYSQL* __stdcall obterConexao()
{
    const char* servidor = "127.0.0.1";
    const char* usuario = "root";
    const char* senha = "";
    const char* nomeBanco = "TrabalhoBD";

    MYSQL* conexao = mysql_init(NULL);

    if (!mysql_real_connect(conexao, servidor, usuario, senha, nomeBanco, 0, NULL, 0))
    {
        cerr << "\n" << mysql_error(conexao) << endl;
        mysql_close(conexao);
        exit(1);
    }
    else
    {
        cout << "\nConexao realizada com sucesso!\n";
        return conexao;
    }
}
