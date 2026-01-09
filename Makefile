CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude -O2

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/endereco.cpp \
          $(SRC_DIR)/logradouro.cpp \
          $(SRC_DIR)/palavra.cpp \
          $(SRC_DIR)/consulta.cpp \
          $(SRC_DIR)/utils.cpp

# Arquivos objeto
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/endereco.o \
          $(OBJ_DIR)/logradouro.o \
          $(OBJ_DIR)/palavra.o \
          $(OBJ_DIR)/consulta.o \
          $(OBJ_DIR)/utils.o

# Executável
EXECUTABLE = $(BIN_DIR)/tp3.out

# Alvo padrão
all: $(EXECUTABLE)

# Regra para criar o executável
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Regra para compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
