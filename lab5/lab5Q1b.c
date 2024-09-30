/*Felippe Petrasso Fonseca Hübner 2110870
Breno Pinheiro Gallo de Sá 2110183*/
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#define NUM_THREADS 100
#define TAM_VET 100000

int vetor[TAM_VET];

void *roda(void *ini) // função que os trabalhadores executam, multiplicando por 2 as poisições em que trabalham
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
  clock_t tempoI = clock(); // tempo inicial
  int t; //representa a thread da posição threads[t]
  int inicio[NUM_THREADS];
  int soma = 0;
  for (int i = 0; i < TAM_VET; i++) // loop responsável por iniciar as posições do vetor com 5
  {
    vetor[i] = 5;
  }
  for (t = 0; t < NUM_THREADS; t++) // loop responsável por criar a thread na parcela em que trabalhará
  {
    inicio[t] = t * 1000;
    pthread_create(&threads[t], NULL, roda, &inicio[t]); //função responsável por criar a thread e indicar a o método executado por ela
  }
  for (t = 0; t < NUM_THREADS; t++) //loop responsável por juntar as threads
  {
    pthread_join(threads[t], NULL);
  }
  for (int j = 0; j < TAM_VET; j++) //loop responsável por fazer a soma total do vetor
  {
    soma += vetor[j];
  }
  clock_t tempoF = clock(); //Tempo final
  double tempoE = (double)(tempoF - tempoI) / CLOCKS_PER_SEC; // tempo de execução do programa
  printf("Tempo de execução: %.16g\n", tempoE);
  printf("Soma: %d\n", soma);
  return 0;
}

// Repita o código do Ex1 usando agora com 100 trabalhadores e com um vetor de 100.000 posições.
// Indique o que ocorreu