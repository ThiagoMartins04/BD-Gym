#include "menu.h"


#include <iostream>

using namespace std;

int Menu::selecionarProfessor (MYSQL* conexao) {
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    char* vQuery = "SELECT A.ID, C.NOME, B.NOME ESPECIALIDADE, A.TURNO FROM PROFESSOR A INNER JOIN ESPECIALIDADE B ON B.ID = A.ID_ESPECIALIDADE INNER JOIN PESSOA C ON C.ID = A.ID";

    if(mysql_query(conexao, vQuery))
    {
        mysql_error(conexao);
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        mysql_error(conexao);
    }

    Usuario usuario;
    while((row = mysql_fetch_row(resultado)) != NULL) {
        cout << "ID: " << row[0] << " | Nome: " << row[1] << " | Especialidade: " << row[2] << " | Turno: " << row[3] << endl;
    }

    mysql_free_result(resultado);

    cout << endl;
    cout << "ID do Professor: ";
    int professorSelecionado = 0;
    cin >> professorSelecionado;
    return professorSelecionado;
}

bool Menu::inserirTreino(MYSQL* conexao, int idProfessor, Usuario usuario) {
    string query = "INSERT INTO TREINO (id_aluno, id_professor, dataTreino, finalizado) VALUES (" + to_string(usuario.getId()) + ", " + to_string(idProfessor) + ", now(), false)";

    if (mysql_query(conexao, query.c_str())) {
        cout << mysql_error(conexao);
        system("pause");
        return false;
    }

    system("cls");
    cout << "Agenda inserida com sucesso!" << endl;
    system("pause");

    return true;
}

void Menu::mostrarTreino(MYSQL* conexao, Usuario usuario) {
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    string vQuery = "SELECT C.NOME PROFESSOR, A.DATATREINO, A.FINALIZADO FROM TREINO A INNER JOIN PROFESSOR B ON B.ID = A.ID_PROFESSOR INNER JOIN PESSOA C ON C.ID = B.ID WHERE A.ID_ALUNO = " + to_string(usuario.getId());

    if(mysql_query(conexao, vQuery.c_str()))
    {
        mysql_error(conexao);
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        mysql_error(conexao);
    }

    while((row = mysql_fetch_row(resultado)) != NULL) {
        cout << "Professor: " << row[0] << " | Data: " << row[1] << " | Finalizou: " << row[2] << endl;
    }

    mysql_free_result(resultado);

    system("pause");
}

Usuario Menu::menuCadastro(MYSQL* conexao) {
    Usuario usuario;
    return usuario;
}

Usuario Menu::menuLogin(MYSQL* conexao) {
    system("cls");

    string login;
    string senha;

    cout << "Login: ";
    cin >> login;

    cout << endl;

    cout << "Senha: ";
    cin >> senha;


    MYSQL_RES *resultado;
    MYSQL_ROW row;

    char* vQuery = "SELECT A.ID, B.ID, A.DATACADASTRO, A.LOGIN, A.SENHA, B.NOME, B.CPF, B.DATANASCIMENTO, B.SEXO, B.TELEFONE, B.EMAIL FROM USUARIO A INNER JOIN PESSOA B ON A.ID_PESSOA = B.ID";

    if(mysql_query(conexao, vQuery))
    {
        mysql_error(conexao);
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        mysql_error(conexao);
    }

    Usuario usuario;
    while((row = mysql_fetch_row(resultado)) != NULL) {
        if(login == row[3] && senha == row[4]) {
            system("cls");

            usuario.setId(atoi(row[0]));
            usuario.setIdPessoa(atoi(row[1]));
            usuario.setDataCadastro(row[2]);
            usuario.setLogin(row[3]);
            usuario.setSenha(row[4]);
            usuario.setNome(row[5]);
            usuario.setCpf(row[6]);
            usuario.setDataCadastro(row[7]);
            usuario.setSexo(row[8][0]);
            usuario.setTelefone(row[9]);
            usuario.setEmail(row[10]);
            usuario.setTipo(conexao);

            mysql_free_result(resultado);

            return usuario;
        }
    }

    mysql_free_result(resultado);

    system("cls");
    cout << "Nenhum usuário encontrado.";
    return usuario;
}

