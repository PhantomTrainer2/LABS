//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h> 
#include <sys/wait.h>

#define EVER ;;

void childhandler(int signo);
int delay;

int main (int argc, char *argv[])
{
	pid_t pid;
	signal(SIGCHLD, childhandler);
	if ((pid = fork()) < 0)
	{
		fprintf(stderr, "Erro ao criar filho\n");
		exit(-1);
	}
	if (pid == 0) /* child */
		execvp(argv[2], argv);
		//sleep(3);
	//for(EVER); /* ou sleep(3); ou, no próximo exercício, execvp(argv[2], argv);*/
	else /* parent */
	{
		sscanf(argv[1], "%d", &delay); /* read delay from command line */
		sleep(delay);
		printf("Program %s exceeded limit of %d seconds!\n", argv[2], delay);
		kill(pid, SIGKILL);
	}
	return 0;
}

void childhandler(int signo) /* Executed if child dies before parent */
{
	int status;
	pid_t pid = wait(&status);
	printf("Child %d terminated within %d seconds com estado %d.\n", pid, delay, status);
	exit(0);
}

/*
3) Execute e explique o funcionamento de filhocidio.c, com as 4 opções:
a- for(EVER) //filho em loop eterno 
b- sleep(3) //filho dorme 3 segundos -
c- execvp(sleep5) // filho executa o programa sleep5
d- execvp(sleep15) // filho executa o programa sleep15
Explique o que ocorreu em cada programa
*/