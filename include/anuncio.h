#ifndef ANUNCIO_H
#define ANUNCIO_H

#include <string>
#include <memory>
#include "Imovel.h"
#include "Usuario.h"

class Anuncio {
private:
    std::string titulo_;
    std::unique_ptr<Imovel> imovel_;
    std::shared_ptr<Usuario> anunciante_;

public:
    Anuncio(std::string titulo, std::unique_ptr<Imovel> imovel_externo, std::shared_ptr<Usuario> anunciante);
    ~Anuncio();
    
    std::string get_titulo() const;
    std::shared_ptr<Usuario> get_anunciante() const;
    void exibir_anuncio() const;
};

#endif // ANUNCIO_H