#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// Estrutura de dados para FILA ------------------------------------------------
struct noFila{
    unsigned short chave;
    unsigned short distancia;
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

void insereFila(Fila *F, unsigned short x, unsigned short distancia){
    noFila *novo = new(noFila);
    novo -> proximo = NULL;
    novo -> chave = x;
    novo -> distancia = distancia;
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

	// c = numero de cidades
	// e = mumero de estradas
	// l = cidade atual
  // p = maximo de pedagios
  // x = cidade 1
  // y = cidade 2
  unsigned short c, e, l, p, x, y;

	while(scanf("%hu%hu%hu%hu", &c, &e, &l, &p) != 0) {
    if(c == 0)
      return 0;

		// cria matriz de adjacencia
		unsigned short matrizDeAdjacencia[c][c];

		// inicia tudo com zero
    memset(matrizDeAdjacencia, 0, sizeof(matrizDeAdjacencia[0][0]) * c * c);

    // recebe os vertices
		for (unsigned short indiceVertice = 0; indiceVertice < e; indiceVertice++) {

			scanf("%hu%hu", &x, &y);

			// define as adjacencias na matriz
			matrizDeAdjacencia[x-1][y-1] = 1;
			matrizDeAdjacencia[y-1][x-1] = 1;

		}

    printf("Teste %d\n", ++indice);

		// realiza a busca em largura para encontrar as cidades --------------------
		Fila *fila = new(Fila);
    inicializaFila(fila);

    // vetor de vertices marcados
    bool verticesMarcados[c];

    // vetor de vertices alcancaveis
    bool verticesAlcancaveis[c];

    // zera os vetores
    memset(verticesMarcados, false, c);
    memset(verticesAlcancaveis, false, c);

    // variavel que armazena o no atual
    noFila *noAtual;

    // poe na fila um vertice qualqueru de G e marque-o como alcançado
		insereFila(fila, l-1, 0);
		verticesMarcados[l-1] = true;

    // enquanto a fila for diferente de vazio faca
		while(!filaVazia(fila)){

      // v ← elemento da frente da fila (retire v da fila)
			noAtual = removeFila(fila);

      // para toda aresta(v, w),tal que w ainda nao foi alcançado, marque w como
      // alcançado e poe w na fila
			for (unsigned short indiceMatriz = 0; indiceMatriz < c; indiceMatriz++) {

        if(matrizDeAdjacencia[noAtual -> chave][indiceMatriz] == 1){

  				if(!verticesMarcados[indiceMatriz]){
  					verticesMarcados[indiceMatriz] = true;

            if(noAtual -> distancia < p){
						  insereFila(fila, indiceMatriz, noAtual -> distancia + 1);
              verticesAlcancaveis[indiceMatriz] = true;
            }

  				}

        }

			}

		}
    for(unsigned short indiceVetorAlcancados = 0; indiceVetorAlcancados < c; indiceVetorAlcancados++)
      if(verticesAlcancaveis[indiceVetorAlcancados] == true) printf("%hu ", indiceVetorAlcancados+1);

    printf("\n\n");

	}
	return 0;
}
