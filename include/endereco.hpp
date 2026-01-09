#ifndef ENDERECO_H
#define ENDERECO_H

#include <string>

/**
 * TAD Endereço
 * 
 * Armazena os dados brutos de um endereço individual com todos seus atributos.
 * Uma função pertencente a esse TAD é o cálculo das coordenadas médias necessário
 * para construir o TAD Logradouro.
 */
class Endereco {
private:
    std::string idEnd;          // Identificador alfanumérico do endereço
    std::string idLog;          // Identificador numérico do logradouro
    std::string tipoLog;        // Tipo do logradouro (RUA, AVENIDA, etc)
    std::string log;            // Nome do logradouro
    std::string num;            // Número do endereço
    std::string bairro;         // Bairro do endereço
    std::string regiao;         // Região do endereço
    std::string cep;            // Código de endereçamento postal
    double lat;                 // Latitude
    double lon;                 // Longitude

public:
    /**
     * Construtor padrão
     */
    Endereco();

    /**
     * Construtor parametrizado
     */
    Endereco(const std::string& idEnd, const std::string& idLog, 
             const std::string& tipoLog, const std::string& log,
             const std::string& num, const std::string& bairro,
             const std::string& regiao, const std::string& cep,
             double lat, double lon);

    /**
     * Getters para acesso aos atributos
     */
    const std::string& getIdEnd() const;
    const std::string& getIdLog() const;
    const std::string& getTipoLog() const;
    const std::string& getLog() const;
    const std::string& getNum() const;
    const std::string& getBairro() const;
    const std::string& getRegiao() const;
    const std::string& getCep() const;
    double getLat() const;
    double getLon() const;

    /**
     * Setters para modificação dos atributos
     */
    void setIdEnd(const std::string& idEnd);
    void setIdLog(const std::string& idLog);
    void setTipoLog(const std::string& tipoLog);
    void setLog(const std::string& log);
    void setNum(const std::string& num);
    void setBairro(const std::string& bairro);
    void setRegiao(const std::string& regiao);
    void setCep(const std::string& cep);
    void setLat(double lat);
    void setLon(double lon);

    /**
     * Destrutor
     */
    ~Endereco();
};

#endif // ENDERECO_H