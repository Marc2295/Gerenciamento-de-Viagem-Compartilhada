#include "palavra.hpp"

// ============================================================================
// ListaInteiros - Implementação
// ============================================================================

ListaInteiros::ListaInteiros() : inicio(nullptr), tamanho(0) {
}

ListaInteiros::~ListaInteiros() {
    NodoListaInt* atual = inicio;
    while (atual != nullptr) {
        NodoListaInt* temp = atual;
        atual = atual->prox;
        delete temp;
    }
    inicio = nullptr;
    tamanho = 0;
}

void ListaInteiros::inserir(int valor) {
    // Evita duplicatas
    if (contem(valor)) {
        return;
    }

    // Se lista vazia ou valor é menor que o primeiro
    if (inicio == nullptr || valor < inicio->valor) {
        NodoListaInt* novo = new NodoListaInt(valor);
        novo->prox = inicio;
        inicio = novo;
        tamanho++;
        return;
    }

    // Encontra a posição correta para manter ordenação
    NodoListaInt* atual = inicio;
    while (atual->prox != nullptr && atual->prox->valor < valor) {
        atual = atual->prox;
    }

    NodoListaInt* novo = new NodoListaInt(valor);
    novo->prox = atual->prox;
    atual->prox = novo;
    tamanho++;
}

NodoListaInt* ListaInteiros::getInicio() const {
    return inicio;
}

int ListaInteiros::getTamanho() const {
    return tamanho;
}

bool ListaInteiros::contem(int valor) const {
    NodoListaInt* atual = inicio;
    while (atual != nullptr) {
        if (atual->valor == valor) {
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

int* ListaInteiros::toArray() const {
    if (tamanho == 0) {
        return nullptr;
    }

    int* arr = new int[tamanho];
    int idx = 0;
    NodoListaInt* atual = inicio;
    while (atual != nullptr) {
        arr[idx++] = atual->valor;
        atual = atual->prox;
    }
    return arr;
}

// ============================================================================
// Palavra (Árvore AVL) - Implementação
// ============================================================================

Palavra::Palavra() : raiz(nullptr), numPalavras(0) {
}

Palavra::~Palavra() {
    desalocarRec(raiz);
    raiz = nullptr;
}

int Palavra::altura(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

int Palavra::fatorBalanceamento(NodoAVL* nodo) const {
    if (nodo == nullptr) {
        return 0;
    }
    return altura(nodo->esq) - altura(nodo->dir);
}

NodoAVL* Palavra::rotacaoDireita(NodoAVL* y) {
    NodoAVL* x = y->esq;
    NodoAVL* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));
    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));

    return x;
}

NodoAVL* Palavra::rotacaoEsquerda(NodoAVL* x) {
    NodoAVL* y = x->dir;
    NodoAVL* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + (altura(x->esq) > altura(x->dir) ? altura(x->esq) : altura(x->dir));
    y->altura = 1 + (altura(y->esq) > altura(y->dir) ? altura(y->esq) : altura(y->dir));

    return y;
}

NodoAVL* Palavra::rotacaoEsquerdaDireita(NodoAVL* nodo) {
    nodo->esq = rotacaoEsquerda(nodo->esq);
    return rotacaoDireita(nodo);
}

NodoAVL* Palavra::rotacaoDireitaEsquerda(NodoAVL* nodo) {
    nodo->dir = rotacaoDireita(nodo->dir);
    return rotacaoEsquerda(nodo);
}

NodoAVL* Palavra::inserirRec(NodoAVL* nodo, const std::string& palavra) {
    if (nodo == nullptr) {
        numPalavras++;
        return new NodoAVL(palavra);
    }

    if (palavra < nodo->palavra) {
        nodo->esq = inserirRec(nodo->esq, palavra);
    } else if (palavra > nodo->palavra) {
        nodo->dir = inserirRec(nodo->dir, palavra);
    } else {
        // Palavra já existe, não inserir duplicata
        return nodo;
    }

    nodo->altura = 1 + (altura(nodo->esq) > altura(nodo->dir) ? 
                        altura(nodo->esq) : altura(nodo->dir));

    int fb = fatorBalanceamento(nodo);

    // Caso Left-Left
    if (fb > 1 && palavra < nodo->esq->palavra) {
        return rotacaoDireita(nodo);
    }

    // Caso Right-Right
    if (fb < -1 && palavra > nodo->dir->palavra) {
        return rotacaoEsquerda(nodo);
    }

    // Caso Left-Right
    if (fb > 1 && palavra > nodo->esq->palavra) {
        return rotacaoEsquerdaDireita(nodo);
    }

    // Caso Right-Left
    if (fb < -1 && palavra < nodo->dir->palavra) {
        return rotacaoDireitaEsquerda(nodo);
    }

    return nodo;
}

NodoAVL* Palavra::buscarRec(NodoAVL* nodo, const std::string& palavra) const {
    if (nodo == nullptr) {
        return nullptr;
    }

    if (palavra == nodo->palavra) {
        return nodo;
    } else if (palavra < nodo->palavra) {
        return buscarRec(nodo->esq, palavra);
    } else {
        return buscarRec(nodo->dir, palavra);
    }
}

void Palavra::desalocarRec(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return;
    }
    desalocarRec(nodo->esq);
    desalocarRec(nodo->dir);
    delete nodo;
}

ListaInteiros* Palavra::obterPalavra(const std::string& palavra) {
    NodoAVL* nodo = buscarRec(raiz, palavra);
    
    if (nodo != nullptr) {
        return nodo->logradouros;
    }

    // Palavra não existe, inserir e retornar
    raiz = inserirRec(raiz, palavra);
    nodo = buscarRec(raiz, palavra);
    return nodo->logradouros;
}

ListaInteiros* Palavra::buscar(const std::string& palavra) const {
    NodoAVL* nodo = buscarRec(raiz, palavra);
    if (nodo != nullptr) {
        return nodo->logradouros;
    }
    return nullptr;
}

int Palavra::getNumPalavras() const {
    return numPalavras;
}

void Palavra::adicionarLogradouro(const std::string& palavra, int idLog) {
    ListaInteiros* lista = obterPalavra(palavra);
    if (lista != nullptr) {
        lista->inserir(idLog);
    }
}