//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define EVER ;;

void sig_handler(int signum){
  printf("Erro de ponto flutuante\nValor do sinal: %d\n", signum);
  exit(1);
}

int main(void){
  int n1, n2;
  void (*p)(int);
  p = signal(SIGFPE, sig_handler);
  printf("Digite o primeiro numero: ");
  scanf("%d", &n1);
  printf("Digite o segundo numero: ");
  scanf("%d", &n2);
  int soma = n1 + n2;
  int sub = n1 - n2;
  int mult = n1 * n2;
  int div = n1/n2;
  printf("Soma: %d\n", soma);
  printf("Subtração: %d\n", sub);
  printf("Multiplicação: %d\n", mult);
  printf("Divisão: %d\n", div);
}
