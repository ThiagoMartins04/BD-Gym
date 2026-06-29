#include "usuario.h"

// GETTERS
int Usuario::getId() {
    return id;
}

int Usuario::getIdPessoa() {
    return id_pessoa;
}

string Usuario::getDataCadastro() {
    return dataCadastro;
}

string Usuario::getLogin() {
    return login;
}

string Usuario::getSenha() {
    return senha;
}

char Usuario::getTipo() {
    return tipo;
}

// SETTERS
bool Usuario::setId(int id) {
    if (id <= 0) return false;
    this->id = id;
    return true;
}

bool Usuario::setIdPessoa(int id_pessoa) {
    if (id_pessoa <= 0) return false;
    this->id_pessoa = id_pessoa;
    return true;
}

bool Usuario::setDataCadastro(string dataCadastro) {
    if (dataCadastro.empty()) return false;
    this->dataCadastro = dataCadastro;
    return true;
}

bool Usuario::setLogin(string login) {
    if (login.empty()) return false;
    this->login = login;
    return true;
}

bool Usuario::setSenha(string senha) {
    if (senha.empty()) return false;
    this->senha = senha;
    return true;
}

bool Usuario::setTipo(MYSQL* conexao) {
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    string vQuery = "SELECT CASE WHEN B.ID IS NOT NULL THEN 'A' ELSE 'P' END TIPO FROM USUARIO A LEFT JOIN ALUNO B ON B.ID = A.ID LEFT JOIN PROFESSOR C ON C.ID = A.ID WHERE A.ID = " + to_string(this->getId());

    if(mysql_query(conexao, vQuery.c_str()))
    {
        mysql_error(conexao);
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        mysql_error(conexao);
    }

    while((row = mysql_fetch_row(resultado)) != NULL) {
        this->tipo = row[0][0];
    }

    mysql_free_result(resultado);
    return true;
}

bool Usuario::deleteUsuario(MYSQL* conexao) {
    char tipoUsuario = this->getTipo();

    if (tipoUsuario == 'A') {

        string query1 = "DELETE FROM ALUNOMENSALIDADE WHERE ID_ALUNO = " + to_string(this->id);
        string query2 = "DELETE A FROM TREINOEXERCICIO A INNER JOIN TREINO B ON B.ID = A.ID_TREINO INNER JOIN ALUNO C ON C.ID = B.ID_ALUNO WHERE C.ID = " + to_string(this->id);
        string query3 = "DELETE FROM TREINO WHERE ID_ALUNO = " + to_string(this->id);
        string query4 = "DELETE FROM ALUNO WHERE ID = " + to_string(this->id);
        string query5 = "DELETE FROM USUARIO WHERE ID = " + to_string(this->id);

        if (mysql_query(conexao, query1.c_str())) {
            cout << mysql_error(conexao);
            system("pause");
            return false;
        }

        if (mysql_query(conexao, query2.c_str())) {
            cout << mysql_error(conexao);
            system("pause");
            return false;
        }

        if (mysql_query(conexao, query3.c_str())) {
            cout << mysql_error(conexao);
            system("pause");
            return false;
        }

        if (mysql_query(conexao, query4.c_str())) {
            cout << mysql_error(conexao);
            system("pause");
            return false;
        }

        if (mysql_query(conexao, query5.c_str())) {
            cout << mysql_error(conexao);
            system("pause");
            return false;
        }

        cout << "Usuário excluído com sucesso!" << endl;
    }
    else {
        cout << "Função não implementada!" << endl;
        return false;
    }

    return true;
}
