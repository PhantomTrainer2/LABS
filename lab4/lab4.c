// Felippe Petrasso Fonseca Hübner 2110870
// Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval T; // TAD para armazenar o tempo

int main(void)
{
  pid_t pid1, pid2, pid3; //ids dos processos
  int pid1Active = 0; // variáveis para identificar se o processo está ativo
  int pid2Active = 0;
  int pid3Active = 0;
	
  if ((pid1 = fork()) == 0)
    for (;;) {} // processo1 em loop infinito
  else if ((pid2 = fork()) == 0)
    for (;;) {} // processo2 em loop infinito
  else if ((pid3 = fork()) == 0) 
    for (;;) {} // processo3 em loop infinito 
	else
	{
    kill(pid1, SIGSTOP);
    kill(pid2, SIGSTOP);
    kill(pid3, SIGSTOP);
    for (;;)
		{
			gettimeofday(&T, NULL);
			int seg = T.tv_sec % 60; // tempo em segundos
		
			if (seg == 5) // início de p1
			{
				kill(pid1, SIGCONT);
				kill(pid3, SIGSTOP);
				pid3Active = 0; // necessário caso p3 inicie antes de seg = 5
				if (pid1Active == 0)
				{
					printf("processo 2 e processo 3 parados\n");
					printf("processo 1 de pid: %d em execução no segundo: %d\n", pid1, seg);
				}
				pid1Active = 1;
			}
			
			if (pid1Active == 1 && seg > 25) // fim do intevalo de p1
				pid1Active = 0;
			
			if (seg == 45) // início de p2
			{
				kill(pid2, SIGCONT);
				kill(pid3, SIGSTOP);
				pid3Active = 0;
				if (pid2Active == 0)
				{
					printf("processo 1 e processo 3 parados\n");
					printf("processo 2 de pid: %d em execução no segundo: %d\n", pid2, seg);
				}
				pid2Active = 1;
			}
			if (pid2Active == 1 && seg < 45) // fim do intervalo de p2
				pid2Active = 0;
			
			if (pid1Active == 0 && pid2Active == 0 && pid3Active == 0)
			{
				kill(pid1, SIGSTOP);
				kill(pid2, SIGSTOP);
				kill(pid3, SIGCONT);
				printf("processo 1 e processo 2 parados\n");
				printf("processo 3 de pid: %d em execução no segundo: %d\n", pid3, seg);
				pid3Active = 1;
			}
    }
  }

  return 0;
}

/*
LAB4 – Sinais e escalonamento de processos de tempo real
Na política de escalonamento REAL-TIME cada processo deve executar
periodicamente (uma vez por minuto), iniciando sua execução, em determinado
momento de tempo (I) e deve permanecer executando apenas durante um certo
período de tempo (D). Escreva em C um programa escalonador que executa um loop
infinito criando três processos filho, p1, p2 e p3, e que os escalona da
seguinte maneira (a cada minuto): • P1 inicia após 5 segundos (do início do
minuto cheio) e executa por 20 segundos • P2 inicia após 45 segundos (do minuto
cheio) e executa durante 15 segundos • P3 executa quando nem P1 e nem P2
executam Obs: Use sinais para iniciar/continuar e interromper a execução dos
processo (SIGCONT e SIGSTOP), use a chamada gettimeofday (&T,NULL) onde T é do
tipo struct timeval, cujo campo tv_sec contém, o número de segundos
transcorridos desde 1/1/1970
*/