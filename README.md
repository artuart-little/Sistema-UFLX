# Sistema UFLX
Projeto da disciplina Programação Orientada a Objetos que busco criar um sistema de comércio de imóveis voltado aos estudantes da UFPB.

Percebo que a forma de contato que os estudantes de superior têm para procurar/encontrar/oferecer vagas em imóveis (ou imóveis por completo) se limitam somente a grupos de conversa em aplicativos de rede social. Por conta disso, planejo criar esse sistema para melhorar essa situação e ajudar estudantes a encontrar/oferecer imóveis para moradia.

## Descrição do Domínio
O UFLX é um sistema de comércio de imóveis voltado para estudantes universitários. A plataforma permite que proprietários anunciem vagas ou imóveis completos e que estudantes demonstrem interesse nessas ofertas, facilitando o contato direto entre as partes.

## Diagrama UML

```mermaid
classDiagram
    
    class Usuario {
        -string nome_
        -string telefone_
        +Usuario(string nome, string contato)
        +~Usuario()
        +get_nome() string
        +get_telefone() string
        +validar_telefone() void
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

    class Inspecionavel {
        <<interface>>
        +realizar_inspecao() void*
    }

    Imovel <|-- ImovelCompartilhado : herda
    Imovel <|-- ImovelInteiro : herda
    Inspecionavel <|.. ImovelCompartilhado : implementa
    Inspecionavel <|.. ImovelInteiro : implementa

    Anuncio "1" *-- "1" Imovel : compoe
    Anuncio "1" o-- "1" Usuario : agrega
    Interesse "1" o-- "1" Usuario : agrega
    Interesse "1" o-- "1" Anuncio : observa (agrega)
```

#### ---
*Artur Rodrigues Nunes de Almeida - 20250018637 - Aluno de Ciência de Dados e Inteligência Artificial - Centro de Informática (CI) / UFPB*
