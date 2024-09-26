//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>

#define TAMANHO 10000
#define NUM_WORKERS 2

// Função para verificar se todos os elementos de um vetor são iguais
bool verificar_iguais(int *vetor, int tamanho)
{
	for (int i = 1; i < tamanho; i++)
	{
		if (vetor[i] != vetor[0]) 
			return false;   
	}
	return true;
}

int main(int argc, char *argv[])
{
	int segmento, *p, pid, status;

	// Criando a memória compartilhada
	segmento = shmget(IPC_PRIVATE, TAMANHO * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	if (segmento < 0)
	{
		perror("shmget");
		exit(1);
	}
	// Associando o ponteiro ao segmento de memória compartilhada
	// Associa a memória compartilhada ao processo
	p = (int *) shmat(segmento, 0, 0);
	if (p == (int *) -1)
	{
		perror("shmat");
		exit(1);
	}

	// Inicializando o vetor compartilhado com valor 5
	for (int i = 0; i < TAMANHO; i++) 
		p[i] = 5;
	// Criando os processos trabalhadores
	for (int i = 0; i < NUM_WORKERS; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{ // Processo filho (trabalhador)
			// Multiplicando cada elemento por 2 e somando 2
			for (int j = 0; j < TAMANHO; j++)
				p[j] = p[j] * 2 + 2;
			exit(0);
		}
	}

	// Esperando os processos filhos terminarem
	for (int i = 0; i < NUM_WORKERS; i++) 
		pid = wait(&status);
	// Imprimindo o vetor modificado
	printf("Vetor modificado:\n");
	for (int i = 0; i < TAMANHO; i++)
		printf("%d ", p[i]);
	printf("\n");
	// Verificando se todos os elementos do vetor são iguais
	bool iguais = verificar_iguais(p, TAMANHO);
	if (iguais) 
		printf("Todos os elementos do vetor são iguais.\n");
	else
		printf("Os elementos do vetor não são todos iguais.\n");

		// Libera a memória compartilhada do processo
		shmdt(p);
		// Libera a memória compartilhada
		shmctl(segmento, IPC_RMID, 0);

		return 0;
}
/*
Ex2: concorrência
Considere o vetor de 10.000 posições inicializado com o valor 5.
Crie 2 trabalhadores, ambos multiplicam por 2 e somam 2 em todas as posições do vetor.
Verifique automaticamente se todas as posições têm valores iguais e explique o que
ocorreu.
*/
