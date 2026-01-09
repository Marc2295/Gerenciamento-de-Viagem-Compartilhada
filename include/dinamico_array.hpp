#ifndef DINAMICOARRAY_H
#define DINAMICOARRAY_H

/**
 * TAD DinamicoArray
 * 
 * Implementação manual de um array dinâmico
 * Funcionalidades: inserir, acessar por índice, redimensionar automaticamente
 */
template<typename T>
class DinamicoArray {
private:
    T* dados;
    int tamanho;
    int capacidade;

    /**
     * Redimensiona o array quando necessário
     */
    void redimensionar() {
        if (tamanho >= capacidade) {
            int novaCapacidade = (capacidade == 0) ? 10 : capacidade * 2;
            T* novosDados = new T[novaCapacidade];
            
            for (int i = 0; i < tamanho; i++) {
                novosDados[i] = dados[i];
            }
            
            delete[] dados;
            dados = novosDados;
            capacidade = novaCapacidade;
        }
    }

public:
    /**
     * Construtor
     */
    DinamicoArray() : dados(nullptr), tamanho(0), capacidade(0) {
    }

    /**
     * Destrutor
     */
    ~DinamicoArray() {
        delete[] dados;
        dados = nullptr;
        tamanho = 0;
        capacidade = 0;
    }

    /**
     * Adiciona um elemento no final
     */
    void push_back(const T& valor) {
        redimensionar();
        dados[tamanho++] = valor;
    }

    /**
     * Retorna o tamanho
     */
    int size() const {
        return tamanho;
    }

    /**
     * Acessa elemento por índice
     */
    T& operator[](int idx) {
        return dados[idx];
    }

    /**
     * Acessa elemento por índice (const)
     */
    const T& operator[](int idx) const {
        return dados[idx];
    }

    /**
     * Limpa o array
     */
    void clear() {
        tamanho = 0;
    }

    /**
     * Retorna true se vazio
     */
    bool empty() const {
        return tamanho == 0;
    }

    /**
     * Retorna ponteiro para dados brutos
     */
    T* data() {
        return dados;
    }

    /**
     * Retorna ponteiro para dados brutos (const)
     */
    const T* data() const {
        return dados;
    }
};

#endif