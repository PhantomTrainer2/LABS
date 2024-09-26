//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define TAMANHO 10000
#define NUM_WORKERS 10
#define CHUNK_SIZE (TAMANHO / NUM_WORKERS)

// Função para calcular a soma das parcelas de um vetor
int calcular_soma(int *vetor, int inicio, int fim) {
		int soma = 0;
		for (int i = inicio; i < fim; i++) {
				soma += vetor[i];
		}
		return soma;
}

int main(int argc, char *argv[]) {
		int segmento, *p, pid, status;

		// Criando a memória compartilhada
		segmento = shmget(IPC_PRIVATE, TAMANHO * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
		if (segmento < 0) {
				perror("shmget");
				exit(1);
		}

		// Associando o ponteiro ao segmento de memória compartilhada
		// Associa a memória compartilhada ao processo
		p = (int *) shmat(segmento, 0, 0);
		if (p == (int *) -1) {
				perror("shmat");
				exit(1);
		}

		// Inicializando o vetor compartilhado com valor 5
		for (int i = 0; i < TAMANHO; i++) {
				p[i] = 5;
		}

		// Criando os processos trabalhadores
		for (int i = 0; i < NUM_WORKERS; i++) {
				pid = fork();
				if (pid < 0) {
						perror("fork");
						exit(1);
				} else if (pid == 0) { // Processo filho (trabalhador)
						int inicio = i * CHUNK_SIZE;
						int fim = inicio + CHUNK_SIZE;

						// Multiplicando a parcela do vetor por 2
						for (int j = inicio; j < fim; j++) {
								p[j] *= 2;
						}

						// Calculando a soma da parcela do vetor
						int soma_parcela = calcular_soma(p, inicio, fim);
						printf("Processo %d: Soma da parcela = %d\n", getpid(), soma_parcela);
						exit(0);
				}
		}

		// Processo pai (coordenador)
		int soma_total = 0;

		// Esperando os processos filhos terminarem e acumulando as somas
		for (int i = 0; i < NUM_WORKERS; i++) {
				pid = wait(&status);
				// soma_total += calcular_soma(p, i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE);
		}

		// Somando as somas parciais dos trabalhadores
		for (int i = 0; i < NUM_WORKERS; i++) {
				soma_total += calcular_soma(p, i * CHUNK_SIZE, (i + 1) * CHUNK_SIZE);
		}

		printf("Soma total das parcelas = %d\n", soma_total);

		// Libera a memória compartilhada do processo
		shmdt(p);
		// Libera a memória compartilhada
		shmctl(segmento, IPC_RMID, 0);

		return 0;
}

/*
LAB2 – INF1316 – Sistemas Operacionais Exercício 
com memória compartilhada
Ex1: Paralelismo
Criar um vetor a de 10.000 posições inicializado com valor 5.
Criar 10 processos trabalhadores que utilizam áreas diferentes do vetor para multiplicar a sua
parcela do vetor por 2 e somar as posições do vetor retornando o resultado para um processo
coordenador que irá apresentar a soma de todas as parcelas recebidas dos trabalhadores.
Obs: O 1º trabalhador irá atuar nas primeiras 1.000 posições, o 2º trabalhador nas 1.000 posições
seguintes e assim sucessivamente.
*/