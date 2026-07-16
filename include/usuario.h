#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nome_;
    std::string telefone_;

public:
    Usuario(std::string nome, std::string contato);
    ~Usuario();
    
    std::string get_nome() const;
    std::string get_telefone() const;
    void validar_telefone() const;
};

#endif // USUARIO_H