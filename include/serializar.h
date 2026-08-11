#ifndef SERIALIZACAO_H
#define SERIALIZACAO_H

#include <nlohmann/json.hpp>
#include "Imovel.h"
#include <memory>
#include <string>

using json = nlohmann::json;

// (4.A) e (4.B) to_json: Serializacao do dominio com campo "type" para polimorfismo
inline void to_json(json& j, const Imovel& imovel) {
    j = json{
        {"tipo", imovel.get_tipo()}, // OCP puro (elimina necessidade de if/else)
        {"quartos", imovel.get_quartos_disponiveis()},
        {"aluguel", imovel.get_aluguel_mensal()},
        {"bairro", imovel.get_bairro()},
        {"distancia", imovel.get_distancia_ufpb()}
    };
}

// (4.A) from_json: Reconstrucao dinamica do objeto a partir do JSON (Nao-intrusivo)
inline void from_json(const json& j, std::unique_ptr<Imovel>& p) {
    std::string tipo = j.at("tipo").get<std::string>();
    int quartos = j.at("quartos").get<int>();
    float aluguel = j.at("aluguel").get<float>();
    std::string bairro = j.at("bairro").get<std::string>();
    float distancia = j.at("distancia").get<float>();

    if (tipo == "ImovelCompartilhado") {
        p = std::make_unique<ImovelCompartilhado>(quartos, aluguel, bairro, distancia);
    } else if (tipo == "ImovelInteiro") {
        p = std::make_unique<ImovelInteiro>(quartos, aluguel, bairro, distancia);
    } else {
        p = nullptr; 
    }
}

#endif // SERIALIZACAO_H