Usuario Menu::menuRegistro(MYSQL* conexao) {
    int escolhaUsuario = 0;
    do
    {
        system("cls");
        cout << "Bem vindo ao BD Gym!" << endl << endl;

        cout << "[1] Logar" << endl;
        cout << "[2] Cadastrar" << endl;
        cout << "[3] Sair" << endl << endl;

        if (escolhaUsuario != 0) { cout << "Escolha um valor válido!" << endl;}
        cin >> escolhaUsuario;
    } while (escolhaUsuario < 1 || escolhaUsuario > 3);

    switch(escolhaUsuario) {
    case 1:
        {
            Usuario usuario;
            usuario = this->menuLogin(conexao);
            return usuario;
        }
    case 2:
        {

        }
    case 3:
        {
            exit(0);
        }
    }
}

void Menu::menuAluno(Usuario usuario, MYSQL* conexao) {
    Aluno aluno(usuario, conexao);
    do {
        system("cls");
        cout << "Aluno(a) " << usuario.getNome() << endl << endl;

        cout << "[1] Agendar aula" << endl;
        cout << "[2] Verificar treinos" << endl;
        cout << "[3] Verificar mensalidades" << endl;
        cout << "[4] Alterar dados" << endl;
        cout << "[5] Excluir conta" << endl;
        cout << "[6] Sair" << endl << endl;

        cout << "Escolha: ";

        int escolha = 0;

        cin >> escolha;

        switch(escolha) {
        case 1:
            {
                system("cls");

                cout << "Agende sua aula! Veja os professores disponíveis:" << endl << endl;

                int professorSelecionado = this->selecionarProfessor(conexao);

                this->inserirTreino(conexao, professorSelecionado, usuario);

                break;
            }
        case 2:
            {
                system("cls");

                cout << "Segue a lista de treinos: " << endl << endl;

                this->mostrarTreino(conexao, usuario);
                break;
            }
        case 3:
            {
                break;
            }
        case 4:
            {
                system("cls");
                int escolha = 0;
                do {
                    cout << "Selecione o que alterar:" << endl << endl;

                    cout << "[1] Altura | Atual: " << aluno.getAltura() << endl;
                    cout << "[2] Peso | Atual: " << aluno.getPeso() << endl;
                    cout << "[3] Sair" << endl << endl;

                    cout << "Escolha: ";

                    cin >> escolha;

                } while (escolha < 1 || escolha > 3);

                if (escolha == 1) aluno.alterarAltura(conexao);
                if (escolha == 2) aluno.alterarPeso(conexao);
                break;
            }
        case 5:
        {
            system("cls");
            int escolha;
            do {
                cout << "Certeza que deseja efetuar a exclusão da conta? " << endl << endl;

                cout << "[1] Sim" << endl;
                cout << "[2] Não" << endl << endl;

                cin >> escolha;

            } while (escolha > 2 || escolha < 1);

            if (escolha == 1) {
                if(usuario.deleteUsuario(conexao)) {
                    exit(0);
                }
            }

            break;
        }
        case 6:
            {
                system("cls");
                exit(0);
                break;
            }
        }
    } while (true);

};

void Menu::menuProfessor(Usuario usuario) {
    system("cls");
    cout << "Professor(a) " << usuario.getNome() << endl << endl;



};

void Menu::menuPrincipal(Usuario usuario, MYSQL* conexao) {
    system("cls");

    cout << "Bem vindo, " << usuario.getNome() << "!" << endl;

    system("pause");

    char tipoUsuario = usuario.getTipo();

    if (tipoUsuario == 'A') {
        this->menuAluno(usuario, conexao);
    } else {
        this->menuProfessor(usuario);
    }
};
