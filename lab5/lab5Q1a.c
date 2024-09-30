/*Felippe Petrasso Fonseca Hübner 2110870
Breno Pinheiro Gallo de Sá 2110183*/
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#define NUM_THREADS 10
#define TAM_VET 10000

int vetor[TAM_VET];

void *roda(void *ini)
{
  int inicio = *((int *)ini);
  int fim = inicio + 1000;
  int soma = 0;
  for (int i = inicio; i < fim; i++)
  {
    vetor[i] *= 2;
    soma += vetor[i];
  }
  pthread_exit(NULL);
}

int main()
{
  pthread_t threads[NUM_THREADS];
  clock_t tempoI = clock();
  int t;
  int inicio[NUM_THREADS];
  int soma = 0;
  for (int i = 0; i < TAM_VET; i++)
  {
    vetor[i] = 5;
  }
  for (t = 0; t < NUM_THREADS; t++)
  {
    inicio[t] = t * 1000;
    pthread_create(&threads[t], NULL, roda, &inicio[t]);
  }
  for (t = 0; t < NUM_THREADS; t++)
  {
    pthread_join(threads[t], NULL);
  }
  for (int j = 0; j < TAM_VET; j++)
  {
    soma += vetor[j];
  }
  clock_t tempoF = clock();
  double tempoE = (double)(tempoF - tempoI) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %.16g\n", tempoE);
  printf("Soma: %d\n", soma);
  return 0;
}
