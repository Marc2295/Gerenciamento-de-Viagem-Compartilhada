#ifndef MAPA_H
#define MAPA_H

#include <string>

/**
 * TAD Mapa<K, V>
 * 
 * Implementação manual de uma estrutura de "mapa"
 * Usa Árvore AVL para manter ordem e busca eficiente O(log n)
 * 
 * Funcionalidades necessárias:
 * - Inserir par chave-valor
 * - Buscar valor por chave
 * - Verificar existência de chave
 * - Iterar sobre pares
 */

template<typename K, typename V>
struct ParChaveValor {
    K chave;
    V valor;

    ParChaveValor() : chave(K()), valor(V()) {}
    ParChaveValor(const K& k, const V& v) : chave(k), valor(v) {}
};

template<typename K, typename V>
struct NodoMapa {
    K chave;
    V valor;
    NodoMapa* esq;
    NodoMapa* dir;
    int altura;

    NodoMapa(const K& k, const V& v)
        : chave(k), valor(v), esq(nullptr), dir(nullptr), altura(1) {}

    ~NodoMapa() {
        // Nós serão deletados recursivamente
    }
};

template<typename K, typename V>
class Mapa {
private:
    NodoMapa<K, V>* raiz;

    int altura(NodoMapa<K, V>* nodo) const {
        return nodo == nullptr ? 0 : nodo->altura;
    }

    int fatorBalanceamento(NodoMapa<K, V>* nodo) const {
        return nodo == nullptr ? 0 : altura(nodo->esq) - altura(nodo->dir);
    }

    NodoMapa<K, V>* rotacaoDireita(NodoMapa<K, V>* y) {
        NodoMapa<K, V>* x = y->esq;
        NodoMapa<K, V>* T2 = x->dir;

        x->dir = y;
        y->esq = T2;

        y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));
        x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));

        return x;
    }

    NodoMapa<K, V>* rotacaoEsquerda(NodoMapa<K, V>* x) {
        NodoMapa<K, V>* y = x->dir;
        NodoMapa<K, V>* T2 = y->esq;

        y->esq = x;
        x->dir = T2;

        x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));
        y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));

        return y;
    }

    NodoMapa<K, V>* inserirRec(NodoMapa<K, V>* nodo, const K& chave, const V& valor) {
        if (nodo == nullptr) {
            return new NodoMapa<K, V>(chave, valor);
        }

        if (chave < nodo->chave) {
            nodo->esq = inserirRec(nodo->esq, chave, valor);
        } else if (chave > nodo->chave) {
            nodo->dir = inserirRec(nodo->dir, chave, valor);
        } else {
            // Chave existe, atualiza valor
            nodo->valor = valor;
            return nodo;
        }

        nodo->altura = 1 + (altura(nodo->esq) > altura(nodo->dir) ? 
                            altura(nodo->esq) : altura(nodo->dir));

        int fb = fatorBalanceamento(nodo);

        // Caso Left-Left
        if (fb > 1 && chave < nodo->esq->chave) {
            return rotacaoDireita(nodo);
        }

        // Caso Right-Right
        if (fb < -1 && chave > nodo->dir->chave) {
            return rotacaoEsquerda(nodo);
        }

        // Caso Left-Right
        if (fb > 1 && chave > nodo->esq->chave) {
            nodo->esq = rotacaoEsquerda(nodo->esq);
            return rotacaoDireita(nodo);
        }

        // Caso Right-Left
        if (fb < -1 && chave < nodo->dir->chave) {
            nodo->dir = rotacaoDireita(nodo->dir);
            return rotacaoEsquerda(nodo);
        }

        return nodo;
    }

    NodoMapa<K, V>* buscarRec(NodoMapa<K, V>* nodo, const K& chave) const {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (chave == nodo->chave) {
            return nodo;
        } else if (chave < nodo->chave) {
            return buscarRec(nodo->esq, chave);
        } else {
            return buscarRec(nodo->dir, chave);
        }
    }

    void desalocarRec(NodoMapa<K, V>* nodo) {
        if (nodo == nullptr) {
            return;
        }
        desalocarRec(nodo->esq);
        desalocarRec(nodo->dir);
        delete nodo;
    }

    void coletarParesRec(NodoMapa<K, V>* nodo, ParChaveValor<K, V>* pares, int& idx) const {
        if (nodo == nullptr) {
            return;
        }
        coletarParesRec(nodo->esq, pares, idx);
        pares[idx++] = ParChaveValor<K, V>(nodo->chave, nodo->valor);
        coletarParesRec(nodo->dir, pares, idx);
    }

public:
    Mapa() : raiz(nullptr) {}

    ~Mapa() {
        desalocarRec(raiz);
        raiz = nullptr;
    }

    /**
     * Insere ou atualiza um par chave-valor
     */
    void inserir(const K& chave, const V& valor) {
        raiz = inserirRec(raiz, chave, valor);
    }

    /**
     * Busca um valor pela chave
     * Retorna ponteiro para o valor ou nullptr
     */
    V* buscar(const K& chave) {
        NodoMapa<K, V>* nodo = buscarRec(raiz, chave);
        if (nodo != nullptr) {
            return &(nodo->valor);
        }
        return nullptr;
    }

    /**
     * Busca um valor pela chave (const)
     */
    const V* buscar(const K& chave) const {
        NodoMapa<K, V>* nodo = buscarRec(raiz, chave);
        if (nodo != nullptr) {
            return &(nodo->valor);
        }
        return nullptr;
    }

    /**
     * Verifica se chave existe
     */
    bool contem(const K& chave) const {
        return buscarRec(raiz, chave) != nullptr;
    }

    /**
     * Retorna número de pares
     */
    int tamanho() const {
        return contarNodosRec(raiz);
    }

    /**
     * Retorna true se vazio
     */
    bool vazio() const {
        return raiz == nullptr;
    }

    /**
     * Coleta todos os pares em ordem (in-order)
     * O chamador deve liberar a memória retornada
     */
    ParChaveValor<K, V>* coletarTodos(int& tamanho) const {
        tamanho = contarNodosRec(raiz);
        if (tamanho == 0) {
            return nullptr;
        }

        ParChaveValor<K, V>* pares = new ParChaveValor<K, V>[tamanho];
        int idx = 0;
        coletarParesRec(raiz, pares, idx);
        return pares;
    }

private:
    int contarNodosRec(NodoMapa<K, V>* nodo) const {
        if (nodo == nullptr) {
            return 0;
        }
        return 1 + contarNodosRec(nodo->esq) + contarNodosRec(nodo->dir);
    }
};

#endif