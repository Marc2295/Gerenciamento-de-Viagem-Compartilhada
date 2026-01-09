#include "consulta.hpp"
#include "utils.hpp"
#include <cstring>

// ============================================================================
// MaxHeapCandidatos - Implementação
// ============================================================================

MaxHeapCandidatos::MaxHeapCandidatos(int capacidade)
    : tamanho(0), capacidade(capacidade) {
    heap = new Candidato[capacidade];
}

MaxHeapCandidatos::~MaxHeapCandidatos() {
    delete[] heap;
}

int MaxHeapCandidatos::pai(int i) const {
    return (i - 1) / 2;
}

int MaxHeapCandidatos::filhoEsq(int i) const {
    return 2 * i + 1;
}

int MaxHeapCandidatos::filhoDir(int i) const {
    return 2 * i + 2;
}

void MaxHeapCandidatos::subirHeap(int idx) {
    while (idx > 0 && heap[idx] > heap[pai(idx)]) {
        // Troca com pai (sobe se candidato é melhor que pai)
        Candidato temp = heap[idx];
        heap[idx] = heap[pai(idx)];
        heap[pai(idx)] = temp;
        idx = pai(idx);
    }
}

void MaxHeapCandidatos::descerHeap(int idx) {
    while (true) {
        int maior = idx;
        int esq = filhoEsq(idx);
        int dir = filhoDir(idx);

        // Encontra o maior entre pai, filho esquerdo e direito
        if (esq < tamanho && heap[esq] > heap[maior]) {
            maior = esq;
        }
        if (dir < tamanho && heap[dir] > heap[maior]) {
            maior = dir;
        }

        if (maior != idx) {
            Candidato temp = heap[idx];
            heap[idx] = heap[maior];
            heap[maior] = temp;
            idx = maior;
        } else {
            break;
        }
    }
}

void MaxHeapCandidatos::inserir(const Candidato& candidato) {
    if (tamanho < capacidade) {
        // Heap não está cheia, inserir normalmente
        heap[tamanho] = candidato;
        subirHeap(tamanho);
        tamanho++;
    } else if (candidato < heap[0]) {
        // Heap cheia, mas novo candidato é melhor que o pior (topo)
        // Remove o pior (topo) e insere o novo
        heap[0] = candidato;
        descerHeap(0);
    }
    // Caso contrário, candidato não entra pois é pior que os já armazenados
}

Candidato MaxHeapCandidatos::removerTopo() {
    Candidato topo = heap[0];
    heap[0] = heap[tamanho - 1];
    tamanho--;
    if (tamanho > 0) {
        descerHeap(0);
    }
    return topo;
}

Candidato MaxHeapCandidatos::getTopo() const {
    return heap[0];
}

int MaxHeapCandidatos::getTamanho() const {
    return tamanho;
}

bool MaxHeapCandidatos::estaCheia() const {
    return tamanho == capacidade;
}

bool MaxHeapCandidatos::estaVazia() const {
    return tamanho == 0;
}

Candidato* MaxHeapCandidatos::extrairOrdenado(int& tamanhoResultado) {
    if (tamanho == 0) {
        tamanhoResultado = 0;
        return nullptr;
    }

    tamanhoResultado = tamanho;
    Candidato* resultado = new Candidato[tamanhoResultado];

    // Extrai do heap em ordem reversa para obter ordem crescente de distância
    for (int i = tamanhoResultado - 1; i >= 0; i--) {
        resultado[i] = removerTopo();
    }

    return resultado;
}

// ============================================================================
// Consulta - Implementação
// ============================================================================

Consulta::Consulta(int idConsulta, const std::string& consultaTexto,
                   double latOrigem, double lonOrigem, int maxRespostas)
    : idConsulta(idConsulta), consultaTexto(consultaTexto),
      latOrigem(latOrigem), lonOrigem(lonOrigem), maxRespostas(maxRespostas) {
}

Consulta::~Consulta() {
}

int Consulta::getIdConsulta() const {
    return idConsulta;
}

const std::string& Consulta::getConsultaTexto() const {
    return consultaTexto;
}

double Consulta::getLatOrigem() const {
    return latOrigem;
}

double Consulta::getLonOrigem() const {
    return lonOrigem;
}

int Consulta::getMaxRespostas() const {
    return maxRespostas;
}

/**
 * Função auxiliar para interseção eficiente de duas listas ordenadas
 * Tempo: O(n + m) onde n e m são os tamanhos das listas
 * Retorna um array com IDs comuns mantendo ordenação
 */
static int* intersecaoDuasListas(const int* lista1, int tam1, 
                                 const int* lista2, int tam2,
                                 int& tamanhoResultado) {
    if (tam1 == 0 || tam2 == 0) {
        tamanhoResultado = 0;
        return nullptr;
    }

    // Aloca espaço máximo possível (mínimo dos tamanhos)
    int maxTamanho = tam1 < tam2 ? tam1 : tam2;
    int* resultado = new int[maxTamanho];
    int idx = 0;
    int i1 = 0, i2 = 0;

    // Algoritmo de interseção com duas listas ordenadas: O(n + m)
    while (i1 < tam1 && i2 < tam2) {
        if (lista1[i1] == lista2[i2]) {
            resultado[idx++] = lista1[i1];
            i1++;
            i2++;
        } else if (lista1[i1] < lista2[i2]) {
            i1++;
        } else {
            i2++;
        }
    }

    tamanhoResultado = idx;
    
    if (tamanhoResultado == 0) {
        delete[] resultado;
        return nullptr;
    }

    return resultado;
}

