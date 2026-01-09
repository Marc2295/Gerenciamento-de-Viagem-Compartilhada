#include "endereco.hpp"
#include "logradouro.hpp"
#include "palavra.hpp"
#include "consulta.hpp"
#include "utils.hpp"
#include "dinamico_array.hpp"
#include "mapa.hpp"
#include <iostream>

int main() {
    int N, M, R;
    
    std::cin >> N;
    std::cin.ignore();

    // Mapa para armazenar logradouros únicos durante leitura
    Mapa<std::string, Logradouro*> logradourosMap;
    
    // Índice invertido de palavras -> logradouros
    Palavra* indiceAVL = new Palavra();

    // ========================================================================
    // FASE DE CONSTRUÇÃO: Leitura e construção dos TADs incrementalmente
    // ========================================================================

    for (int i = 0; i < N; i++) {
        std::string linha;
        std::getline(std::cin, linha);
        linha = trim(linha);

        if (linha.empty()) {
            i--;
            continue;
        }

        int numCampos = 0;
        std::string* campos = dividirString(linha, ';', numCampos);

        if (numCampos != 10) {
            delete[] campos;
            i--;
            continue;
        }

        std::string idEnd = trim(campos[0]);
        std::string idLog = trim(campos[1]);
        std::string tipoLog = trim(campos[2]);
        std::string log = trim(campos[3]);
        
        double lat = 0.0, lon = 0.0;
        try {
            lat = stringParaDouble(trim(campos[8]));
            lon = stringParaDouble(trim(campos[9]));
        } catch (...) {
            delete[] campos;
            i--;
            continue;
        }

        Logradouro* log_ptr = logradourosMap.buscar(idLog) != nullptr ? 
                              *logradourosMap.buscar(idLog) : nullptr;

        if (log_ptr == nullptr) {
            Logradouro* novo = new Logradouro(idLog, log, lat, lon, 1);
            logradourosMap.inserir(idLog, novo);
        } else {
            log_ptr->atualizarMedias(lat, lon);
        }

        int numPalavras = 0;
        std::string* palavras = dividirString(log, ' ', numPalavras);

        if (palavras != nullptr) {
            for (int j = 0; j < numPalavras; j++) {
                std::string palavra = trim(palavras[j]);
                if (!palavra.empty()) {
                    try {
                        int idLogInt = stringParaInt(idLog);
                        indiceAVL->adicionarLogradouro(palavra, idLogInt);
                    } catch (...) {
                    }
                }
            }
            delete[] palavras;
        }

        delete[] campos;
    }

    std::cin >> M >> R;
    std::cin.ignore();

    // Converte mapa de logradouros para array e coleta pares
    int numLogradouros = 0;
    ParChaveValor<std::string, Logradouro*>* pares = logradourosMap.coletarTodos(numLogradouros);

    DinamicoArray<Logradouro*> logradourosArray;
    for (int i = 0; i < numLogradouros; i++) {
        logradourosArray.push_back(pares[i].valor);
    }

    if (pares != nullptr) {
        delete[] pares;
    }

    // ========================================================================
    // FASE DE CONSULTAS: Processa as M consultas
    // ========================================================================

    std::cout << M << std::endl;
    for (int i = 0; i < M; i++) {
        std::string linha;
        std::getline(std::cin, linha);
        linha = trim(linha);

        if (linha.empty()) {
            i--;
            continue;
        }

        int numCampos = 0;
        std::string* campos = dividirString(linha, ';', numCampos);

        if (numCampos != 4) {
            delete[] campos;
            i--;
            continue;
        }

        int idConsulta = 0;
        double latOrigem = 0.0, lonOrigem = 0.0;

        try {
            idConsulta = stringParaInt(trim(campos[0]));
            latOrigem = stringParaDouble(trim(campos[2]));
            lonOrigem = stringParaDouble(trim(campos[3]));
        } catch (...) {
            delete[] campos;
            i--;
            continue;
        }

        std::string consultaTexto = trim(campos[1]);

        Consulta consulta(idConsulta, consultaTexto, latOrigem, lonOrigem, R);

        int numResultados = 0;
        Candidato* resultados = consulta.executar(indiceAVL, 
                                                  logradourosArray.data(), 
                                                  logradourosArray.size(), 
                                                  latOrigem, lonOrigem,
                                                  numResultados);

        std::cout << idConsulta << ";" << numResultados << std::endl;

        if (resultados != nullptr) {
            for (int j = 0; j < numResultados; j++) {
                std::cout << resultados[j].idLog << ";" << resultados[j].nome << std::endl;
            }
            delete[] resultados;
        }

        delete[] campos;
    }

    // ========================================================================
    // Liberação de memória
    // ========================================================================

    delete indiceAVL;

    for (int i = 0; i < logradourosArray.size(); i++) {
        delete logradourosArray[i];
    }

    return 0;
}