#include "Interesse.h"
#include <iostream>

Interesse::Interesse(std::shared_ptr<Usuario> interessado, std::shared_ptr<Anuncio> anuncio_alvo, std::string mensagem) 
    : interessado_(interessado), anuncio_alvo_(anuncio_alvo), mensagem_(mensagem) {
    std::cout << "Interesse registrado por: " << interessado_->get_nome() << "\n";
}

Interesse::~Interesse() {
    std::cout << "~Interesse destruido.\n";
}

std::shared_ptr<Usuario> Interesse::get_interessado() const { return interessado_; }

std::weak_ptr<Anuncio> Interesse::get_anuncio_alvo() const { return anuncio_alvo_; }

std::string Interesse::get_mensagem() const { return mensagem_; }

void Interesse::processar_interesse() const {
    if (auto anuncio_ref = anuncio_alvo_.lock()) {
        std::cout << "\n ---- NOVO INTERESSE ---- \n";
        std::cout << "Anuncio: " << anuncio_ref->get_titulo() << "\n";
        std::cout << "Interessado: " << interessado_->get_nome() << " (" << interessado_->get_telefone() << ")\n";
        std::cout << "Mensagem: \"" << mensagem_ << "\"\n";
        std::cout << "-------------------------------\n";
    }
}