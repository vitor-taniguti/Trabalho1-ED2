# Nome do executável principal
TARGET = ted

# Compilador
CC = gcc

# Flags
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb \
-Iinclude -I./test/unity \
-DUNITY_INCLUDE_DOUBLE \
-Werror=implicit-function-declaration

# Diretórios
SRC_DIR = ./src
BUILD_DIR = ./build
TEST_DIR = ./test
TEST_BUILD_DIR = ./test/build

# Arquivos fonte do projeto
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Remove main.c da lista de objetos (evita conflito nos testes)
SRCS_NO_MAIN = $(filter-out $(SRC_DIR)/main.c, $(SRCS))

# Objetos
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
OBJS_NO_MAIN = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS_NO_MAIN))

# Testes
TEST_SRCS = $(wildcard $(TEST_DIR)/teste_*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_BUILD_DIR)/%, $(TEST_SRCS))

# =========================
# BUILD PRINCIPAL
# =========================

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@echo "Compilando $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@echo "Linkando $(TARGET)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) -lm

# =========================
# TESTES
# =========================

# Compila cada teste
$(TEST_BUILD_DIR)/teste_%: $(TEST_DIR)/teste_%.c $(OBJS_NO_MAIN)
	@mkdir -p $(TEST_BUILD_DIR)
	@echo "Compilando teste $<"
	$(CC) $(CFLAGS) $< $(OBJS_NO_MAIN) ./test/unity/unity.c -o $@ -lm

# Roda todos os testes
test: $(TEST_BINS)
	@echo "====================="
	@echo "Rodando testes..."
	@echo "====================="
	@for test in $(TEST_BINS); do \
		echo ""; \
		echo ">> $$test"; \
		$$test; \
	done

# =========================
# LIMPEZA
# =========================

clean:
	@echo "Limpando tudo..."
	rm -rf $(BUILD_DIR) $(TEST_BUILD_DIR) $(TARGET)

.PHONY: all test clean