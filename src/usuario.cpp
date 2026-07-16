#include "Usuario.h"
#include <iostream>

Usuario::Usuario(std::string nome, std::string contato) : nome_(nome), telefone_(contato) {
    std::cout << "\nUsuario criado: " << nome_ << "\n";
}

Usuario::~Usuario() {
    std::cout << "~Usuario destruido: " << nome_ << "\n";
}

std::string Usuario::get_nome() const { return nome_; }
std::string Usuario::get_telefone() const { return telefone_; }

void Usuario::validar_telefone() const {
    if (telefone_.length() == 13) {
        std::cout << "Telefone validado com sucesso.\n";
    } else {
        std::cout << "Telefone invalido. Deve ter 13 caracteres (Formato: 83 91234-5678)\n";
    }
}