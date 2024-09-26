/*Felippe Petrasso Fonseca Hübner 2110870
Breno Pinheiro Gallo de Sá 2110183*/
#include <stdio.h>
#include <time.h>
#define TAM_VET 10000

int vetor[TAM_VET];

int main() {
  int soma = 0;
  clock_t tempoI = clock();
  for (int i = 0; i < TAM_VET; i++) {
    vetor[i] = 5;
  }
  for (int i = 0; i < TAM_VET; i++) {
    vetor[i] *= 2;
    soma += vetor[i];
  }
  clock_t tempoF = clock();
  double tempoE = (double)(tempoF - tempoI) / CLOCKS_PER_SEC;
  printf("Tempo de execução: %.16g\n", tempoE);
  printf("Soma: %d\n", soma);
    return 0;
}
