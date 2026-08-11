cmake_minimum_required(VERSION 3.14)
project(SistemaUFLX)

# Configuração do C++ e flags de compilação
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)

# Warnings e modo debug com sanitizers exigidos no roteiro (em hashtag pois bugam no Windows)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    #add_compile_options(-fsanitize=address,undefined -g)
    #add_link_options(-fsanitize=address,undefined)
    add_compile_options(-g)
endif() 

# Define onde os ficheiros de cabeçalho (.h) estão localizados
include_directories(include)

# BLOCO CATCH2 (Testes Automatizados)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# BLOCO NLOHMANN JSON (Serialização)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG        v3.11.3   
)
FetchContent_MakeAvailable(json)

# COMPILAÇÃO DOS MÓDULOS (O Domínio)
set(DOMAIN_SRCS
    src/Usuario.cpp
    src/Imovel.cpp
    src/Anuncio.cpp
    src/Interesse.cpp
)

# EXECUTÁVEL PRINCIPAL
# Compila o sistema juntando o main.cpp com as classes do domínio
add_executable(meu_sistema src/main.cpp ${DOMAIN_SRCS})
target_link_libraries(meu_sistema PRIVATE nlohmann_json::nlohmann_json)

# EXECUTÁVEL DE TESTES
# Compila os testes juntando o test_tp3.cpp com as classes do domínio (sem o main)
add_executable(testes tests/test_tp3.cpp ${DOMAIN_SRCS})
target_link_libraries(testes PRIVATE Catch2::Catch2WithMain nlohmann_json::nlohmann_json)

# Integração com o CTest
include(CTest)
include(Catch)
catch_discover_tests(testes)

# Interface Gráfica 
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Ativa o meta-object compiler do Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Compila o executável da interface gráfica
add_executable(gui src/gui_main.cpp src/janela.cpp include/janela.h ${DOMAIN_SRCS})

# Linka as dependências (Qt e JSON)
target_link_libraries(gui PRIVATE Qt6::Widgets nlohmann_json::nlohmann_json)