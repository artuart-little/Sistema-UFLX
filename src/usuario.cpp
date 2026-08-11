#include "Usuario.h"
#include "erros.h"
#include <iostream>

Usuario::Usuario(std::string nome, std::string contato) : nome_(std::move(nome)), telefone_(std::move(contato)) {
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
        // Lança exceção de domínio em caso de erro real
        throw TelefoneInvalido("O formato exige 13 caracteres. Inserido: " + telefone_);
    }
}