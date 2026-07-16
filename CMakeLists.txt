cmake_minimum_required(VERSION 3.14)
project(SistemaUFLX)

# Configuração do C++ e flags de compilação
set(CMAKE_CXX_STANDARD 17)
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

# ---------------------------------------------------------
# BLOCO CATCH2 (Testes Automatizados)
# ---------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# ---------------------------------------------------------
# COMPILAÇÃO DOS MÓDULOS (O Domínio)
# ---------------------------------------------------------
# Agrupamos todos os ficheiros do domínio numa variável para não repetir
set(DOMAIN_SRCS
    src/Usuario.cpp
    src/Imovel.cpp
    src/Anuncio.cpp
    src/Interesse.cpp
)

# ---------------------------------------------------------
# EXECUTÁVEL PRINCIPAL
# ---------------------------------------------------------
# Compila o sistema juntando o main.cpp com as classes do domínio
add_executable(meu_sistema src/main.cpp ${DOMAIN_SRCS})

# ---------------------------------------------------------
# EXECUTÁVEL DE TESTES
# ---------------------------------------------------------
# Compila os testes juntando o test_tp2.cpp com as classes do domínio (sem o main)
add_executable(testes tests/test_tp2.cpp ${DOMAIN_SRCS})
target_link_libraries(testes PRIVATE Catch2::Catch2WithMain)

# Integração com o CTest
include(CTest)
include(Catch)
catch_discover_tests(testes)