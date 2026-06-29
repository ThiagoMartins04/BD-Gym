#include "pessoa.h"

int Pessoa::getId() {
    return id;
}

string Pessoa::getNome() {
    return nome;
}

string Pessoa::getCpf() {
    return cpf;
}

char Pessoa::getSexo() {
    return sexo;
}

string Pessoa::getTelefone() {
    return telefone;
}

string Pessoa::getEmail() {
    return email;
}

bool Pessoa::setNome(string nome) {
    if (nome.empty()) return false;
    this->nome = nome;
    return true;
}

bool Pessoa::setCpf(string cpf) {
    if (cpf.empty()) return false;
    this->cpf = cpf;
    return true;
}

bool Pessoa::setSexo(char sexo) {
    if (sexo != 'M' && sexo != 'F') return false;
    this->sexo = sexo;
    return true;
}

bool Pessoa::setTelefone(string telefone) {
    if (telefone.empty()) return false;
    this->telefone = telefone;
    return true;
}

bool Pessoa::setEmail(string email) {
    if (email.empty()) return false;
    this->email = email;
    return true;
}
