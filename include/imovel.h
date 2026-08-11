#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>
#include "Inspecionavel.h"
#include "utilitarios.h"

// Classe Base Abstrata
class Imovel : public Contavel<Imovel> {
protected:
    int quartos_disponiveis_;
    float aluguel_mensal_;
    std::string bairro_;
    float distancia_ufpb_;

public:
    Imovel(int quartos, float aluguel, std::string bairro, float distancia);
    virtual ~Imovel(); // Destrutor virtual essencial para polimorfismo
    
    int get_quartos_disponiveis() const;
    float get_aluguel_mensal() const;
    std::string get_bairro() const;
    float get_distancia_ufpb() const;
    
    virtual float calcular_preco_vaga() const = 0; // Método virtual puro
    virtual bool verificar_localizacao() const;    // Método virtual não-puro
    virtual std::string get_tipo() const = 0;
};

// Classe Derivada Concreta (Herança Múltipla)
class ImovelCompartilhado : public Imovel, public Inspecionavel {
public:
    ImovelCompartilhado(int quartos, float aluguel, std::string bairro, float distancia);
    ~ImovelCompartilhado() override;

    float calcular_preco_vaga() const override;
    bool verificar_localizacao() const override;
    void realizar_inspecao() const override;
    std::string get_tipo() const override;
};

// Classe Derivada Concreta Final
class ImovelInteiro final : public Imovel, public Inspecionavel { 
public:
    ImovelInteiro(int quartos, float aluguel, std::string bairro, float distancia);
    ~ImovelInteiro() override;
    void realizar_inspecao() const override;
    float calcular_preco_vaga() const override;
    std::string get_tipo() const override;
};

#endif // IMOVEL_H