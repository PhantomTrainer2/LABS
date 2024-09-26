//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define EVER ;;

void intHandler(int sinal){
  printf("SIGKILL INTERROMPIDO\n");
}
void quitHandler(int sinal){
puts ("Terminando o processo...\n");
exit (0);
}
int main (void){
pid_t pid = getpid();
printf("Pid = %d\n", pid);
void (*p)(int);
p = signal(SIGKILL, intHandler);
printf("Aguardando sinal\n");
p = signal(SIGQUIT, quitHandler);
for(EVER);
}

/*
2) Tente fazer um programa para interceptar o sinal SIGKILL. Você conseguiu? Explique.
*/