// teste gabriel

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <mpi.h>
#include <time.h>

#define V 25

// Grafo representado por uma Matriz de Adjac�ncia ponderada(com arestas valoradas).
int grafo[V][V] = {
    {0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {10, 0, 8, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 0, 0, 9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 5, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 9, 0, 0, 8, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 10, 0, 8, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 12, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 12, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 6, 0, 8, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int distancias[V];
int visitados[V];

int encontrarVerticeMaisProximo()
{
  int distanciaMinima = INT_MAX;
  int verticeMaisProximo;

  for (int i = 0; i < V; i++)
  {
    if (!visitados[i] && distancias[i] <= distanciaMinima)
    {
      distanciaMinima = distancias[i];
      verticeMaisProximo = i;
    }
  }

  return verticeMaisProximo;
}

void dijkstra(int verticeInicial)
{
  // Inicia as distancias como valores suficientemente grandes e visitados como falso
  for (int i = 0; i < V; i++)
  {
    distancias[i] = INT_MAX;
    visitados[i] = 0;
  }

  distancias[verticeInicial] = 0; // Inicia o Vertice da distancia inicial como 0;
  for (int i = 0; i < V - 1; i++)
  {
    int verticeAtual = encontrarVerticeMaisProximo();
    visitados[verticeAtual] = 1;

    for (int j = 0; j < V; j++)
    {
      if (!visitados[j] && grafo[verticeAtual][j] != 0 && distancias[verticeAtual] != INT_MAX && distancias[verticeAtual] + grafo[verticeAtual][j] < distancias[j])
      {
        distancias[j] = distancias[verticeAtual] + grafo[verticeAtual][j];
      }
    }
  }
}

int main(int argc, char *argv[])
{
  MPI_Init(&argc, &argv);
  double tempoExecucao = 0.0;

  int verticeInicial = 0;
  clock_t inicio = clock();

  dijkstra(verticeInicial);

  printf("Vertice\tDistancia Minima\n");
  for (int i = 0; i < V; i++)
  {
    printf("%d\t%d\n", i, distancias[i]);
  }

  clock_t fim = clock();

  tempoExecucao += (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo de execucao: %f segundos\n", tempoExecucao);

  MPI_Finalize();
  return 0;
}