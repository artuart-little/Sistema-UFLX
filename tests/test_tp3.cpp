#include <catch2/catch_test_macros.hpp>
#include "Usuario.h"
#include "Imovel.h"
#include "Anuncio.h"
#include "utilitarios.h"
#include "erros.h"
#include "repositorio.h"
#include <memory>

// TEST_CASE 1: Validação do Template Genérico e do Concept (Questão 1)
TEST_CASE("Q1: Template Catalogo e Concept") {
    // 1. Instanciando o template com um tipo primitivo para teste puro
    Catalogo<int> cat_inteiros;
    cat_inteiros.adicionar(10);
    cat_inteiros.adicionar(20);
    REQUIRE(cat_inteiros.tamanho() == 2);
    REQUIRE(cat_inteiros.get_item(0) == 10);

    // 2. Testando o Concept (Precificavel)
    ImovelInteiro imovel(1, 1000.0f, "Bessa", 3.0f);
    // A projeção anual deve ser o valor da vaga (1000) * 12 meses
    REQUIRE(projetar_aluguel_anual(imovel) == 12000.0f);
}

// TEST_CASE 2: Validação de Exceções e std::optional (Questão 2)
TEST_CASE("Q2: Tratamento de Erros") {
    // 1. Validando REQUIRE_THROWS_AS pela base da Exceção
    Usuario user_invalido("Teste", "123");
    REQUIRE_THROWS_AS(user_invalido.validar_telefone(), ErroDominio);

    // 2. Validando buscas com optional nos 2 casos
    Catalogo<std::shared_ptr<Anuncio>> cat_anuncios;
    auto imovel = std::make_unique<ImovelInteiro>(1, 1500.0f, "Centro", 4.0f);
    auto dono = std::make_shared<Usuario>("Dono", "83 99999-8888");
    auto anuncio = std::make_shared<Anuncio>("Vaga Teste", std::move(imovel), dono);
    
    cat_anuncios.adicionar(anuncio);

    // Caso 1: Achou
    auto achou = buscar_anuncio_por_titulo(cat_anuncios, "Vaga Teste");
    REQUIRE(achou.has_value() == true);

    // Caso 2: Não achou
    auto nao_achou = buscar_anuncio_por_titulo(cat_anuncios, "Vaga Inexistente");
    REQUIRE(nao_achou.has_value() == false);
}

// TEST_CASE 3 e 4: Validação de Serialização Round-trip e DIP (Questões 4 e DIP)
TEST_CASE("Q4: Serializacao e DIP com Repositorio em Memoria") {
    // Prepara um estado inicial
    EstadoSistema estado_original;
    estado_original.version = 5;
    estado_original.imoveis.push_back(std::make_unique<ImovelInteiro>(2, 2000.0f, "Mangabeira", 7.0f));

    // Usa injeção de dependência com a implementação de MEMÓRIA (não toca o disco)
    RepositorioMemoria repo;
    AppUFLX app(repo);

    // Executa a lógica de alto nível
    app.executar_salvamento(estado_original);
    EstadoSistema estado_carregado = app.executar_carregamento();

    // Comprovações de round-trip (foi salvo e lido de forma idêntica)
    REQUIRE(estado_carregado.version == 5);
    REQUIRE(estado_carregado.imoveis.size() == 1);
    
    // Verifica se o polimorfismo e os dados internos foram preservados via JSON na memória
    REQUIRE(estado_carregado.imoveis[0]->get_bairro() == "Mangabeira");
    REQUIRE(estado_carregado.imoveis[0]->get_aluguel_mensal() == 2000.0f);
    REQUIRE(estado_carregado.imoveis[0]->get_quartos_disponiveis() == 2);
}