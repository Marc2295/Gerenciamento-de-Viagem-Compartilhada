#ifndef CONSULTA_H
#define CONSULTA_H

#include "palavra.hpp"
#include "logradouro.hpp"
#include <string>

/**
 * Estrutura para representar um candidato (logradouro com distância)
 * Utilizado no min-heap de tamanho R
 */
struct Candidato {
    int idLog;
    std::string nome;
    double distancia;

    Candidato() : idLog(0), nome(""), distancia(0.0) {}
    Candidato(int idLog, const std::string& nome, double distancia)
        : idLog(idLog), nome(nome), distancia(distancia) {}

    // Comparação para min-heap (maior distância no topo para fácil remoção)
    bool operator<(const Candidato& outro) const {
        return distancia < outro.distancia; // Inverte para max-heap (remove o maior)
    }

    bool operator>(const Candidato& outro) const {
        return distancia > outro.distancia;
    }
};

/**
 * Min-Heap de tamanho limitado para manter os R logradouros mais próximos
 * Implementado como árvore binária em array
 */
class MaxHeapCandidatos {
private:
    Candidato* heap;
    int tamanho;
    int capacidade;

    /**
     * Retorna o índice do pai de um nodo
     */
    int pai(int i) const;

    /**
     * Retorna o índice do filho esquerdo
     */
    int filhoEsq(int i) const;

    /**
     * Retorna o índice do filho direito
     */
    int filhoDir(int i) const;

    /**
     * Sobe um elemento na heap (heapify up)
     */
    void subirHeap(int idx);

    /**
     * Desce um elemento na heap (heapify down)
     */
    void descerHeap(int idx);

public:
    /**
     * Construtor
     */
    MaxHeapCandidatos(int capacidade);

    /**
     * Destrutor
     */
    ~MaxHeapCandidatos();

    /**
     * Insere um candidato no heap
     * Se heap está cheio e candidato é melhor que o pior, remove o pior e insere
     */
    void inserir(const Candidato& candidato);

    /**
     * Remove e retorna o elemento com maior distância (raiz do max-heap)
     */
    Candidato removerTopo();

    /**
     * Retorna o topo sem remover
     */
    Candidato getTopo() const;

    /**
     * Retorna o número de candidatos na heap
     */
    int getTamanho() const;

    /**
     * Retorna true se a heap está cheia
     */
    bool estaCheia() const;

    /**
     * Retorna true se a heap está vazia
     */
    bool estaVazia() const;

    /**
     * Extrai todos os candidatos ordenados por distância crescente
     * Retorna um array e atualiza tamanho
     */
    Candidato* extrairOrdenado(int& tamanhoResultado);
};

/**
 * TAD Consulta
 * 
 * Coordena a execução de uma consulta ao sistema de despacho.
 * Integra informações dos TADs Logradouro e Palavra para gerar respostas.
 * 
 * Fase 1: Recuperação de listas de logradouros para cada palavra
 * Fase 2: Interseção das listas e cálculo de distâncias euclidianas
 * Fase 3: Uso de min-heap de tamanho R para seleção dos R melhores
 */
class Consulta {
private:
    int idConsulta;
    std::string consultaTexto;
    double latOrigem;
    double lonOrigem;
    int maxRespostas;

public:
    /**
     * Construtor
     */
    Consulta(int idConsulta, const std::string& consultaTexto,
             double latOrigem, double lonOrigem, int maxRespostas);

    /**
     * Destrutor
     */
    ~Consulta();

    /**
     * Getters
     */
    int getIdConsulta() const;
    const std::string& getConsultaTexto() const;
    double getLatOrigem() const;
    double getLonOrigem() const;
    int getMaxRespostas() const;

    /**
     * Executa a consulta usando os índices de palavra e logradouros
     * Retorna um array de candidatos e atualiza tamanho
     * 
     * Fase 1: Recupera listas de logradouros para cada palavra da consulta
     * Fase 2: Calcula a interseção das listas (logradouros com TODAS as palavras)
     *         e calcula distâncias euclidianas até a origem
     * Fase 3: Usa min-heap de tamanho R para selecionar os R melhores
     */
    Candidato* executar(Palavra* indice,
                        Logradouro** logradourosArray,
                        int numLogradouros,
                        double latOrigem,
                        double lonOrigem,
                        int& tamanhoResultado);
};

#endif // CONSULTA_H