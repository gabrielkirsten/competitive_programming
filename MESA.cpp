#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// Estrutura de dados para FILA ------------------------------------------------
struct noFila{
    short chave;
    noFila *proximo;
};

struct Fila{
    noFila *primeiro, *ultimo;
};

void inicializaFila(Fila *F){
    F -> primeiro = NULL;
    F -> ultimo = NULL;
}

bool filaVazia(Fila *F){
    return F -> primeiro == NULL;
}

void insereFila(Fila *F, short x){
    noFila *novo = new(noFila);
    novo -> proximo = NULL;
    novo -> chave = x;
    if(filaVazia(F))
        F -> primeiro = novo;
    else
        F -> ultimo -> proximo = novo;
    F -> ultimo = novo;
}

noFila* removeFila(Fila *F){
    noFila *aux = F -> primeiro;
    F -> primeiro = F -> primeiro -> proximo;
    return aux;
}

int main(void) {
  // indice para impressao do numero da intancia
	short indice = 0;

  bool sync_with_stdio (bool sync = true);

	// n = numero de convidados
	// m = mumero de relacoes de amizade
	// u,v = relacoes de amizade, u eh amigo de v e v eh amigo de u
  unsigned short m, n, u, v;

  bool ehBipartido;

	while(scanf("%hu%hu", &n, &m) != EOF) {

    ehBipartido = true;

		// cria matriz de adjacencia
		unsigned short matrizDeAdjacencia[n][n];

		// inicia tudo com zero
    memset(matrizDeAdjacencia, 0, sizeof(matrizDeAdjacencia[0][0]) * n * n);

    // recebe as relacoes de amizade
		for (unsigned short relacaoAmizade = 0; relacaoAmizade < m; relacaoAmizade++) {

			scanf("%hu%hu", &u, &v);

			// define as adjacencias na matriz
			matrizDeAdjacencia[u-1][v-1] = 1;
			matrizDeAdjacencia[v-1][u-1] = 1;

		}

		// realiza a busca em largura verificando se eh bipartido ------------------
		Fila *fila = new(Fila);
    inicializaFila(fila);

    // vetor de vertices marcados
    bool verticesMarcados[n];

    // vetor de vertices com grupos
    bool verticesPertencenteAoGrupo[n];

    // zera o vetor de vertices marcados e grupos
    memset(verticesMarcados, false, n);
    memset(verticesPertencenteAoGrupo, false, n);

    // variavel que armazena o no atual
    unsigned short noAtual;

    // poe na fila um vertice qualqueru de G e marque-o como alcançado
		insereFila(fila, 0);
		verticesMarcados[0] = true;
    verticesPertencenteAoGrupo[0] = true;

    // enquanto a fila for diferente de vazio faca
		while(!filaVazia(fila) && ehBipartido){

      // v ← elemento da frente da fila (retire v da fila)
			noAtual = removeFila(fila)->chave;

      // para toda aresta(v, w),tal que w ainda nao foi alcançado, marque w como
      // alcançado e poe w na fila
			for (unsigned short indiceMatriz = 0; indiceMatriz < n; indiceMatriz++) {

        if(matrizDeAdjacencia[noAtual][indiceMatriz] == 1){

          if(verticesMarcados[indiceMatriz] && verticesPertencenteAoGrupo[indiceMatriz] == verticesPertencenteAoGrupo[noAtual]){
            ehBipartido = false;
            break;
          }

  				if(!verticesMarcados[indiceMatriz]){
  					verticesMarcados[indiceMatriz] = true;
						insereFila(fila, indiceMatriz);
            verticesPertencenteAoGrupo[indiceMatriz] = !verticesPertencenteAoGrupo[noAtual];
  				}

        }

			}

		}

		printf("Instancia %d\n%s\n\n", ++indice, ehBipartido ? "sim" : "nao");

	}
	return 0;
}
