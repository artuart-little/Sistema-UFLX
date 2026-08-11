#include "janela.h"
#include <QString>
#include <string>

JanelaPrincipal::JanelaPrincipal(AppUFLX& core, QWidget* parent)
    : QWidget(parent), app_core_(core) {
    configurar_ui();
}

void JanelaPrincipal::configurar_ui() {
    setWindowTitle("Sistema UFLX - Painel de Controle");
    setMinimumSize(450, 350);

    // Instancia os widgets
    lista_imoveis_ = new QListWidget(this);
    btn_adicionar_ = new QPushButton("Adicionar Imovel Novo (+)", this);
    btn_carregar_ = new QPushButton("Carregar do JSON", this);
    btn_salvar_ = new QPushButton("Salvar no JSON", this);
    btn_limpar_ = new QPushButton("Limpar Tela", this);

    // Layout Vertical
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(lista_imoveis_);
    layout->addWidget(btn_adicionar_);
    layout->addWidget(btn_carregar_);
    layout->addWidget(btn_salvar_);
    layout->addWidget(btn_limpar_);

    // Conecta os cliques 
    connect(btn_adicionar_, &QPushButton::clicked, this, &JanelaPrincipal::ao_clicar_adicionar);
    connect(btn_carregar_, &QPushButton::clicked, this, &JanelaPrincipal::ao_clicar_carregar);
    connect(btn_salvar_, &QPushButton::clicked, this, &JanelaPrincipal::ao_clicar_salvar);
    connect(btn_limpar_, &QPushButton::clicked, this, &JanelaPrincipal::ao_clicar_limpar);
}

void JanelaPrincipal::ao_clicar_adicionar() {
    // Cria um imóvel com nome e preço dinâmicos baseados no tamanho da lista
    int numero = estado_atual_.imoveis.size() + 1;
    std::string bairro = "Bairro Expansao " + std::to_string(numero);
    float preco = 800.0f + (numero * 150.50f);
    
    estado_atual_.version = 1;
    estado_atual_.imoveis.push_back(std::make_unique<ImovelInteiro>(2, preco, bairro, 5.0f));
    
    atualizar_lista(); // Mostra a alteracao na tela
}

void JanelaPrincipal::ao_clicar_carregar() {
    try {
        estado_atual_ = app_core_.executar_carregamento();
        atualizar_lista();
        QMessageBox::information(this, "UFLX", "Dados lidos do arquivo JSON com sucesso!");
    } catch (...) {
        QMessageBox::critical(this, "Erro", "Falha ao carregar os dados.");
    }
}

void JanelaPrincipal::ao_clicar_salvar() {
    try {
        app_core_.executar_salvamento(estado_atual_);
        QMessageBox::information(this, "UFLX", "Estado salvo no arquivo estado_uflx.json!");
    } catch (...) {
        QMessageBox::critical(this, "Erro", "Falha ao salvar os dados.");
    }
}

void JanelaPrincipal::ao_clicar_limpar() {
    lista_imoveis_->clear();
}

void JanelaPrincipal::atualizar_lista() {
    lista_imoveis_->clear();
    for (const auto& imovel : estado_atual_.imoveis) {
        // Formata o dinheiro para 2 casas decimais usando os recursos do QString
        QString texto = QString::fromStdString(imovel->get_tipo() + " | Bairro: " + imovel->get_bairro()) + 
                        " | R$ " + QString::number(imovel->get_aluguel_mensal(), 'f', 2);
        lista_imoveis_->addItem(texto);
    }
}