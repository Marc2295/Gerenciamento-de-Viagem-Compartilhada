#ifndef LOGRADOURO_H
#define LOGRADOURO_H

#include <string>

/**
 * TAD Logradouro
 * 
 * Contém informações agregadas dos logradouros únicos, especialmente
 * as coordenadas médias (centro de gravidade) calculadas a partir de todos
 * os endereços pertencentes ao mesmo logradouro.
 * 
 * Mantém o mapeamento entre IdLog e nome do logradouro.
 */
class Logradouro {
private:
    std::string idLog;          // Identificador numérico do logradouro
    std::string nome;           // Nome do logradouro
    double latMedia;            // Latitude média dos endereços
    double lonMedia;            // Longitude média dos endereços
    int quantidade;             // Quantidade de endereços deste logradouro

public:
    /**
     * Construtor padrão
     */
    Logradouro();

    /**
     * Construtor parametrizado
     */
    Logradouro(const std::string& idLog, const std::string& nome,
               double latMedia, double lonMedia, int quantidade);

    /**
     * Getters para acesso aos atributos
     */
    const std::string& getIdLog() const;
    const std::string& getNome() const;
    double getLatMedia() const;
    double getLonMedia() const;
    int getQuantidade() const;

    /**
     * Setters para modificação dos atributos
     */
    void setIdLog(const std::string& idLog);
    void setNome(const std::string& nome);
    void setLatMedia(double latMedia);
    void setLonMedia(double lonMedia);
    void setQuantidade(int quantidade);

    /**
     * Atualiza a coordenada média ao processar um novo endereço
     * Utiliza cálculo incremental: media_nova = (media_antiga * n + valor) / (n + 1)
     * 
     * @param novaLat Latitude do novo endereço
     * @param novaLon Longitude do novo endereço
     */
    void atualizarMedias(double novaLat, double novaLon);

    /**
     * Destrutor
     */
    ~Logradouro();
};

#endif // LOGRADOURO_H