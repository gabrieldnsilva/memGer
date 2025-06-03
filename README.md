<div align="center">

# 🧠 memGer - Memory Manager Simulator

<img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C Language">
<img src="https://img.shields.io/badge/OS-Linux-orange?style=for-the-badge&logo=linux" alt="Linux">
<img src="https://img.shields.io/badge/Topic-Operating%20Systems-green?style=for-the-badge" alt="OS">
<img src="https://img.shields.io/badge/Algorithm-Page%20Replacement-red?style=for-the-badge" alt="Page Replacement">

### 📖 Simulador Interativo de Algoritmos de Substituição de Página

_Um projeto acadêmico para a disciplina de Sistemas Operacionais_

</div>

---

## 🎯 Sobre o Projeto

O **memGer** é um simulador educacional que implementa algoritmos clássicos de substituição de página utilizados em sistemas operacionais para gerenciamento de memória virtual. O projeto foi desenvolvido em **C** com foco na clareza didática e interface interativa.

### 🔥 Algoritmos Implementados

```
┌─────────────────────────────────────────┐
│  🔄 FIFO (First In, First Out)         │
│  📊 LRU (Least Recently Used)          │
└─────────────────────────────────────────┘
```

## ✨ Funcionalidades

-   🎮 **Interface Interativa**: Menu amigável com navegação simples
-   📊 **Visualização em Tempo Real**: Acompanhe cada passo da simulação
-   ⚖️ **Comparação de Algoritmos**: Compare FIFO vs LRU lado a lado
-   🔢 **Entrada Customizável**: Defina suas próprias sequências de referência
-   📈 **Relatórios Detalhados**: Estatísticas completas de page faults
-   ✅ **Validação de Entrada**: Tratamento robusto de dados inválidos

## 🏗️ Arquitetura do Projeto

```
memGer/
├── 📁 src/
│   ├── 📄 main.c           # Função principal e menu
│   ├── 📄 fifo.c           # Implementação do algoritmo FIFO
│   ├── 📄 lru.c            # Implementação do algoritmo LRU
│   ├── 📄 utils.c          # Funções auxiliares e I/O
│   └── 📄 page_replacement.h # Definições e protótipos
├── 📄 Makefile             # Script de compilação
└── 📄 README.md            # Este arquivo
```

## 🚀 Como Usar

### Pré-requisitos

-   GCC Compiler
-   Sistema Linux/Unix
-   Terminal

### Compilação e Execução

```bash
# Clone o repositório (se aplicável)
git clone <repo-url>
cd memGer

# Compile o projeto
make

# Execute o simulador
./bin/memger

# Ou compile manualmente
gcc -o memger src/*.c -I src/
./memger
```

### 📋 Exemplo de Uso

```
╔════════════════════════════════════════════╗
║     SIMULADOR DE SUBSTITUIÇÃO DE PÁGINA   ║
╠════════════════════════════════════════════╣
║ 1. Algoritmo FIFO                         ║
║ 2. Algoritmo LRU                          ║
║ 3. Comparar ambos os algoritmos           ║
║ 4. Sair                                   ║
╚════════════════════════════════════════════╝

Escolha uma opção: 3

Digite o número de referências: 8
Digite as referências: 1 2 3 4 1 2 5 1

Digite o número de frames: 3
```

**Saída do FIFO:**

```
=== Simulação FIFO ===
Passo 1: Página 1 (FAULT) -> Frames: [ 1 | - | - ]
Passo 2: Página 2 (FAULT) -> Frames: [ 1 | 2 | - ]
Passo 3: Página 3 (FAULT) -> Frames: [ 1 | 2 | 3 ]
Passo 4: Página 4 (FAULT) -> Frames: [ 4 | 2 | 3 ]
Passo 5: Página 1 (FAULT) -> Frames: [ 4 | 1 | 3 ]
...
Total de page faults: 6
```

## 🧮 Conceitos Teóricos

### 🔄 FIFO (First In, First Out)

-   **Princípio**: Substitui a página que está há mais tempo na memória
-   **Vantagens**: Simplicidade de implementação
-   **Desvantagens**: Pode sofrer da Anomalia de Belady

### 📊 LRU (Least Recently Used)

-   **Princípio**: Substitui a página menos recentemente usada
-   **Vantagens**: Boa aproximação do algoritmo ótimo
-   **Desvantagens**: Maior complexidade de implementação

## 📊 Estruturas de Dados

```c
typedef struct {
    int page_faults;           // Número total de faltas de página
    int final_pages[MAX_PAGES]; // Estado final da memória
    int num_frames;            // Quantidade de frames utilizados
} SimulationResult;
```

## 🎓 Objetivos Acadêmicos

Este projeto foi desenvolvido para demonstrar:

-   ✅ Compreensão dos algoritmos de substituição de página
-   ✅ Implementação modular em linguagem C
-   ✅ Tratamento de entrada e validação de dados
-   ✅ Visualização clara de algoritmos complexos
-   ✅ Comparação quantitativa de desempenho

## 📈 Casos de Teste Recomendados

### Teste 1: Sequência Clássica

```
Referências: 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
Frames: 3
```

### Teste 2: Anomalia de Belady (FIFO)

```
Referências: 1 2 3 4 1 2 5 1 2 3 4 5
Frames: 3 vs 4
```

### Teste 3: Localidade de Referência

```
Referências: 1 1 1 2 2 2 3 3 3 1 1 1
Frames: 2
```

## 👨‍💻 Autor

**Gabriel Silva**
**Kaique Carvalho**
**Rogério Rodrigues**

## 📝 Licença

Este projeto foi desenvolvido para fins acadêmicos e educacionais.

---

<div align="center">

### 🌟 Se este projeto te ajudou, deixe uma ⭐!

**Feito com ❤️ para a disciplina de Sistemas Operacionais**

</div>
