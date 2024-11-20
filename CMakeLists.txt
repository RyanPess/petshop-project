# Versão mínima do CMake necessária
cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(petshopProject)

# Especificar a linguagem padrão do projeto
set(CMAKE_C_STANDARD 11)

# Diretórios de cabeçalhos
include_directories(include)

# Adicionar todos os arquivos C automaticamente
file(GLOB_RECURSE SOURCES "src/*.c")

# Configurações do compilador
add_compile_options(-Wall -Wextra -pedantic)

# Criar o executável
add_executable(petshopProject ${SOURCES})