Candidato* Consulta::executar(Palavra* indice,
                             Logradouro** logradourosArray,
                             int numLogradouros,
                             double latOrigem,
                             double lonOrigem,
                             int& tamanhoResultado) {
    tamanhoResultado = 0;

    if (indice == nullptr || logradourosArray == nullptr || numLogradouros == 0) {
        return nullptr;
    }

    // ========================================================================
    // FASE 1: Dividir consulta em palavras e recuperar listas de logradouros
    // ========================================================================
    
    int numPalavrasConsulta = 0;
    std::string* palavrasConsulta = dividirString(consultaTexto, ' ', numPalavrasConsulta);

    if (numPalavrasConsulta == 0 || palavrasConsulta == nullptr) {
        return nullptr;
    }

    // Recuperar listas de logradouros para cada palavra
    int** listasLogradouros = new int*[numPalavrasConsulta];
    int* tamanhosListas = new int[numPalavrasConsulta];

    for (int i = 0; i < numPalavrasConsulta; i++) {
        ListaInteiros* lista = indice->buscar(palavrasConsulta[i]);
        if (lista == nullptr || lista->getTamanho() == 0) {
            tamanhosListas[i] = 0;
            listasLogradouros[i] = nullptr;
        } else {
            listasLogradouros[i] = lista->toArray();
            tamanhosListas[i] = lista->getTamanho();
            
            // Ordenar a lista para permitir interseção eficiente
            if (tamanhosListas[i] > 1) {
                quicksort(listasLogradouros[i], 0, tamanhosListas[i] - 1);
            }
        }
    }

    // ========================================================================
    // FASE 2: Interseção das listas (logradouros com TODAS as palavras)
    //         Cálculo de distâncias euclidianas
    // ========================================================================
    
    int* candidatos = nullptr;
    int numCandidatos = 0;

    if (numPalavrasConsulta == 1) {
        // Se há apenas uma palavra, os candidatos são todos da lista
        if (listasLogradouros[0] != nullptr && tamanhosListas[0] > 0) {
            numCandidatos = tamanhosListas[0];
            candidatos = new int[numCandidatos];
            for (int i = 0; i < numCandidatos; i++) {
                candidatos[i] = listasLogradouros[0][i];
            }
        }
    } else {
        // Múltiplas palavras - fazer interseção sucessiva
        int* temp = nullptr;
        int tempTamanho = 0;

        // Começa com as duas primeiras listas
        if (listasLogradouros[0] != nullptr && listasLogradouros[1] != nullptr &&
            tamanhosListas[0] > 0 && tamanhosListas[1] > 0) {
            temp = intersecaoDuasListas(listasLogradouros[0], tamanhosListas[0],
                                       listasLogradouros[1], tamanhosListas[1],
                                       tempTamanho);
        }

        // Intersecta progressivamente com as demais listas
        for (int i = 2; i < numPalavrasConsulta && tempTamanho > 0; i++) {
            if (listasLogradouros[i] != nullptr && tamanhosListas[i] > 0) {
                int* novo = intersecaoDuasListas(temp, tempTamanho,
                                                listasLogradouros[i], tamanhosListas[i],
                                                numCandidatos);
                delete[] temp;
                temp = novo;
                tempTamanho = numCandidatos;
            } else {
                tempTamanho = 0;
                if (temp != nullptr) delete[] temp;
                temp = nullptr;
                break;
            }
        }

        candidatos = temp;
        numCandidatos = tempTamanho;
    }

    // ========================================================================
    // FASE 3: Max-Heap de tamanho R para selecionar os R melhores
    // ========================================================================
    
    MaxHeapCandidatos heap(maxRespostas);

    for (int i = 0; i < numCandidatos; i++) {
        int idLog = candidatos[i];
        
        // Encontrar o logradouro correspondente a este idLog
        Logradouro* logradouro = nullptr;
        for (int j = 0; j < numLogradouros; j++) {
            if (logradourosArray[j] != nullptr) {
                try {
                    int idLogArray = std::stoi(logradourosArray[j]->getIdLog());
                    if (idLogArray == idLog) {
                        logradouro = logradourosArray[j];
                        break;
                    }
                } catch (...) {
                    // Erro de conversão, pula
                }
            }
        }

        if (logradouro != nullptr) {
            // FASE 2: Calcular distância euclidiana
            double distancia = calcularDistancia(latOrigem, lonOrigem,
                                                logradouro->getLatMedia(),
                                                logradouro->getLonMedia());

            // FASE 3: Inserir na heap se for um dos R melhores
            Candidato cand(idLog, logradouro->getNome(), distancia);
            heap.inserir(cand);
        }
    }

    // Extrai os resultados ordenados
    Candidato* resultado = nullptr;
    if (heap.getTamanho() > 0) {
        resultado = heap.extrairOrdenado(tamanhoResultado);
    } else {
        tamanhoResultado = 0;
    }

    // ========================================================================
    // Limpeza de memória
    // ========================================================================
    
    for (int i = 0; i < numPalavrasConsulta; i++) {
        if (listasLogradouros[i] != nullptr) {
            delete[] listasLogradouros[i];
        }
    }
    delete[] listasLogradouros;
    delete[] tamanhosListas;
    delete[] palavrasConsulta;
    
    if (candidatos != nullptr) {
        delete[] candidatos;
    }

    return resultado;
}