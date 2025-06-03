# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Diretórios
SRCDIR = src
BUILDDIR = build
OBJDIR = $(BUILDDIR)/obj
BINDIR = $(BUILDDIR)/bin

# Nome do executável
TARGET = memGer
TARGET_PATH = $(BINDIR)/$(TARGET)

# Arquivos fonte e objetos
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Diretório de include
INCLUDES = -I$(SRCDIR)

# Regra padrão
all: directories $(TARGET_PATH)

# Criar diretórios necessários
directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

# Compilar o executável
$(TARGET_PATH): $(OBJECTS)
	@echo "🔗 Linkando $(TARGET)..."
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "✅ Build concluído: $(TARGET_PATH)"

# Compilar arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "🔨 Compilando $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Dependências específicas
$(OBJDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/page_replacement.h
$(OBJDIR)/fifo.o: $(SRCDIR)/fifo.c $(SRCDIR)/page_replacement.h
$(OBJDIR)/lru.o: $(SRCDIR)/lru.c $(SRCDIR)/page_replacement.h
$(OBJDIR)/utils.o: $(SRCDIR)/utils.c $(SRCDIR)/page_replacement.h

# Executar o programa
run: $(TARGET_PATH)
	@echo "🚀 Executando $(TARGET)..."
	@cd $(BINDIR) && ./$(TARGET)

# Depuração com GDB
debug: $(TARGET_PATH)
	@echo "🐛 Iniciando depuração..."
	@cd $(BINDIR) && gdb ./$(TARGET)

# Verificar vazamentos de memória com Valgrind
valgrind: $(TARGET_PATH)
	@echo "🔍 Verificando vazamentos de memória..."
	@cd $(BINDIR) && valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Instalar (copiar para /usr/local/bin)
install: $(TARGET_PATH)
	@echo "📦 Instalando $(TARGET)..."
	sudo cp $(TARGET_PATH) /usr/local/bin/
	@echo "✅ $(TARGET) instalado em /usr/local/bin/"

# Desinstalar
uninstall:
	@echo "🗑️  Removendo $(TARGET)..."
	sudo rm -f /usr/local/bin/$(TARGET)
	@echo "✅ $(TARGET) removido"

# Limpeza
clean:
	@echo "🧹 Limpando arquivos de build..."
	rm -rf $(BUILDDIR)
	@echo "✅ Limpeza concluída"

# Limpeza completa (incluindo cache do git)
distclean: clean
	@echo "🧹 Limpeza completa..."
	rm -rf .git/objects/*

# Mostrar informações do projeto
info:
	@echo "📊 Informações do Projeto memGer"
	@echo "================================="
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Diretório fonte: $(SRCDIR)"
	@echo "Diretório build: $(BUILDDIR)"
	@echo "Executável: $(TARGET_PATH)"
	@echo "Arquivos fonte:"
	@for src in $(SOURCES); do echo "  - $$src"; done

# Mostrar ajuda
help:
	@echo "🆘 Comandos disponíveis:"
	@echo "========================"
	@echo "make         - Compilar o projeto"
	@echo "make run     - Compilar e executar"
	@echo "make debug   - Compilar e executar com GDB"
	@echo "make valgrind- Verificar vazamentos com Valgrind"
	@echo "make clean   - Limpar arquivos de build"
	@echo "make install - Instalar no sistema"
	@echo "make info    - Mostrar informações do projeto"
	@echo "make help    - Mostrar esta ajuda"

.PHONY: all directories run debug valgrind install uninstall clean distclean info help
