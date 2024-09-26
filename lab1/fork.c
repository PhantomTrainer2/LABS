//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

  int vetor[10] = {0};

  int pid, status;
	pid = fork();
  if (pid != 0) 
	{
    for (int i = 0; i < 10; i++) {
      vetor[i] += 1;
    }
    waitpid(-1, &status, 0);
    for (int i = 0; i < 10; i++) {
      printf("%d %d\n",i, vetor[i]);
    }
    exit(0);
  } else {
    for (int i = 0; i < 10; i++)
      vetor[i] -= 1;
    exit(0);
  }
	return 0;
}


/*
Ex1– Elaborar programa para criar 2 processos hierárquicos (pai e filho) onde é declarado um vetor 
de 10 posições inicializado com 0. Após o fork() o processo pai faz um loop de somando 1 às 
posições do vetor, exibe o vetor e espera o filho terminar. O processo filho subtrai 1 de todas as 
posições do vetor, exibe o vetor e termina. Explique os resultados obtidos (por quê os valores de pai 
e filho são diferentes? Os valores estão consistentes com o esperado?) 
Bibliotecas: stdio.h, unistd.h, sys/wait.h, stdlib.h 
Função que retorna o pid do processo: int getpid() 



O resultado decorre do fato de o processo filho estar em uma área de memória diferente do processo pai, ou seja, o processo é duplicado, fazendo com que sejam executados de forma independente. 
*/