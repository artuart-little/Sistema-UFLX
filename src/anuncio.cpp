#include "Anuncio.h"
#include <iostream>

Anuncio::Anuncio(std::string titulo, std::unique_ptr<Imovel> imovel_externo, std::shared_ptr<Usuario> anunciante) 
    : titulo_(titulo), imovel_(std::move(imovel_externo)), anunciante_(anunciante) {
    std::cout << "\nAnuncio criado: " << titulo_ << "\n";
}

Anuncio::~Anuncio() {
    std::cout << "~Anuncio destruido: " << titulo_ << "\n";
}

std::string Anuncio::get_titulo() const { return titulo_; }

std::shared_ptr<Usuario> Anuncio::get_anunciante() const { return anunciante_; }

void Anuncio::exibir_anuncio() const {
    std::cout << "\n--- ANUNCIO UFLX ---\n";
    std::cout << "Titulo: " << titulo_ << "\n";
    std::cout << "Anunciante: " << anunciante_->get_nome() << " | Contato: " << anunciante_->get_telefone() << "\n";
    std::cout << "Bairro: " << imovel_->get_bairro() << "\n";
    imovel_->calcular_preco_vaga();
    imovel_->verificar_localizacao();
    std::cout << "--------------------\n";
}