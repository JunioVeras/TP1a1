// ---------------------------------------------------------------------
//  Arquivo	    : main.cpp
//  Conteúdo	: funcao main do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include <iostream>
#include <string>
#include "estrutura.h"
#include <vector>

int main(int argc, char* argv[])
// Descricao: funcao main
// Entrada: void
// Saida: casamento estavel eh impresso na tela
{
    // criacao das variaveis que serao coletadas do usuario
    int V, N, M;
    std::vector<std::string> mapa;
    std::vector<std::vector<Pref>> preferencias;

    
    // recebimento da quantidade de pessoas e bicicletas, e da dimensao do mapa
    std::cin >> V;
    std::cin >> N;
    std::cin >> M;

    // recebimento do mapa
    for(int i = 0; i < N; i++)
    {
        std::string aux;
        std::cin >> aux;
        mapa.push_back(aux);
    }

    // recebimento da lista de preferencias, sendo que a preferencia sera armazenada contendo o id da bicicleta e seu rank
    for(int i = 0; i < V; i++)
    {
        std::vector<Pref> aux1;
        for(int j = 0; j < V; j++)
        {
            int aux2;
            std::cin >> aux2;
            Pref aux3;
            aux3.id = j;
            aux3.rank = aux2;
            aux1.push_back(aux3);
        }
        preferencias.push_back(aux1);
    }

    // cria uma instacia da classe para resolucao do problema e chama as funcoes
    StableMatchLagoa lagoa(N, M, V, preferencias, mapa);
    lagoa.computa_menores_distancias();
    lagoa.normaliza_preferencia();
    lagoa.calcula_casamento_estavel();
    lagoa.imprime();

    return 0;
}