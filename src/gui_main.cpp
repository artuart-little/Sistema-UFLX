#include <QApplication>
#include "janela.h"
#include "repositorio.h"

int main(int argc, char *argv[]) {
    QApplication aplicacao_qt(argc, argv);

    // (6.B) Inicializamos o dominio (sem interface) primeiro
    RepositorioJson repo_producao;
    AppUFLX motor_uflx(repo_producao); 

    // Instanciamos a GUI passando o motor do sistema
    JanelaPrincipal janela(motor_uflx);
    janela.show();

    return aplicacao_qt.exec();
}