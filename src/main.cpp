#include <iostream>

#include "Usuario.h"
#include "Imovel.h"
#include "Anuncio.h"
#include "Interesse.h"
#include "utilitarios.h"
#include "erros.h" 
#include "repositorio.h"

// Funções livres polimórficas
const Imovel* maior_valor(const std::vector<std::unique_ptr<Imovel>>& itens) {
    const Imovel* maior = nullptr;
    float max_preco = -1.0f;
    
    for (const auto& item : itens) {
        float preco = item->calcular_preco_vaga();
        if (preco > max_preco) {
            max_preco = preco;
            maior = item.get();
        }
    }
    return maior;
}

const Imovel* menor_valor(const std::vector<std::unique_ptr<Imovel>>& itens) {
    const Imovel* menor = nullptr;
    float min_preco = 999999.9f; 
    
    for (const auto& item : itens) {
        float preco = item->calcular_preco_vaga();
        if (preco < min_preco) {
            min_preco = preco;
            menor = item.get();
        }
    }
    return menor;
}

// Função livre puramente atralada à interface
void agendar_inspecao(const Inspecionavel& local) {
    std::cout << "--- Agendando Nova Inspecao ---\n";
    local.realizar_inspecao(); 
}

#ifndef RUNNING_TESTS

int main() {
    std::cout << "================\n";
    std::cout << " SISTEMA UFLX \n";
    std::cout << "================\n\n";

    // Parte 1 do Trabalho: Encapsulamento, Composição e Agregação
    std::cout << " --- P1 (Modelagem de Entidades do Domínio) --- \n";

    {   
        auto proprietario = std::make_shared<Usuario>("Artur Almeida", "83 99999-0000");
        auto cliente = std::make_shared<Usuario>("Maria Eloisa", "83 91234-5678");
        
        auto imovel_ptr = std::make_unique<ImovelCompartilhado>(2, 800.0f, "Castelo Branco", 1.5f);
        auto anuncio_vaga = std::make_shared<Anuncio>("Vaga em AP com 2 quartos", std::move(imovel_ptr), proprietario);
        
        anuncio_vaga->exibir_anuncio();
        
        Interesse interesse_maria(cliente, anuncio_vaga, "Tenho interesse na vaga. Posso agendar uma visita?");
        interesse_maria.processar_interesse();
    } 

    // Parte 2 do trabalho: Herança, Polimorfismo e Interfaces
    std::cout << "\n --- P2 (Polimorfismo Dinamico e Vetor Base) --- \n";

    auto locador_lucas = std::make_shared<Usuario>("Lucas", "83 98888-1111");

    // Polimorfismo Dinâmico em vetor de ponteiros base
    std::vector<std::unique_ptr<Imovel>> catalogo;
    catalogo.push_back(std::make_unique<ImovelCompartilhado>(4, 1000.0f, "Bancarios", 2.0f));
    catalogo.push_back(std::make_unique<ImovelInteiro>(1, 2000.0f, "Altiplano", 1.0f));
    catalogo.push_back(std::make_unique<ImovelInteiro>(1, 900.0f, "Valentina", 12.0f));

   // Filtragem polimórfica para descarte de imóveis distantes da UFPB
    for (auto it = catalogo.begin(); it != catalogo.end(); ) {
        if (!(*it)->verificar_localizacao()) {       
            it = catalogo.erase(it); // Gerenciamento limpo com destrutor virtual automático
        } else {
            ++it;
        }
    }

    // Busca do imovel *mais caro* (requisição da Parte 2) e do mais barato usando função livre 
    const Imovel* imovel_caro = maior_valor(catalogo);
    const Imovel* imovel_barato = menor_valor(catalogo);

    std::cout << "\n -> Imovel de Maior Valor: " << imovel_caro->get_bairro() 
              << " | R$ " << imovel_caro->calcular_preco_vaga() << "\n";
    std::cout << "\n -> Imovel de Menor Valor: " << imovel_barato->get_bairro() 
              << " | R$ " << imovel_barato->calcular_preco_vaga() << "\n";

    // Resgate de ponteiros para criação dos anúncios (Unindo Parte 1 com Parte 2 do Trabalho)
    std::unique_ptr<Imovel> ptr_barato;
    std::unique_ptr<Imovel> ptr_caro;
    for (auto& item : catalogo) {
        if (item.get() == imovel_barato) ptr_barato = std::move(item);
        else if (item.get() == imovel_caro) ptr_caro = std::move(item);
    }

    auto anuncio_caro = std::make_shared<Anuncio>("Apartamento de Luxo", std::move(ptr_caro), locador_lucas);
    auto anuncio_barato = std::make_shared<Anuncio>("Republica perto da UFPB", std::move(ptr_barato), locador_lucas);

    anuncio_caro->exibir_anuncio();
    anuncio_barato->exibir_anuncio();

    if (auto* interface_inspecao = dynamic_cast<Inspecionavel*>(ptr_barato.get())) {
        agendar_inspecao(*interface_inspecao); 
    }
        
    auto estudante = std::make_shared<Usuario>("Carlos", "83 93333-4444");
    Interesse interesse_carlos(estudante, anuncio_barato, "Me interessei pelo valor. Como reservo?");
    interesse_carlos.processar_interesse();

    // Parte 3 do Trabalho: Programação Genérica, Erros, STL e Concorrência 
    std::cout << "\n--- P3: Questao 1  (Programacao Generica, CRTP e Ranges) ---\n";
    
    Catalogo<std::shared_ptr<Usuario>> catalogo_usuarios;
    catalogo_usuarios.adicionar(estudante);
    catalogo_usuarios.adicionar(locador_lucas);
    
    Catalogo<std::shared_ptr<Anuncio>> catalogo_anuncios;
    catalogo_anuncios.adicionar(anuncio_barato);
    catalogo_anuncios.adicionar(anuncio_caro);
    
    std::cout << "-> Usuarios cadastrados (Template): " << catalogo_usuarios.tamanho() << "\n";
    std::cout << "-> Anuncios ativos (Template): " << catalogo_anuncios.tamanho() << "\n";
    std::cout << "-> Imoveis ativos (CRTP): " << Imovel::get_quantidade_ativa() << "\n";
    std::cout << "-> Projecao anual do imovel mais caro (Concept): R$ " 
              << projetar_aluguel_anual(*imovel_caro) << "\n\n";

    // Simulando a entrada de novos imoveis no sistema para avaliacao de dados
    catalogo.push_back(std::make_unique<ImovelCompartilhado>(3, 600.0f, "Castelo Branco", 1.2f)); // R$ 200/vaga
    catalogo.push_back(std::make_unique<ImovelInteiro>(2, 1500.0f, "Tambau", 7.0f));              // R$ 1500/vaga
    catalogo.push_back(std::make_unique<ImovelInteiro>(1, 900.0f, "Bancarios", 2.5f));            // R$ 900/vaga
    catalogo.push_back(std::make_unique<ImovelCompartilhado>(4, 1600.0f, "Mangabeira", 4.0f));    // R$ 400/vaga
    catalogo.push_back(std::make_unique<ImovelInteiro>(3, 3000.0f, "Cabo Branco", 8.5f));         // R$ 3000/vaga

    namespace rv = std::ranges::views;
    auto nomes_bairros_acessiveis = catalogo 
        | rv::filter([](const std::unique_ptr<Imovel>& i){ 
            return i != nullptr && i->calcular_preco_vaga() <= 1000.0f; 
        })
        | rv::transform([](const std::unique_ptr<Imovel>& i){ 
            return i->get_bairro(); 
        });

    if (std::ranges::empty(nomes_bairros_acessiveis)) {
        std::cout << "\n -> Nenhum bairro com imoveis acessiveis (ate R$1000,00).\n";
    } else {
        std::cout << "\n -> Bairros com imoveis acessiveis (ate R$1000,00):\n";
        for (const auto& bairro : nomes_bairros_acessiveis) {
            std::cout << "- " << bairro << "\n";
        }
    }

    std::cout << "\n--- P3: Questao 2 (Tratamento de Erros) ---\n";

    std::cout << "1. Teste de Excecao na Validacao:\n";
    try {
        Usuario usuario_invalido("Teste", "123");
        usuario_invalido.validar_telefone();
    } catch (const ErroDominio& e) {
        std::cout << "\n -> Excecao capturada pela base: " << e.what() << "\n";
    }

    auto busca_sucesso = buscar_anuncio_por_titulo(catalogo_anuncios, "Apartamento de Luxo");
    auto busca_falha = buscar_anuncio_por_titulo(catalogo_anuncios, "Inexistente");
    std::cout << "-> Busca por 'Apartamento de Luxo' (std::optional): " 
              << (busca_sucesso.has_value() ? "Encontrado" : "Nao encontrado") << "\n";
    std::cout << "-> Busca por 'Inexistente' (std::optional): " 
              << (busca_falha.has_value() ? "Encontrado" : "Nao encontrado (std::nullopt)") << "\n";

    // Tratamento de variant com std::visit (Sucesso com valor OU erro com string)
    ResultadoValidacao resultado_ok = validar_anuncio_seguro(anuncio_caro);
    std::shared_ptr<Anuncio> anuncio_nulo = nullptr;
    ResultadoValidacao resultado_falha = validar_anuncio_seguro(anuncio_nulo);

    auto processar_variant = [](const ResultadoValidacao& res) {
        std::visit([](const auto& valor) {
            using Tipo = std::decay_t<decltype(valor)>;
            if constexpr (std::is_same_v<Tipo, std::shared_ptr<Anuncio>>) {
                std::cout << "-> [Variant Sucesso]: Anuncio Validado - " << valor->get_titulo() << "\n";
            } else if constexpr (std::is_same_v<Tipo, std::string>) {
                std::cout << "-> [Variant Falha]: " << valor << "\n";
            }
        }, res);
    };
    
    processar_variant(resultado_ok);
    processar_variant(resultado_falha);

    std::cout << "\n--- P3: Questao 3 (STL e Processamento Concorrente) ---\n";

    std::map<std::string, std::shared_ptr<Usuario>> agenda_usuarios;
    agenda_usuarios[estudante->get_telefone()] = estudante;
    agenda_usuarios[locador_lucas->get_telefone()] = locador_lucas;

    std::unordered_set<std::string> bairros_unicos;
    for (const auto& item : catalogo) {
        if (item) {
            bairros_unicos.insert(item->get_bairro());
        }
    }

    std::cout << "Contatos na agenda (std::map): " << agenda_usuarios.size() << "\n";
    std::cout << "Bairros unicos com imoveis (std::unordered_set): " << bairros_unicos.size() << "\n";

    std::vector<Imovel*> imoveis_ordenados;
    for (const auto& ptr : catalogo) {
        if (ptr) {imoveis_ordenados.push_back(ptr.get());}
    }

    // Algoritmo 1: sort (ordenar imoveis do mais barato para o mais caro)
    std::sort(imoveis_ordenados.begin(), imoveis_ordenados.end(), 
        [](Imovel* a, Imovel* b) { return a->calcular_preco_vaga() < b->calcular_preco_vaga(); });

    // Algoritmo 2: count_if capturando variável local
    float limite_orcamento = 950.0f;
    int imoveis_acessiveis = std::count_if(imoveis_ordenados.begin(), imoveis_ordenados.end(),
        [limite_orcamento](Imovel* imovel) { return imovel->calcular_preco_vaga() <= limite_orcamento; });

    // Algoritmo 3: accumulate para somar valores e encontrar a média de precos
    float soma_total = std::accumulate(imoveis_ordenados.begin(), imoveis_ordenados.end(), 0.0f,
        [](float acumulado, Imovel* imovel) { return acumulado + imovel->calcular_preco_vaga(); });

    std::cout << "Imoveis com valor limite de R$" << limite_orcamento << ": " << imoveis_acessiveis << "\n";
    
    if (!imoveis_ordenados.empty()) {
        std::cout << "-> Media de precos da plataforma: R$" << (soma_total / imoveis_ordenados.size()) << "\n";
    } else {
        std::cout << "-> Media de precos da plataforma: R$ 0.00 (Catálogo Vazio)\n";
    }
    
    std::mutex mtx_seguranca;
    int inspecoes_aprovadas = 0;
    std::vector<std::future<bool>> processamentos_futuros;
    
    for (const auto& imovel : imoveis_ordenados) {
        processamentos_futuros.push_back(
            std::async(std::launch::async, [imovel]() {
                return imovel->verificar_localizacao();
            })
        );
    }

    for (auto& futuro : processamentos_futuros) {
        if (futuro.get()) { 
            std::lock_guard<std::mutex> lock(mtx_seguranca); 
            inspecoes_aprovadas++;
        }
    }
    
    std::cout << "Total de imoveis aprovados concorrentemente (Threads + Mutex): " << inspecoes_aprovadas << "\n";    

    std::cout << "\n --- P3: Questao 4 (Persistencia de Dados e SOLID (DIP) ) ---\n";
    EstadoSistema estado_producao;
    estado_producao.version = 1;
    estado_producao.imoveis.push_back(std::make_unique<ImovelInteiro>(2, 1200.0f, "Bessa", 3.0f));

    RepositorioJson repo_json;
    AppUFLX app(repo_json);
    app.executar_salvamento(estado_producao);
    std::cout << "-> Estado salvo no arquivo 'estado_uflx.json' via DIP.\n";    

    std::cout << "\n--- Programa Finalizado ---\n";
    
    return 0;

}

#endif