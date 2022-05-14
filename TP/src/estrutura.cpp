// ---------------------------------------------------------------------
//  Arquivo	    : estrutura.cpp
//  Conteúdo	: implementacao da estrutura de dados do programa
//  Autor		: Junio veras de Jesus Lima
// ---------------------------------------------------------------------

#include "estrutura.h"
#include <vector>
#include <stack>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

bool comparacao(Pref a, Pref b)
// Descricao: comparacao utilizada para ordenacao estavel
// Entrada: Pref a, Pref b
// Saida: indica se o rank de a eh maior que o de b
{
    return (a.rank > b.rank);
}

StableMatchLagoa::StableMatchLagoa(int N, int M, int V, std::vector<std::vector<Pref>> preferencias, std::vector<std::string> mapa)
// Descricao: construtor da classe
// Entrada: N, M, V, preferencias e mapa
// Saida: os dados sao registrados na classe
{
    // associa as variaveis correspondentes
    this->N = N;
    this->M = M;
    this->V = V;
    this->preferencias = preferencias;
    this->mapa = mapa;

    // cria um vetor de bicicletas
    this->bicicletas = new Bicicleta[this->V];

    // localiza as bicicletas no mapa e atribui a localizacao dela a correspondente no vetor de bicicletas
    for(int i = 0; i < this->N; i++)
    {
        for(int j = 0; j < this->M; j++)
        {
            if(isdigit(this->mapa[i][j]))
            {
                int id = (int)this->mapa[i][j] - 48;
                this->bicicletas[id].i = i;
                this->bicicletas[id].j = j;
            }
        }
    }

    // cria um vetor de pessoas e um de inteiros para colocar o casamento estavel
    this->pessoas = new Pessoa[this->V];
    this->casamento_estavel = new int[this->V];
}

void StableMatchLagoa::computa_menores_distancias()
// Descricao: realiza uma bfs no mapa comecando pelas localizacoes das bicicletas para computar a distancia minima entre elas e as pessoas
// Entrada: void
// Saida: eh registrada a distancia das bicicletas as pessoas
{
    // realiza um bfs para cada bicicleta
    for(int b = 0; b < this->V; b++)
    {
        // cria um vetor de distancia e uma matriz auxiliar para identificar quando um elemento da matriz ja foi percorrido
        int *distancia = new int[this->V];
        int **cores = new int*[this->N];

        for(int i = 0; i < this->N; i++)
        {
            cores[i] = new int[this->M];
            for(int j = 0; j < this->M; j++)
            {
                cores[i][j] = 0;
            }
        }

        // criacao de uma pilha de execucao para realizacao da bfs com a localizacao inicial da bicicleta
        int camada = 0;
        std::stack<int> pilha;
 
        pilha.push(this->bicicletas[b].i);
        pilha.push(this->bicicletas[b].j);

        cores[this->bicicletas[b].i][this->bicicletas[b].j] = 1;

        // BFS
        while(!pilha.empty())
        {
            // cria uma pilha auxiliar para armazenar a proxima camada da bfs
            std::stack<int> prox_pilha;

            // enquanto a pilha nao estiver vazia pega as localizacoes e verifica a existencia de caminhos adjascentes
            while(!pilha.empty())
            {
                int posi, posj;
                posj = pilha.top();
                pilha.pop();
                posi = pilha.top();
                pilha.pop();

                // se a localizacao atual eh um caractere alfabetico, ou seja, uma pessoa, adicionamos a distancia da pessoa no vetor de distancia, enderecado pelo seu id
                if(isalpha(this->mapa[posi][posj]))
                {
                    distancia[(int)this->mapa[posi][posj] - 97] = camada;
                }

                // verifica todas as 4 possibilidades adjascentes a localizacao atual e adiciona na proxima pilha caso o caminho exista
                if(posi - 1 >= 0)
                {
                    if(this->mapa[posi-1][posj] != '-' && cores[posi-1][posj] != 1)
                    {
                        prox_pilha.push(posi-1);
                        prox_pilha.push(posj);
                        cores[posi-1][posj] = 1;
                    }
                }
                if(posi + 1 < this->N)
                {
                    if(this->mapa[posi+1][posj] != '-' && cores[posi+1][posj] != 1)
                    {
                        prox_pilha.push(posi+1);
                        prox_pilha.push(posj);
                        cores[posi+1][posj] = 1;
                    }
                }
                if(posj - 1 >= 0)
                {
                    if(this->mapa[posi][posj-1] != '-' && cores[posi][posj-1] != 1)
                    {
                        prox_pilha.push(posi);
                        prox_pilha.push(posj-1);
                        cores[posi][posj-1] = 1;
                    }
                }
                if(posj + 1 < this->M)
                {
                    if(this->mapa[posi][posj+1] != '-' && cores[posi][posj+1] != 1)
                    { 
                        prox_pilha.push(posi);
                        prox_pilha.push(posj+1);
                        cores[posi][posj+1] = 1;
                    }
                }
            }
            // atribuimos a pilha como a proxima pilha
            pilha = prox_pilha;
            camada++;
        }
        // atribuimos a lista de distancias criada a lista de distancias da bicicleta em questao
        this->bicicletas[b].distancia = distancia;
    }
}

