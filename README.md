# Sistema UFLX
Projeto da disciplina Programação Orientada a Objetos que busco criar um sistema de comércio de imóveis voltado aos estudantes da UFPB.

Percebo que a forma de contato que os estudantes de superior têm para procurar/encontrar/oferecer vagas em imóveis (ou imóveis por completo) se limitam somente a grupos de conversa em aplicativos de rede social. Por conta disso, planejo criar esse sistema para melhorar essa situação e ajudar estudantes a encontrar/oferecer imóveis para moradia.

## Descrição do Domínio
O UFLX é um sistema de comércio de imóveis voltado para estudantes universitários. A plataforma permite que proprietários anunciem vagas ou imóveis completos e que estudantes demonstrem interesse nessas ofertas, facilitando o contato direto entre as partes.

## Diagrama UML

```mermaid
classDiagram
    class Inspecionavel {
        <<interface>>
        +realizar_inspecao() void*
    }

    class Imovel {
        <<abstract>>
        #int quartos_disponiveis_
        #float aluguel_mensal_
        #string bairro_
        #float distancia_ufpb_
        +Imovel(int quartos, float aluguel, string bairro, float distancia)
        +virtual ~Imovel()
        +get_quartos_disponiveis() int
        +get_aluguel_mensal() float
        +get_bairro() string
        +get_distancia_ufpb() float
        +calcular_preco_vaga() float*
        +verificar_localizacao() bool
    }

    class ImovelCompartilhado {
        +ImovelCompartilhado(int quartos, float aluguel, string bairro, float distancia)
        +~ImovelCompartilhado()
        +calcular_preco_vaga() float
        +verificar_localizacao() bool
        +realizar_inspecao() void
    }

    class ImovelInteiro {
        +ImovelInteiro(int quartos, float aluguel, string bairro, float distancia)
        +~ImovelInteiro()
        +calcular_preco_vaga() float
        +realizar_inspecao() void
    }

    class Usuario {
        -string nome_
        -string telefone_
        +Usuario(string nome, string contato)
        +~Usuario()
        +get_nome() string
        +get_telefone() string
        +validar_telefone() void
    }

    class Anuncio {
        -string titulo_
        -unique_ptr~Imovel~ imovel_
        -shared_ptr~Usuario~ anunciante_
        +Anuncio(string titulo, int quartos, float aluguel, string bairro, float distancia, shared_ptr~Usuario~ anunciante)
        +~Anuncio()
        +get_titulo() string
        +get_anunciante() shared_ptr~Usuario~
        +exibir_anuncio() void
    }

    class Interesse {
        -shared_ptr~Usuario~ interessado_
        -weak_ptr~Anuncio~ anuncio_alvo_
        -string mensagem_
        +Interesse(shared_ptr~Usuario~ interessado, shared_ptr~Anuncio~ anuncio_alvo, string mensagem)
        +~Interesse()
        +get_interessado() shared_ptr~Usuario~
        +get_anuncio_alvo() weak_ptr~Anuncio~
        +get_mensagem() string
        +processar_interesse() void
    }

    %% Reorganização hierárquica para evitar cruzamento de linhas
    Inspecionavel <|.. ImovelCompartilhado : implementa
    Inspecionavel <|.. ImovelInteiro : implementa
    Imovel <|-- ImovelCompartilhado : herda
    Imovel <|-- ImovelInteiro : herda

    %% Inversão da ordem de declaração para guiar o layout
    Imovel "1" <--* "1" Anuncio : compoe
    Usuario "1" <--o "1" Anuncio : agrega
    Anuncio "1" <--o "1" Interesse : observa
    Usuario "1" <--o "1" Interesse : agrega
```

## Herança Avançada
Foi inserida a interface pura estrita `Inspecionavel`, utilizada para modelar a capacidade de inspecionar a residência. Esta interface foi adicionada às classes derivadas usando o princípio de herança múltipla.

Além disso, a classe derivada `ImovelInteiro` foi assinalada com a palavra-chave `final`. Sendo uma definição arquitetônica de fim de linha, isso garante como regra de design que nenhum desenvolvedor futuro possa especializar esta classe e alterar equivocadamente a sua matemática inteiriça de cálculo de vagas.

#### ---
*Artur Rodrigues Nunes de Almeida - 20250018637 - Aluno de Ciência de Dados e Inteligência Artificial - Centro de Informática (CI) / UFPB*
