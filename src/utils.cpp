#include "utils.hpp"

double calcularDistancia(double lat1, double lon1, double lat2, double lon2) {
    double deltaLat = lat2 - lat1;
    double deltaLon = lon2 - lon1;
    return std::sqrt(deltaLat * deltaLat + deltaLon * deltaLon);
}

std::string* dividirString(const std::string& str, char delim, int& tamanho) {
    // Primeira passada: conta quantas partes há
    int numPartes = 1;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            numPartes++;
        }
    }

    tamanho = numPartes;
    if (tamanho == 0 || str.empty()) {
        return nullptr;
    }

    std::string* arr = new std::string[tamanho];
    
    // Segunda passada: divide a string
    int idx = 0;
    size_t inicio = 0;
    
    for (size_t i = 0; i <= str.length(); i++) {
        if (i == str.length() || str[i] == delim) {
            if (i > inicio) {
                arr[idx] = str.substr(inicio, i - inicio);
                idx++;
            }
            inicio = i + 1;
        }
    }

    return arr;
}

std::string trim(const std::string& str) {
    // Encontra o primeiro caractere != ' '
    size_t inicio = 0;
    while (inicio < str.length() && 
           (str[inicio] == ' ' || str[inicio] == '\t' || 
            str[inicio] == '\n' || str[inicio] == '\r')) {
        inicio++;
    }

    // Se string toda é espaço
    if (inicio >= str.length()) {
        return "";
    }

    // Encontra o último caractere != ' '
    size_t fim = str.length() - 1;
    while (fim >= inicio && 
           (str[fim] == ' ' || str[fim] == '\t' || 
            str[fim] == '\n' || str[fim] == '\r')) {
        fim--;
    }

    return str.substr(inicio, fim - inicio + 1);
}

int stringParaInt(const std::string& str) {
    int resultado = 0;
    int sinal = 1;
    size_t i = 0;

    // Trata sinal negativo
    if (i < str.length() && str[i] == '-') {
        sinal = -1;
        i++;
    } else if (i < str.length() && str[i] == '+') {
        i++;
    }

    // Converte dígitos
    while (i < str.length() && str[i] >= '0' && str[i] <= '9') {
        resultado = resultado * 10 + (str[i] - '0');
        i++;
    }

    return resultado * sinal;
}

double stringParaDouble(const std::string& str) {
    double resultado = 0.0;
    double frator = 0.1;
    int sinal = 1;
    bool temDecimal = false;
    size_t i = 0;

    // Trata sinal
    if (i < str.length() && str[i] == '-') {
        sinal = -1;
        i++;
    } else if (i < str.length() && str[i] == '+') {
        i++;
    }

    // Processa parte inteira e decimal
    while (i < str.length()) {
        if (str[i] == '.') {
            temDecimal = true;
            i++;
            continue;
        }

        if (str[i] >= '0' && str[i] <= '9') {
            if (!temDecimal) {
                resultado = resultado * 10.0 + (str[i] - '0');
            } else {
                resultado += (str[i] - '0') * frator;
                frator *= 0.1;
            }
        }
        i++;
    }

    return resultado * sinal;
}

void trocar(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int particionar(int* arr, int baixo, int alto) {
    int pivo = arr[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (arr[j] < pivo) {
            i++;
            trocar(arr[i], arr[j]);
        }
    }
    trocar(arr[i + 1], arr[alto]);
    return (i + 1);
}

void quicksort(int* arr, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(arr, baixo, alto);

        quicksort(arr, baixo, pi - 1);
        quicksort(arr, pi + 1, alto);
    }
}