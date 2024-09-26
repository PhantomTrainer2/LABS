//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>

#define SHM_KEY 7000
#define SHM_SIZE 1024

int main() {
    // Solicita a mensagem do usuário
    char mensagem[SHM_SIZE];
    printf("Digite a mensagem do dia: ");
    fgets(mensagem, SHM_SIZE, stdin);

    // Remove o caractere de nova linha do final da string, se existir
    mensagem[strcspn(mensagem, "\n")] = '\0';

    // Cria a memória compartilhada
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    if (shmid == -1) {
        perror("Erro ao criar a memória compartilhada");
        return 1;
    }

    // Faz o attach à memória compartilhada
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("Erro ao fazer o attach à memória compartilhada");
        return 1;
    }

    // Copia a mensagem para a memória compartilhada
    strcpy(shared_memory, mensagem);

    // Libera a memória (detach)
    if (shmdt(shared_memory) == -1) {
        perror("Erro ao liberar a memória compartilhada");
        return 1;
    }

    printf("Mensagem salva na memória compartilhada.\n");
    return 0;
}

/*
Ex3: Troca de mensagens via memória compartilhada 
Mensagem do Dia
Faça um programa que: Leia da entrada uma mensagem do dia. Crie uma memória compartilhada
com a chave 7000. Salve a mensagem na memória compartilhada.
Faça um outro programa que utilize o mesmo valor de chave da memória compartilhada e dê attach
na memória gerada pelo programa anterior. Em seguida este processo deve exibir a mensagem do
dia para o usuário e deve liberar a memória compartilhada.
Observação: Atenção com os flags*/