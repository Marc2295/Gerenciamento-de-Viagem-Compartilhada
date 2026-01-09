#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cmath>

/**
 * Funções utilitárias para o sistema de consulta
 */

/**
 * Calcula a distância euclidiana entre dois pontos
 * Utilizada para encontrar logradouros mais próximos da origem
 * 
 * @param lat1 Latitude do ponto 1
 * @param lon1 Longitude do ponto 1
 * @param lat2 Latitude do ponto 2
 * @param lon2 Longitude do ponto 2
 * @return Distância euclidiana entre os pontos
 */
double calcularDistancia(double lat1, double lon1, double lat2, double lon2);

/**
 * Divide uma string por um delimitador e retorna um array de strings
 * O chamador é responsável por liberar a memória do array retornado
 * 
 * @param str String a ser dividida
 * @param delim Delimitador
 * @param tamanho Referência que recebe o número de partes
 * @return Array de strings contendo as partes
 */
std::string* dividirString(const std::string& str, char delim, int& tamanho);

/**
 * Remove espaços em branco do início e final de uma string
 * 
 * @param str String a ser 'aparada'
 * @return String sem espaços laterais
 */
std::string trim(const std::string& str);

/**
 * Converte uma string para inteiro
 * 
 * @param str String a converter
 * @return Inteiro representado pela string
 */
int stringParaInt(const std::string& str);

/**
 * Converte uma string para double
 * 
 * @param str String a converter
 * @return Double representado pela string
 */
double stringParaDouble(const std::string& str);

/*
 * Quicksort
 */

void trocar(int& a, int& b);

int particionar(int* arr, int baixo, int alto);

void quicksort(int* arr, int baixo, int alto);

#endif // UTILS_H