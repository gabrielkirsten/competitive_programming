
//  _______  _______  __    _  _______  _______  _______  _______  _______
// |       ||       ||  |  | ||       ||       ||       ||  _    ||  _    |
// |    _  ||   _   ||   |_| ||_     _||    ___||  _____|| | |   || | |   |
// |   |_| ||  | |  ||       |  |   |  |   |___ | |_____ | | |   || |_|   |
// |    ___||  |_|  ||  _    |  |   |  |    ___||_____  || |_|   ||___    |
// |   |    |       || | |   |  |   |  |   |___  _____| ||       |    |   |
// |___|    |_______||_|  |__|  |___|  |_______||_______||_______|    |___|
//  code by: Gabriel Kirsten | SPOJ PROBLEM  --> http://br.spoj.com/problems/PONTES09/

#include <iostream>
#include <string.h>
#include <stdio.h>

#define INFINITO 0XFFFF

using namespace std;

int main(void) {
  bool sync_with_stdio (bool sync = true);

	// n = numero de pilares
	// m = mumero de pontes
	// s,t = extremidades da pontes
  // b = buraco
  unsigned short m, n, s, t, b;

  scanf("%hu%hu", &n, &m);

  unsigned short size = n+2;

	// cria matriz de adjacencia
	unsigned short matrizDeAdjacencia[size][size];

	// inicia tudo com zero
  memset(matrizDeAdjacencia, INFINITO, size * size * sizeof(matrizDeAdjacencia[0][0]));

  // recebe as ligacoes da ponte
	for (unsigned short relacaoAmizade = 0; relacaoAmizade < m; relacaoAmizade++) {

		scanf("%hu%hu%hu", &s, &t, &b);

		// define as adjacencias na matriz
		matrizDeAdjacencia[s][t] = matrizDeAdjacencia[t][s] = b;

	}

	// realiza o algoritmo de dijkstra -----------------------------------------

  // vetor de distancias
  unsigned short distancia[size];
  memset(distancia, INFINITO, sizeof(distancia[0]) * size);

  distancia[0] = 0;

  // vetor de vertices visitados
  bool verticesVisitados[size];
  memset(verticesVisitados, false, sizeof(verticesVisitados[0]) * size);


  while (true){
    int i, n = -1;

    for (i = 0; i < size; i++)
      if (!verticesVisitados[i] && (n == -1 || distancia[i] < distancia[n]))
        n = i;

    if (n == -1)
      break;

    verticesVisitados[n] = true;

    for (i = 0; i < size; i++)
      if (distancia[i] > distancia[n] + matrizDeAdjacencia[n][i])
        distancia[i] = distancia[n] + matrizDeAdjacencia[n][i];

  }

	printf("%hu\n", distancia[size-1]);

	return 0;
}
