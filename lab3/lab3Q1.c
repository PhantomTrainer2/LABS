//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#define EVER ;;
void intHandler(int sinal);
void quitHandler(int sinal);
int main (void)
{
void (*p)(int);
p = signal(SIGINT, intHandler);
printf("Endereco do manipulador anterior %p\n", p);
p = signal(SIGQUIT, quitHandler);
printf("Endereco do manipulador anterior %p\n", p);
puts ("Ctrl-C desabilitado. Use Ctrl-\\ para terminar");
for(EVER);
}
void intHandler(int sinal){
  printf("Você pressionou Ctrl-c (%d)\n", sinal);
}
void quitHandler(int sinal)
{
printf("Terminando o processo...\n");
exit (0);
}

/*
1) Execute o programa “ctrl-c.c”. Digite Ctrl-C e Ctrl-\. Analise o resultado. Neste mesmo programa, 
remova os comandos signal( ) e repita o teste anterior observando os resultados. Explique o que 
ocorreu no relatório.
*/