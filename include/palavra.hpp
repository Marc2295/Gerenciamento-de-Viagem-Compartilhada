#ifndef PALAVRA_H
#define PALAVRA_H

#include <string>

/**
 * Nó de uma lista dinâmica de inteiros
 * Usado para armazenar IDs de logradouros associados a uma palavra
 */
struct NodoListaInt {
    int valor;
    NodoListaInt* prox;

    NodoListaInt(int valor) : valor(valor), prox(nullptr) {}
};

/**
 * Lista dinâmica de inteiros para armazenar IDs de logradouros
 * Mantida em ordem crescente para facilitar interseção eficiente
 */
class ListaInteiros {
private:
    NodoListaInt* inicio;
    int tamanho;

public:
    ListaInteiros();
    ~ListaInteiros();

    /**
     * Insere um valor mantendo a ordem crescente
     * Evita duplicatas
     */
    void inserir(int valor);

    /**
     * Retorna o primeiro nodo da lista
     */
    NodoListaInt* getInicio() const;

    /**
     * Retorna o tamanho da lista
     */
    int getTamanho() const;

    /**
     * Verifica se um valor está na lista
     */
    bool contem(int valor) const;

    /**
     * Retorna um array com cópia dos valores
     */
    int* toArray() const;
};

/**
 * Nó da Árvore AVL
 * Armazena uma palavra e a lista de logradouros onde ela ocorre
 */
struct NodoAVL {
    std::string palavra;
    ListaInteiros* logradouros;
    NodoAVL* esq;
    NodoAVL* dir;
    int altura;

    NodoAVL(const std::string& palavra)
        : palavra(palavra), logradouros(nullptr), esq(nullptr), 
          dir(nullptr), altura(1) {
        logradouros = new ListaInteiros();
    }

    ~NodoAVL() {
        delete logradouros;
    }
};

/**
 * TAD Palavra - Índice Invertido implementado com Árvore AVL
 * 
 * Mapeia cada palavra única para uma lista de logradouros onde ela ocorre.
 * A árvore AVL garante operações de busca, inserção em O(log n) tempo.
 * 
 * As listas de logradouros são mantidas em ordem crescente para permitir
 * interseção eficiente durante processamento de consultas.
 */
class Palavra {
private:
    NodoAVL* raiz;
    int numPalavras;

    /**
     * Retorna a altura de um nodo (0 se nullptr)
     */
    int altura(NodoAVL* nodo) const;

    /**
     * Calcula o fator de balanceamento de um nodo
     */
    int fatorBalanceamento(NodoAVL* nodo) const;

    /**
     * Rotação simples à direita
     */
    NodoAVL* rotacaoDireita(NodoAVL* y);

    /**
     * Rotação simples à esquerda
     */
    NodoAVL* rotacaoEsquerda(NodoAVL* x);

    /**
     * Rotação dupla esquerda-direita
     */
    NodoAVL* rotacaoEsquerdaDireita(NodoAVL* nodo);

    /**
     * Rotação dupla direita-esquerda
     */
    NodoAVL* rotacaoDireitaEsquerda(NodoAVL* nodo);

    /**
     * Insere recursivamente na árvore
     */
    NodoAVL* inserirRec(NodoAVL* nodo, const std::string& palavra);

    /**
     * Busca recursivamente na árvore
     */
    NodoAVL* buscarRec(NodoAVL* nodo, const std::string& palavra) const;

    /**
     * Desaloca recursivamente toda a árvore
     */
    void desalocarRec(NodoAVL* nodo);

public:
    /**
     * Construtor
     */
    Palavra();

    /**
     * Destrutor
     */
    ~Palavra();

    /**
     * Insere uma palavra ou recupera a existente
     * Retorna a lista de logradouros da palavra
     */
    ListaInteiros* obterPalavra(const std::string& palavra);

    /**
     * Busca uma palavra na árvore
     * Retorna nullptr se não encontrada
     */
    ListaInteiros* buscar(const std::string& palavra) const;

    /**
     * Retorna o número total de palavras únicas
     */
    int getNumPalavras() const;

    /**
     * Adiciona um logradouro a uma palavra existente ou cria uma nova entrada
     */
    void adicionarLogradouro(const std::string& palavra, int idLog);
};

#endif // PALAVRA_H