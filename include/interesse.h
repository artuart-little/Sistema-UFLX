#ifndef INTERESSE_H
#define INTERESSE_H

#include <string>
#include <memory>
#include "Usuario.h"
#include "Anuncio.h"

class Interesse {
private:
    std::shared_ptr<Usuario> interessado_;
    std::weak_ptr<Anuncio> anuncio_alvo_;
    std::string mensagem_;

public:
    Interesse(std::shared_ptr<Usuario> interessado, std::shared_ptr<Anuncio> anuncio_alvo, std::string mensagem);
    ~Interesse();

    std::shared_ptr<Usuario> get_interessado() const;
    std::weak_ptr<Anuncio> get_anuncio_alvo() const;
    std::string get_mensagem() const;
    void processar_interesse() const;
};

#endif // INTERESSE_H