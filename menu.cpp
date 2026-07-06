#include "menu.h"


#include <iostream>

using namespace std;

bool Menu::verificaSeLoginJaExiste(MYSQL* conexao, string login) {
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    string vQuery = "SELECT LOGIN FROM USUARIO WHERE LOGIN = '" + login + "' LIMIT 1";

    if (mysql_query(conexao, vQuery.c_str())) {
        cout << mysql_error(conexao);
        return false;
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        return false;
    }

    row = mysql_fetch_row(resultado);

    bool existe = (row != nullptr);

    mysql_free_result(resultado);

    return existe;
}

bool Menu::formatoDataValido(const string& data) {
    regex padrao(R"(^\d{2}/\d{2}/\d{4}$)");
    return regex_match(data, padrao);
}

bool Menu::dataValida(const string& data) {
    int dia = stoi(data.substr(0, 2));
    int mes = stoi(data.substr(3, 2));
    int ano = stoi(data.substr(6, 4));

    if (mes < 1 || mes > 12) return false;
    if (dia < 1) return false;

    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // ano bissexto
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        diasMes[1] = 29;
    }

    if (dia > diasMes[mes - 1]) return false;

    return true;
}

string Menu::converterDataParaSQL(const string& data) {
    string dia  = data.substr(0, 2);
    string mes  = data.substr(3, 2);
    string ano  = data.substr(6, 4);

    system("cls");
    cout << ano + "-" + mes + "-" + dia;
    system("pause");
    return ano + "-" + mes + "-" + dia;
}

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

bool Menu::inserirTreino(MYSQL* conexao, int idProfessor, Usuario usuario, string data) {
    string query = "INSERT INTO TREINO (id_aluno, id_professor, dataTreino, finalizado) VALUES (" + to_string(usuario.getId()) + ", " + to_string(idProfessor) + ", '" + data + "', false)";

    if (mysql_query(conexao, query.c_str())) {
        cout << mysql_error(conexao);
        system("pause");
        return false;
    }

    system("cls");
    cout << "Agenda inserida com sucesso!" << endl << endl;
    system("pause");

    return true;
}

void Menu::mostrarMensalidades(MYSQL* conexao, Usuario usuario) {
    MYSQL_RES *resultado;
    MYSQL_ROW row;

    string vQuery = "SELECT PARCELA, VALOR, VALORBAIXADO, COMPETENCIA FROM ALUNOMENSALIDADE WHERE ID_ALUNO = " + to_string(usuario.getId()) +
                    " ORDER BY COMPETENCIA DESC";

    if(mysql_query(conexao, vQuery.c_str()))
    {
        mysql_error(conexao);
    }

    resultado = mysql_store_result(conexao);

    if (resultado == nullptr) {
        mysql_error(conexao);
    }

    while((row = mysql_fetch_row(resultado)) != NULL) {
        cout << "Parcela: " << row[0] << "\t | Valor: " << row[1] << "\t | Valor baixado: " << row[2] << "\t | Competência: " << row[3] << endl;
    }

    mysql_free_result(resultado);

    system("pause");
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
        string finalizou;
        if (row[2][0] == '1') {
            finalizou = "Sim";
        } else {
            finalizou = "Não";
        }
        cout << "Professor: " << row[0] << "\t | Data: " << row[1] << "\t | Finalizou: " << finalizou << endl;
    }

    mysql_free_result(resultado);

    system("pause");
}

