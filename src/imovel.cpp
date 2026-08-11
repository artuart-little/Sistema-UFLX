#include "Imovel.h"
#include "erros.h"
#include <iostream>

Imovel::Imovel(int quartos, float aluguel, std::string bairro, float distancia) 
    : quartos_disponiveis_(quartos), aluguel_mensal_(aluguel), bairro_(bairro), distancia_ufpb_(distancia) {
    std::cout << "Imovel criado.\n";
}

Imovel::~Imovel() { 
    std::cout << "~Imovel (Base) destruido.\n";
}

int Imovel::get_quartos_disponiveis() const { return quartos_disponiveis_; }
float Imovel::get_aluguel_mensal() const { return aluguel_mensal_; }
std::string Imovel::get_bairro() const { return bairro_; }
float Imovel::get_distancia_ufpb() const { return distancia_ufpb_; }

bool Imovel::verificar_localizacao() const {
    if (distancia_ufpb_ <= 2.5f) {
        return true;
    }
    return false;
}

ImovelCompartilhado::ImovelCompartilhado(int quartos, float aluguel, std::string bairro, float distancia)
    : Imovel(quartos, aluguel, bairro, distancia) {
    
    if (quartos <= 0) {
        throw ImovelInvalido("Imovel compartilhado deve ter pelo menos 1 quarto disponivel.");
    }
    
    std::cout << "Imovel Compartilhado instanciado.\n";
}

ImovelCompartilhado::~ImovelCompartilhado() {
    std::cout << "~Imovel Compartilhado (Derivada) destruido.\n";
}

float ImovelCompartilhado::calcular_preco_vaga() const {
    float preco = 0.0f;
    if (quartos_disponiveis_ > 0) {
        preco = aluguel_mensal_ / quartos_disponiveis_;
    }
    return preco;
}

bool ImovelCompartilhado::verificar_localizacao() const {
    return Imovel::verificar_localizacao(); 
}

void ImovelCompartilhado::realizar_inspecao() const {
    std::cout << "Inspecao Efetuada: Areas partilhadas validadas no imovel.\n";
}

ImovelInteiro::ImovelInteiro(int quartos, float aluguel, std::string bairro, float distancia)
    : Imovel(quartos, aluguel, bairro, distancia) {
    std::cout << "Imovel Inteiro instanciado.\n";
}

ImovelInteiro::~ImovelInteiro() {
    std::cout << "~Imovel Inteiro (Derivada final) destruido.\n";
}

void ImovelInteiro::realizar_inspecao() const {
    std::cout << "Inspecao Efetuada: Imovel inteiro validado.\n";
}

float ImovelInteiro::calcular_preco_vaga() const {
    return aluguel_mensal_;
}   

std::string ImovelCompartilhado::get_tipo() const {
    return "ImovelCompartilhado";
}

std::string ImovelInteiro::get_tipo() const {
    return "ImovelInteiro";
}