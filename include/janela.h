#ifndef JANELA_H
#define JANELA_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include "repositorio.h"

class JanelaPrincipal : public QWidget {
    Q_OBJECT 

private:
    AppUFLX& app_core_; 
    EstadoSistema estado_atual_;

    // Elementos Visuais
    QListWidget* lista_imoveis_;
    QPushButton* btn_adicionar_; // Novo botão
    QPushButton* btn_carregar_;
    QPushButton* btn_salvar_;
    QPushButton* btn_limpar_;

    void configurar_ui();
    void atualizar_lista();

private slots: 
    void ao_clicar_adicionar(); // Nova função de clique
    void ao_clicar_carregar();
    void ao_clicar_salvar();
    void ao_clicar_limpar();

public:
    explicit JanelaPrincipal(AppUFLX& core, QWidget* parent = nullptr);
};

#endif // JANELA_H