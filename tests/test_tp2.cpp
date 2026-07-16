#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <memory>

// Importação dos cabeçalhos modulares do sistema
#include "Imovel.h"
#include "Inspecionavel.h"

TEST_CASE("Q1: Polimorfismo e Destrutores verificam heranca", "[heranca]") { 
    // A instanciação aloca o objeto na memória
    std::unique_ptr<Imovel> compart = std::make_unique<ImovelCompartilhado>(2, 800.0f, "Castelo", 1.5f);
    REQUIRE(compart != nullptr);
    
    // Ao final deste bloco (fim de escopo), o unique_ptr será destruído automaticamente.
    // Você verá no terminal a cadeia de destrutores sendo chamada na ordem certa
    // (~ImovelCompartilhado seguido de ~Imovel), conforme exigido no roteiro.
}

TEST_CASE("Q2: Polimorfismo calcula corretamente", "[polimorfismo]") { 
    // Criação de um ImovelInteiro apontado pela classe base Imovel
    std::unique_ptr<Imovel> inteiro = std::make_unique<ImovelInteiro>(1, 1500.0f, "Altiplano", 5.0f);
    
    // Verificamos com Approx (ideal para floats) se o cálculo polimórfico 
    // da classe ImovelInteiro retorna a matemática correta (o valor total do aluguel)
    REQUIRE(inteiro->calcular_preco_vaga() == Catch::Approx(1500.0f)); 
}

TEST_CASE("Q3: Verificacao da Interface Pura", "[interface]") { 
    ImovelCompartilhado rep(4, 1200.0f, "Bessa", 8.0f);
    
    // Atribuição polimórfica apenas pela interface
    const Inspecionavel& i = rep;
    
    // Verifica que a passagem e execução do contrato ocorrem perfeitamente sem falhas (exceptions)
    REQUIRE_NOTHROW(i.realizar_inspecao()); 
}