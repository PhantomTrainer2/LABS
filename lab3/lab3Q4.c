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
  double n1, n2;
  void (*p)(int);
  p = signal(SIGFPE, sig_handler);
  printf("Digite o primeiro numero: ");
  scanf("%lf", &n1);
  printf("Digite o segundo numero: ");
  scanf("%lf", &n2);
  double soma = n1 + n2;
  double sub = n1 - n2;
  double mult = n1 * n2;
  double div = n1/n2;
  printf("Soma: %.16g\n", soma);
  printf("Subtração: %.16g\n", sub);
  printf("Multiplicação: %.16g\n", mult);
  printf("Divisão: %.16g\n", div);
}

/*
4) Faça um programa que leia 2 números reais e imprima o resultado das 4 operações básicas sobre 
estes 2 números. Verifique o que acontece se o 2º. número da entrada for 0 (zero). Capture o sinal 
de erro de floating point (SIGFPE) e repita a experiência anterior. Faça o mesmo agora lendo e 
realizando as operações com inteiros. Explique o que ocorreu nas duas situações.
*/