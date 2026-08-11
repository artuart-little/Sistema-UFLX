#ifndef ERROS_H
#define ERROS_H

#include <stdexcept>
#include <string>
#include <optional>
#include <variant>
#include <memory>
#include "Anuncio.h"
#include "utilitarios.h"

// (2.A) Hierarquia de exceções própria
class ErroDominio : public std::runtime_error {
public:
    using std::runtime_error::runtime_error; // Herda construtor
};

class TelefoneInvalido : public ErroDominio {
public:
    explicit TelefoneInvalido(const std::string& msg) 
        : ErroDominio("Telefone invalido: " + msg) {}
};

class ImovelInvalido : public ErroDominio {
public:
    explicit ImovelInvalido(const std::string& msg) 
        : ErroDominio("Imovel invalido: " + msg) {}
};

// (2.B) optional para busca que pode falhar (retorna nullopt se não achar)
inline std::optional<std::shared_ptr<Anuncio>> buscar_anuncio_por_titulo(
    const Catalogo<std::shared_ptr<Anuncio>>& catalogo, 
    const std::string& titulo_alvo) 
{
    for (const auto& anuncio : catalogo.get_todos()) {
        if (anuncio->get_titulo() == titulo_alvo) {
            return anuncio; // achou
        }
    }
    return std::nullopt; // não achou
}

// (2.C) variant: resultado sucesso-com-valor ou erro-com-mensagem
using ResultadoValidacao = std::variant<std::shared_ptr<Anuncio>, std::string>;

inline ResultadoValidacao validar_anuncio_seguro(std::shared_ptr<Anuncio> anuncio) {
    if (!anuncio) {
        return std::string("Erro: O anuncio referenciado esta nulo.");
    }
    if (anuncio->get_titulo().empty()) {
        return std::string("Erro: O anuncio possui titulo vazio.");
    }
    return anuncio; // Sucesso com valor (retorna o objeto)
}

#endif // ERROS_H