/*Felippe Petrasso Fonseca Hübner 2110870
Breno Pinheiro Gallo de Sá 2110183*/
#include <pthread.h>
#include <stdio.h>
#define TAM_VET 100000
#define NUM_THREADS 100

int vetor[TAM_VET];
void *roda(void *arg) {
  for (int i = 0; i < TAM_VET; i++) {
    vetor[i] = (vetor[i] * 2) + 2;
  }
  return NULL;
}

int main() {
  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < TAM_VET; i++) {
    vetor[i] = 5;
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, roda, NULL);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  for (int i = 1; i < TAM_VET; i++) {
    if (vetor[i] != ((vetor[i-1]*2) + 2)) {
      printf("Há diferenças entre as posições!\n");
      return 0;
    }
  }
  printf("Todas as posições têm o mesmo valor\n");
  return 0;
}
