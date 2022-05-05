// ---------------------------------------------------------------------
//  Arquivo	    : estrutura.h
//  Conteúdo	: estrutura de dados do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#ifndef ESTRUTURA
#define ESTRUTURA

#include <vector>
#include <iostream>
#include <string>

struct Pref
{
    int id;
    int rank;
};

struct Bicicleta
{
    int i;
    int j;
    int *distancia;
    int pessoa_associada = -1;
};

struct Pessoa
{
    int id;
    std::vector<Pref> preferencias;
    int contador = 0;
};

struct elemento
{
    int id;
    int rank;
};

class StableMatchLagoa
{
    private:
        int N;
        int M;
        int V;
        std::vector<std::vector<Pref>> preferencias;
        std::vector<std::string> mapa;
        Bicicleta *bicicletas;
        Pessoa *pessoas;
        int *casamento_estavel;
          
    public:
        StableMatchLagoa(int N, int M, int V, std::vector<std::vector<Pref>> preferencias, std::vector<std::string> mapa);
        void computa_menores_distancias();
        void normaliza_preferencia();
        void calcula_casamento_estavel();
        void imprime();
};

#endif