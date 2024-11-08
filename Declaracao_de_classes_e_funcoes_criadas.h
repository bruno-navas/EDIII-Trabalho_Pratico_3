#ifndef DECLARACAO_DE_CLASSES_E_FUNCOES_CRIADAS_H
#define DECLARACAO_DE_CLASSES_E_FUNCOES_CRIADAS_H

#include <iostream>
#include <set>
using namespace std;

class Cabecalho{
private:
    char status;                // Indicacao da consistencia do arq. de dados, se for 1 esta consistente e se for 0 nao     1 byte
    int topo;                   // Armazena o RRN de um registro logicamente removido ou -1 caso nao haja                   4 bytes
    int nroRegRem;              // Armazena o nro de registros logicamene marcados como removidos, inicia como 0            4 bytes
    int nroPagDisco;            // Armazena o nro de paginas de disco ocupadas pelo arq. de dados                           4 bytes
    int qttCompacta;

public:
    int proxRRN;                // Armazena o valor do prox RRN disponivel, inicia como 0 e muda caso necessario            4 bytes

    explicit Cabecalho(FILE* arquivo);
};

class Dado_bin {
private:
    char removido;              //  Indica se o registro esta logicamente removido                    1 byte
    int encadeamento;           //  Armazena o RRN do proximo registro logicamente removido           4 bytes
    float tamanho;              //  Tamanho do individuo                                              4 bytes
    char unidadeMedida;         //  Unidade de medida da velocidade do individuo                      1 byte
    int velocidade;             //  Velocidade do individuo                                           4 bytes
    int populacao;              //  Qtd de individuos da especie que viviam em determinado lugar      4 bytes
    char variavel[142];         //  Bytes variaveis                                                   142 bytes
    //  Nome-Especie-Habitat-Tipo-Dieta-Alimento
    //  Cada campo variavel eh separado por um delimitador '#'
    //  As strings nao devem terminar com \0
    //  Se sobrar espaço preencher com '$'
public:
    explicit Dado_bin(FILE* arquivo);
    friend class Especie;
    friend class Presa;
};

class Especie{
public:
    string nome;
    string especie;
    string habitat;
    string dieta;
    string tipo;
    int grau_entrada;
    int grau_saida;
    int grau;

    explicit Especie(FILE* arquivo);
    friend class Predador;
    friend class Grafo;
};

class Presa{
public:
    string nome_da_presa;
    int populacao_do_predador;

    explicit Presa(FILE* arquivo);
    bool operator<(const Presa& e) const {
        return this->nome_da_presa < e.nome_da_presa;
    }
    friend ostream& operator<<(ostream& os, const Presa& e);
};

class Predador {
private:
    Especie predador;
    set<Presa> presas;

public:
    explicit Predador(FILE* arquivo);
    void insere_presa(const Presa& p);

    bool operator<(const Predador& e) const {
        return this->predador.nome < e.predador.nome;
    }
    bool operator==(const Predador& outro) const {
        if (this->predador.nome == outro.predador.nome) {
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& out, const Predador& predador);
    friend class Grafo;
    void friend Exibe_predadores();
};

class Grafo {
private:
    int numero_de_vertices;
    set<Predador> vertices;

public:
    explicit Grafo(FILE* arquivo);

    void exibe_grafo() const;
    void friend Exibe_predadores();
};

void Cria_grafo_e_exibe();
Grafo Cria_grafo();
void Exibe_predadores();
void Identifica_ciclos();
void Analisa_conexoes();
void Relacao_presa_predador();

#endif //DECLARACAO_DE_CLASSES_E_FUNCOES_CRIADAS_H
