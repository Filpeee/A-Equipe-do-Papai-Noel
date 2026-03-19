# Compilador C++
CXX = g++

# --- Flags de compilação exigidas pelo enunciado ---
CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror -O2

# --- Diretórios ---
SRCDIR = src
INCDIR = include
OBJDIR = obj

# --- Flags do pré-processador ---
CPPFLAGS = -I$(INCDIR)

# --- Arquivos fonte e de destino ---
EXECUTABLE = tp3.out
TARGET = $(EXECUTABLE)

SOURCES_BASE = tp3.cpp grafo.cpp solucao.cpp
SOURCES = $(addprefix $(SRCDIR)/, $(SOURCES_BASE))
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES_BASE:.cpp=.o))
HEADERS = $(wildcard $(INCDIR)/*.hpp)

# --- Regras padrão ---
.PHONY: all clean zip run

# Regra principal (gera o executável)
all: $(TARGET)

# Linkagem final
$(TARGET): $(OBJECTS)
	@echo "🔗 Linkando executável final na raiz: $@"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

# Compilação de cada arquivo .cpp em .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJDIR)
	@echo "🧩 Compilando: $< → $@"
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# Limpeza de objetos e binários
clean:
	@echo "🧹 Limpando arquivos compilados..."
	rm -rf $(OBJDIR) $(EXECUTABLE)
	@echo "✔ Limpeza concluída."

# Regra para criar o arquivo .zip para submissão
.PHONY: zip
zip:
	@echo "Criando arquivo de submissão 2024080051_FELIPE_ALMEIDA_PEREIRA.zip..."
	@# Remove o zip antigo, se existir
	@rm -f 2024080051_FELIPE_ALMEIDA_PEREIRA.zip
	@# Cria o zip com os diretórios src/, include/, o Makefile E A DOCUMENTAÇÃO
	@zip -r 2024080051_FELIPE_ALMEIDA_PEREIRA.zip $(SRCDIR) $(INCDIR) Makefile 2024080051_FELIPE_ALMEIDA_PEREIRA.pdf
	@echo "Arquivo 2024080051_FELIPE_ALMEIDA_PEREIRA.zip criado com sucesso (incluindo documentação)."

# Regra utilitária (opcional): executar programa com redirecionamento
run: all
	@echo "🚀 Executando programa..."
	@./$(EXECUTABLE)
