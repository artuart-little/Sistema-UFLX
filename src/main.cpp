#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "Usuario.h"
#include "Imovel.h"
#include "Anuncio.h"
#include "Interesse.h"

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

    // Parte 1 do trabalho
    std::cout << " --- P1 (Classes e Objetos) --- \n";

    {   
        auto proprietario = std::make_shared<Usuario>("Artur Almeida", "83 99999-0000");
        
        auto cliente = std::make_shared<Usuario>("Maria Eloisa", "83 91234-5678");
        
        auto imovel_ptr = std::make_unique<ImovelCompartilhado>(2, 800.0f, "Castelo Branco", 1.5f);
        
        auto anuncio_vaga = std::make_shared<Anuncio>("Vaga em AP com 2 quartos", std::move(imovel_ptr), proprietario);
        anuncio_vaga->exibir_anuncio();
        
        Interesse interesse_maria(cliente, anuncio_vaga, "Tenho interesse na vaga. Posso agendar uma visita?");
        interesse_maria.processar_interesse();
    } 

    // Parte 2 do trabalho 
    std::cout << "\n --- P2 (Polimorfismo e Heranca) --- \n";

    auto locador_lucas = std::make_shared<Usuario>("Lucas", "83 98888-1111");

    // Polimorfismo Dinâmico em vetor de ponteiros base
    std::vector<std::unique_ptr<Imovel>> catalogo;
    catalogo.push_back(std::make_unique<ImovelCompartilhado>(4, 1000.0f, "Bancarios", 2.0f));
    catalogo.push_back(std::make_unique<ImovelInteiro>(1, 2000.0f, "Altiplano", 1.0f));
    catalogo.push_back(std::make_unique<ImovelInteiro>(1, 900.0f, "Valentina", 12.0f));

   // Filtragem de imóveis distantes da UFPB
    for (auto it = catalogo.begin(); it != catalogo.end(); ) {
        // Se a verificação retornar falso, o imóvel é descartado
        if (!(*it)->verificar_localizacao()) {       
            Imovel* imovel_distante = it->release(); // Tira a posse do smart pointer
            delete imovel_distante;                  // Desencadeia o destrutor virtual
            it = catalogo.erase(it);                 // Remove o espaço vazio do vetor
        } else {
            ++it;
        }
    }

    // Busca do imovel *mais caro* (requisição da Parte 2) e do mais barato usando função livre 
    const Imovel* imovel_caro = maior_valor(catalogo);
    std::cout << "\nImovel mais caro encontrado no bairro: " << imovel_caro->get_bairro() << "\n";
    std::cout << "Valor de R$" << imovel_caro->calcular_preco_vaga() << "\n";
    
    const Imovel* imovel_barato = menor_valor(catalogo);
    std::cout << "O imovel de menor valor esta no bairro " << imovel_barato->get_bairro() << "!\n";
    std::cout << "Valor de R$ " << imovel_barato->calcular_preco_vaga() << "\n";

    // Unindo Parte 2 com Parte 1
    std::cout << "\n--- P1 e P2 --- \n";

    std::unique_ptr<Imovel> ptr_barato;
    std::unique_ptr<Imovel> ptr_caro;

    // Varre o catálogo para resgatar os smart pointers correspondentes aos endereços
    for (auto& item : catalogo) {
        if (item.get() == imovel_barato) {
            ptr_barato = std::move(item);
        } else if (item.get() == imovel_caro) {
            ptr_caro = std::move(item);
        }
    }

    auto anuncio_caro = std::make_shared<Anuncio>("Apartamento de Luxo", std::move(ptr_caro), locador_lucas);
    anuncio_caro->exibir_anuncio();

    auto anuncio_barato = std::make_shared<Anuncio>("Republica perto da UFPB", std::move(ptr_barato), locador_lucas);
    anuncio_barato->exibir_anuncio();

    // Função livre atrelada puramente à Interface
    if (auto* interface_inspecao = dynamic_cast<Inspecionavel*>(ptr_barato.get())) {
        agendar_inspecao(*interface_inspecao); 
    }
        
    auto estudante = std::make_shared<Usuario>("Carlos", "83 93333-4444");
    Interesse interesse_carlos(estudante, anuncio_barato, "Me interessei pelo valor. Como reservo?");
    interesse_carlos.processar_interesse();


    std::cout << "\n--- Programa Finalizado ---\n";
    return 0;

}

#endif