void StableMatchLagoa::normaliza_preferencia()
// Descricao: altera a lista de preferencias das pessoas que esta por rank para mostrar a ordem de ids de preferencia das bicicletas
// Entrada: void
// Saida: ordena a lista de preferencias
{
    // realiza uma ordenacao estavel das preferencias de uma pessoa seguindo o criterio de comparacao estabelecido
    for(int i = 0; i < this->V; i++)
    {
        std::stable_sort(this->preferencias[i].begin(),this->preferencias[i].end(),comparacao);
    }

    // atribui a lista de preferencias de uma pessoa a lista da pessoa em questao
    for(int i = 0; i < this->V; i++)
    {
        this->pessoas[i].preferencias = preferencias[i];
        this->pessoas[i].id = i;
        this->pessoas[i].contador = 0;
    }
}

void StableMatchLagoa::calcula_casamento_estavel()
// Descricao: calcula o casamento estavel das pessoas e bicicletas
// Entrada: void
// Saida: o casamento estavel eh criado
{
    // cria uma fila para as pessoas sem par
    std::queue<Pessoa> fila;
    for(int i = 0; i < this->V; i++)
    {
        fila.push(this->pessoas[i]);
    }

    // algoritmo de casamento estavel
    while(!fila.empty())
    {
        // cria variaveis auxiliares para conter o id da pessoa analisada nessa rodada e a bicicleta que ele tentara alugar
        int id = fila.front().id;
        int bicicleta = this->pessoas[id].preferencias[this->pessoas[id].contador].id;

        // verifica se a bicicleta nao tem associacao
        if(this->bicicletas[bicicleta].pessoa_associada == -1)
        {
            casamento_estavel[id] = bicicleta;
            this->bicicletas[bicicleta].pessoa_associada = id;
        }
        // se ela tiver associada a alguem verifica se a bicicleta esta mais perto da pessoa do que desse alguem
        else if(this->bicicletas[bicicleta].distancia[this->bicicletas[bicicleta].pessoa_associada] > this->bicicletas[bicicleta].distancia[id])
        {
            casamento_estavel[id] = bicicleta;
            casamento_estavel[this->bicicletas[bicicleta].pessoa_associada] = -1;
            fila.push(this->pessoas[this->bicicletas[bicicleta].pessoa_associada]);
            this->bicicletas[bicicleta].pessoa_associada = id;
        }
        // se ela tiver associada a alguem verifica se a bicicleta esta na mesma distancia da pessoa e desse alguem, e se o id da pessoa eh menor que o desse alguem
        else if((this->bicicletas[bicicleta].distancia[this->bicicletas[bicicleta].pessoa_associada] == this->bicicletas[bicicleta].distancia[id]) && id < this->bicicletas[bicicleta].pessoa_associada)
        {
            casamento_estavel[id] = bicicleta;
            casamento_estavel[this->bicicletas[bicicleta].pessoa_associada] = -1;
            fila.push(this->pessoas[this->bicicletas[bicicleta].pessoa_associada]);
            this->bicicletas[bicicleta].pessoa_associada = id;
        }
        // se nenhuma condicao for atendida a pessoa foi rejeitada e sera colocada novamente na fila
        else
        {
            fila.push(this->pessoas[id]);
        }
        
        this->pessoas[id].contador++;
        fila.pop();
    }
}

void StableMatchLagoa::imprime()
// Descricao: imprime o casamento estavel
// Entrada: void
// Saida: impressao na tela
{
    for(int i = 0; i < this->V - 1; i++)
    {
        std::cout << ((char)(i+97)) << " " << this->casamento_estavel[i] << std::endl;
    }
    std::cout << ((char)(this->V - 1 +97)) << " " << this->casamento_estavel[this->V - 1];
}

// std::cout << std::endl;
// for(int i = 0; i < this->V; i++)
// {
//     for(int j = 0; j < this->V; j++)
//     {
//         std::cout << this->bicicletas[i].distancia[j] << " ";
//     }
//     std::cout << std::endl;
// }

// std::cout << std::endl;
// for(int i = 0; i < this->V; i++)
// {
//     for(int j = 0; j < this->V; j++)
//     {
//         std::cout << this->pessoas[i].preferencias[j].id << " ";
//     }
//     std::cout << std::endl;
// }

// std::cout << std::endl;