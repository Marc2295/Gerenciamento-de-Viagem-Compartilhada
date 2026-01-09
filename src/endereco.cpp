#include "endereco.hpp"

Endereco::Endereco() 
    : idEnd(""), idLog(""), tipoLog(""), log(""), num(""), 
      bairro(""), regiao(""), cep(""), lat(0.0), lon(0.0) {
}

Endereco::Endereco(const std::string& idEnd, const std::string& idLog,
                   const std::string& tipoLog, const std::string& log,
                   const std::string& num, const std::string& bairro,
                   const std::string& regiao, const std::string& cep,
                   double lat, double lon)
    : idEnd(idEnd), idLog(idLog), tipoLog(tipoLog), log(log),
      num(num), bairro(bairro), regiao(regiao), cep(cep),
      lat(lat), lon(lon) {
}

const std::string& Endereco::getIdEnd() const {
    return idEnd;
}

const std::string& Endereco::getIdLog() const {
    return idLog;
}

const std::string& Endereco::getTipoLog() const {
    return tipoLog;
}

const std::string& Endereco::getLog() const {
    return log;
}

const std::string& Endereco::getNum() const {
    return num;
}

const std::string& Endereco::getBairro() const {
    return bairro;
}

const std::string& Endereco::getRegiao() const {
    return regiao;
}

const std::string& Endereco::getCep() const {
    return cep;
}

double Endereco::getLat() const {
    return lat;
}

double Endereco::getLon() const {
    return lon;
}

void Endereco::setIdEnd(const std::string& idEnd) {
    this->idEnd = idEnd;
}

void Endereco::setIdLog(const std::string& idLog) {
    this->idLog = idLog;
}

void Endereco::setTipoLog(const std::string& tipoLog) {
    this->tipoLog = tipoLog;
}

void Endereco::setLog(const std::string& log) {
    this->log = log;
}

void Endereco::setNum(const std::string& num) {
    this->num = num;
}

void Endereco::setBairro(const std::string& bairro) {
    this->bairro = bairro;
}

void Endereco::setRegiao(const std::string& regiao) {
    this->regiao = regiao;
}

void Endereco::setCep(const std::string& cep) {
    this->cep = cep;
}

void Endereco::setLat(double lat) {
    this->lat = lat;
}

void Endereco::setLon(double lon) {
    this->lon = lon;
}

Endereco::~Endereco() {
}