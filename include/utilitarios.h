#ifndef UTILITARIOS_H
#define UTILITARIOS_H

// Bibliotecas da STL centralizadas (Questões 1, 2 e 3 - TP3)
#include <vector>
#include <concepts>
#include <utility>
#include <optional>
#include <variant>
#include <ranges>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <future>
#include <mutex>
#include <thread>
#include <memory>

// (1.A) Template de classe genuinamente reutilizável no domínio
template <typename T>
class Catalogo {
private:
    std::vector<T> itens_;
public:
    void adicionar(T item) { itens_.push_back(std::move(item)); }
    const T& get_item(std::size_t i) const { return itens_.at(i); }
    std::size_t tamanho() const { return itens_.size(); }
    const std::vector<T>& get_todos() const { return itens_; }
};

// (    1.B) CRTP: Mixin para contagem estática de instâncias (sem vtable)
template <typename Derivada>
class Contavel {
    static inline int contagem_ = 0;
public:
    Contavel() { ++contagem_; }
    Contavel(const Contavel&) { ++contagem_; }
    ~Contavel() { --contagem_; }
    
    static int get_quantidade_ativa() { return contagem_; }
};

// (1.C) Concept: Restringe tipos exigindo que tenham o método 'calcular_preco_vaga()'
template <typename T>
concept Precificavel = requires(const T& t) {
    { t.calcular_preco_vaga() } -> std::convertible_to<float>;
};

// (1.D) Função usando o concept na assinatura (requires)
template <Precificavel T>
float projetar_aluguel_anual(const T& item) {
    return item.calcular_preco_vaga() * 12.0f;
}

#endif // UTILITARIOS_H