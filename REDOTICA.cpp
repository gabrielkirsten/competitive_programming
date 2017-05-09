#include <bits/stdc++.h>
#include <stdio.h>

using namespace std;

// número máximo de elementos
#define MAX 100

// vetor de alcançados
bool verticeAlcancado[MAX];

// lista de adjacencia
vector<pair<unsigned short, unsigned short> > listaDeAdjacencia[MAX];

// fila de prioridades para o Kruskal
priority_queue<pair<unsigned short, pair<unsigned short, unsigned short> > > filaDePrioridade;

// Aresta Atual
pair<unsigned short, unsigned short> arestaAtual;

// N -> corresponde ao numero de tabas
// M -> corresponde ao numero de redes possiveis
// X,Y -> corresponde a um vertice do grafo
// Z -> corresponde ao custo de uma aresta
unsigned short N, M, X, Y, Z, indiceDoTeste = 0, indice;

// função para inserir elemento na lista de alcançados
void insert(unsigned short indiceDoVertice) {
    if(verticeAlcancado[indiceDoVertice])
        return;
        
    // marca o vértice como alcançado
    verticeAlcancado[indiceDoVertice] = true;

    // para cada elemento na lista de adjacencia, coloca na lista de prioridades
    for (indice = 0; indice < listaDeAdjacencia[indiceDoVertice].size(); indice++) {
        // se o primeiro elemento já foi alcançado, ignora o processamento
        if (verticeAlcancado[listaDeAdjacencia[indiceDoVertice][indice].first]) 
            continue;
            
        // coloca o par de vértices na lista de prioridades
        filaDePrioridade.push(make_pair(-listaDeAdjacencia[indiceDoVertice][indice].second, make_pair(indiceDoVertice, listaDeAdjacencia[indiceDoVertice][indice].first)));
    }
}

int main () {
    
    bool sync_with_stdio (bool sync = true);

    while (scanf("%hu %hu", &N, &M) != EOF && N && M) {

        printf("Teste %hu\n", ++indiceDoTeste);

        // inicia os elementos
        for (indice = 0; indice < N; indice++) {
            verticeAlcancado[indice] = 0;
            listaDeAdjacencia[indice].clear();
        }
        
        // remove os elementos da lista de prioridades
        while (!filaDePrioridade.empty()){
            filaDePrioridade.pop();
        } 

        // recebe as adjacencias
        while(M--){
            scanf("%hu %hu %hu", &X, &Y, &Z);
            
            // insere as adjacencias na lista
            listaDeAdjacencia[X-1].push_back(make_pair(Y-1, Z));
            listaDeAdjacencia[Y-1].push_back(make_pair(X-1, Z));
        }


        // inicia com o primeiro indice
        insert(0);

        // KRUSKAL 
        // enquanto a fila de prioridades houver itens
        while (!filaDePrioridade.empty()) {
            // obtem a melhor aresta 
            arestaAtual = filaDePrioridade.top().second;
            
            // remove o melhor elemento
            filaDePrioridade.pop();
            
            // se a aresta liga dois elementos já alcançados
            if (verticeAlcancado[arestaAtual.first] && verticeAlcancado[arestaAtual.second]){
                // ignora o processamento, como os dois elementos foram alcançados
                // o vértice não é útil.
                continue;
            } 

            printf("%hu %hu\n", min(arestaAtual.first, arestaAtual.second)+1, max(arestaAtual.first, arestaAtual.second)+1);
            
            // se o vértice já foi alcançado, coloca o outro elemento na lista de 
            // alcançados
            if (verticeAlcancado[arestaAtual.first]) 
                insert(arestaAtual.second);
            else 
                insert(arestaAtual.first);
        }
        
        printf("\n");
    }
}