void Menu::menuCadastro(MYSQL* conexao) {

    string nome, login, senha, cpf, dataNascimento, telefone, email;
    char sexo = 'U';
    double peso, altura;

    system("cls");

    cout << "Bem vindo ao BD Gym! Realize seu cadastro AGORA!\n\n";

    cout << "Nome completo: ";
    getline(cin >> ws, nome);

    cout << "CPF: ";
    getline(cin >> ws, cpf);

    cout << "Data de nascimento (YYYY-MM-DD): ";
    getline(cin >> ws, dataNascimento);

    cout << "Telefone: ";
    getline(cin >> ws, telefone);

    cout << "E-mail: ";
    getline(cin >> ws, email);

    do {
        cout << "Sexo (M/F): ";
        cin >> sexo;
        sexo = toupper(sexo);
    } while (sexo != 'M' && sexo != 'F');

    cout << "Peso (kg): ";
    cin >> peso;

    cout << "Altura (metros): ";
    cin >> altura;

    do {
        cout << "Login (nome.sobrenome): ";
        getline(cin >> ws, login);
    } while (verificaSeLoginJaExiste(conexao, login));

    cout << "Senha: ";
    getline(cin >> ws, senha);

    string queryPessoa =
        "INSERT INTO PESSOA (nome, cpf, dataNascimento, sexo, telefone, email) VALUES ('" +
        nome + "', '" +
        cpf + "', '" +
        dataNascimento + "', '" +
        string(1, sexo) + "', '" +
        telefone + "', '" +
        email + "')";

    if (mysql_query(conexao, queryPessoa.c_str())) {
        cout << mysql_error(conexao);
        system("pause");
        return;
    }

    int idPessoa = mysql_insert_id(conexao);


    string queryUsuario =
        "INSERT INTO USUARIO (id_pessoa, dataCadastro, login, senha) VALUES (" +
        to_string(idPessoa) + ", NOW(), '" + login + "', '" + senha + "')";

    if (mysql_query(conexao, queryUsuario.c_str())) {
        cout << mysql_error(conexao);
        system("pause");
        return;
    }

    int idUsuario = mysql_insert_id(conexao);


    string queryAluno =
        "INSERT INTO ALUNO (id, peso, altura, id_plano) VALUES (" +
        to_string(idUsuario) + ", " +
        to_string(peso) + ", " +
        to_string(altura) + ", 1)";


    if (mysql_query(conexao, queryAluno.c_str())) {
        cout << mysql_error(conexao);
        system("pause");
        return;
    }

    cout << "\nCadastro realizado com sucesso!\n";
    system("pause");

    return;
}

Usuario Menu::menuLogin(MYSQL* conexao) {
    system("cls");

    string login;
    string senha;

    cout << "Bem vindo ao BD Gym!" << endl << endl;

    cout << "Login: ";
    getline(cin >> ws, login);

    cout << "Senha: ";
    getline(cin >> ws, senha);


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

            usuario = Usuario(atoi(row[0]), atoi(row[1]), row[2], row[3], row[4], row[5], row[6], row[7], row[8][0], row[9], row[10]);

            // Vai definir se o tipo de usuário é Aluno/Professor
            usuario.setTipo(conexao);

            mysql_free_result(resultado);

            return usuario;
        }
    }


    system("cls");
    cout << "Nenhum usuário encontrado com essas credenciais." << endl << endl;
    system("pause");



    mysql_free_result(resultado);
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
            Usuario usuario;
            this->menuCadastro(conexao);
            this->menuLogin(conexao);
            return usuario;
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

                string data;
                bool dataValidada = false;

                do {
                    system("cls");
                    cout << "Digite a data (DD/MM/AAAA): ";
                    getline(cin >> ws, data);

                    if (!formatoDataValido(data)) {
                        system("cls");
                        cout << "Formato inválido!" << endl;
                        system("pause");
                    }
                    else if (!dataValida(data)) {
                        system("cls");
                        cout << "Data inválida!" << endl;
                        system("pause");
                    } else {
                        dataValidada = true;
                    }
                } while (dataValidada == false);

                this->inserirTreino(conexao, professorSelecionado, usuario, this->converterDataParaSQL(data));

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
                system("cls");

                cout << "Segue a lista de todas as mensalidades: " << endl << endl;

                this->mostrarMensalidades(conexao, usuario);
                break;
            }
        case 4:
            {
                system("cls");
                int escolha = 0;
                do {
                    cout << "Selecione o que alterar:" << endl << endl;

                    cout << "[1] Altura \t| Atual: " << aluno.getAltura() << endl;
                    cout << "[2] Peso \t| Atual: " << aluno.getPeso() << endl;
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
