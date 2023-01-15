# Labs 4º Edição

Este projeto se trata da resolução do desafio da 4ª edição do Labs da 42 São Paulo que consiste no desenvolvimento de uma aplicação que comprime multiplos textos com o algoritmo de huffman e em seguida descomprime mostrando informações sobre o processo de descompressão

Para mais informações sobre o desafio: _[subject](doc/SUBJECT.md)_

## 🚀 Começando

A aplicação é composta por duas interfaces que se trabalham em conjunto:
* `encoder`: realiza o processo de compressão dos multiplos textos e mostrar as informações do processo de descompressão
* `decoder`: realiza o processo de descompressão

## 📋 Pré-requisitos

Para este projeto é necessario que se tenha o `gcc` ou `clang` instalado em sua máquina para realizar o processo de compilação dos programas e tenha este repositório baixado em sua máquina

### 🔧 Instalação

Compilação:
```bash
make
```
Remover arquivos usados na compilação:
```bash
make clean
```
Remover arquivos usados na compilação e os binários gerados:
```bash
make fclean
```

## 📖 Como usar

### Compressão
Para realizar a compressão:
```bash
./encoder #<flags> <texts>
```

Flags:
* `-f`: para colocar arquivos como texto

### Descompressão

Para realizar a descompressão:
```bash
./decoder #<flags>
```

Flags:
* `-c filename`: para escrever o texto comprimido em um arquivo específico
* `-d filename`: para escrever o texto descomprimido em um arquivo específico

## ✒️ Autor

O projeto foi desenvolvido por Erick Medeiros
* login de cadete: eandre-f
* github: erick-medeiros
