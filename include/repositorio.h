#ifndef REPOSITORIO_H
#define REPOSITORIO_H

#include <vector>
#include <fstream>
#include "serializar.h"

// Estrutura do Estado completo para salvamento com versão
struct EstadoSistema {
    int version = 1;
    std::vector<std::unique_ptr<Imovel>> imoveis;
};

// (4.C) Abstração - Interface para DIP
class Repositorio {
public:
    virtual void salvar(const EstadoSistema& estado) = 0;
    virtual EstadoSistema carregar() = 0;
    virtual ~Repositorio() = default;
};

// (4.D) Implementação de Produção (JSON no Disco)
class RepositorioJson : public Repositorio {
public:
    void salvar(const EstadoSistema& estado) override {
        json doc;
        doc["version"] = estado.version; // Versionamento
        json array_imoveis = json::array();
        
        for (const auto& imovel : estado.imoveis) {
            json j;
            to_json(j, *imovel);
            array_imoveis.push_back(j);
        }
        doc["imoveis"] = array_imoveis;
        
        std::ofstream out("estado_uflx.json");
        out << doc.dump(4);
    }
    
    EstadoSistema carregar() override {
        EstadoSistema estado;
        std::ifstream in("estado_uflx.json");
        if (!in.is_open()) return estado;
        
        json doc;
        in >> doc;
        estado.version = doc.value("version", 1);
        
        if (doc.contains("imoveis")) {
            for (const auto& j : doc["imoveis"]) {
                std::unique_ptr<Imovel> ptr_imovel;
                j.get_to(ptr_imovel); // O nlohmann detecta e invoca nossa custom from_json!
                if (ptr_imovel) {
                    estado.imoveis.push_back(std::move(ptr_imovel));
                }
            }
        }
        return estado;
    }
};

// (4.D) Implementação de Teste (Memória)
class RepositorioMemoria : public Repositorio {
private:
    EstadoSistema memoria_;
public:
    void salvar(const EstadoSistema& estado) override {
        memoria_.version = estado.version;
        memoria_.imoveis.clear();
        for (const auto& imovel : estado.imoveis) {
            if (auto comp = dynamic_cast<ImovelCompartilhado*>(imovel.get())) {
                memoria_.imoveis.push_back(std::make_unique<ImovelCompartilhado>(*comp));
            } else if (auto inte = dynamic_cast<ImovelInteiro*>(imovel.get())) {
                memoria_.imoveis.push_back(std::make_unique<ImovelInteiro>(*inte));
            }
        }
    }
    EstadoSistema carregar() override {
        EstadoSistema copia;
        copia.version = memoria_.version;
        for (const auto& imovel : memoria_.imoveis) {
            if (auto comp = dynamic_cast<ImovelCompartilhado*>(imovel.get())) {
                copia.imoveis.push_back(std::make_unique<ImovelCompartilhado>(*comp));
            } else if (auto inte = dynamic_cast<ImovelInteiro*>(imovel.get())) {
                copia.imoveis.push_back(std::make_unique<ImovelInteiro>(*inte));
            }
        }
        return copia;
    }
};

// (4.C) Classe de Alto Nível - Depende da Abstração e recebe via injeção
class AppUFLX {
    Repositorio& repo_;
public:
    explicit AppUFLX(Repositorio& r) : repo_{r} {}
    
    void executar_salvamento(const EstadoSistema& estado) {
        repo_.salvar(estado);
    }
    
    EstadoSistema executar_carregamento() {
        return repo_.carregar();
    }
};
#endif // REPOSITORIO_H