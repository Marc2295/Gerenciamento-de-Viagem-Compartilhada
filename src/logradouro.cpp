#include "logradouro.hpp"

Logradouro::Logradouro()
    : idLog(""), nome(""), latMedia(0.0), lonMedia(0.0), quantidade(0) {
}

Logradouro::Logradouro(const std::string& idLog, const std::string& nome,
                       double latMedia, double lonMedia, int quantidade)
    : idLog(idLog), nome(nome), latMedia(latMedia), lonMedia(lonMedia),
      quantidade(quantidade) {
}

const std::string& Logradouro::getIdLog() const {
    return idLog;
}

const std::string& Logradouro::getNome() const {
    return nome;
}

double Logradouro::getLatMedia() const {
    return latMedia;
}

double Logradouro::getLonMedia() const {
    return lonMedia;
}

int Logradouro::getQuantidade() const {
    return quantidade;
}

void Logradouro::setIdLog(const std::string& idLog) {
    this->idLog = idLog;
}

void Logradouro::setNome(const std::string& nome) {
    this->nome = nome;
}

void Logradouro::setLatMedia(double latMedia) {
    this->latMedia = latMedia;
}

void Logradouro::setLonMedia(double lonMedia) {
    this->lonMedia = lonMedia;
}

void Logradouro::setQuantidade(int quantidade) {
    this->quantidade = quantidade;
}

void Logradouro::atualizarMedias(double novaLat, double novaLon) {
    // Cálculo incremental de média
    // media_nova = (media_antiga * n + valor) / (n + 1)
    if (quantidade == 0) {
        latMedia = novaLat;
        lonMedia = novaLon;
    } else {
        latMedia = (latMedia * quantidade + novaLat) / (quantidade + 1);
        lonMedia = (lonMedia * quantidade + novaLon) / (quantidade + 1);
    }
    quantidade++;
}

Logradouro::~Logradouro() {
}