/*Felippe Petrasso Fonseca Hübner 2110870
Breno Pinheiro Gallo de Sá 2110183*/
#include <pthread.h>
#include <stdio.h>
#define TAM_VET 100000
#define NUM_THREADS 100

int vetor[TAM_VET];
void *roda(void *arg) // função que os trabalhadores executam, multiplicando por 2 as e semar por 2 as poisções em que trabalham
{
  for (int i = 0; i < TAM_VET; i++)
  {
    vetor[i] = (vetor[i] * 2) + 2;
  }
  return NULL;
}

int main()
{
  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < TAM_VET; i++) // loop responsável por iniciar as posições do vetor com 5
  {
    vetor[i] = 5;
  }
  for (int i = 0; i < NUM_THREADS; i++)  // loop responsável por criar a thread
  {
    pthread_create(&threads[i], NULL, roda, NULL); //função responsável por criar a thread e indicar a o método executado por ela
  }
  for (int i = 0; i < NUM_THREADS; i++) //loop responsável por juntar as threads
  {
    pthread_join(threads[i], NULL); 
  }
  for (int i = 1; i < TAM_VET; i++)  //loop responsável por percorrer o vetor e verificar se houve diferença nas posições
  {
    if (vetor[i] != ((vetor[i - 1] * 2) + 2))
    {
      printf("Há diferenças entre as posições!\n");
      return 0;
    }
  }
  printf("Todas as posições têm o mesmo valor\n");
  return 0;
}

// Repita o código do Ex2 usando agora 10 ou 100 trabalhadores e um vetor de 100.000 posições.
// Indique o que ocorreu.