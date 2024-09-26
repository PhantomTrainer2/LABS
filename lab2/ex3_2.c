//Felippe Petrasso Fonseca Hübner 2110870
//Breno Pinheiro Gallo de Sá 2110183

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/shm.h>

#define SHM_KEY 7000
#define SHM_SIZE 1024

int main() {
    // Localiza a memória compartilhada
    int shmid = shmget(SHM_KEY, SHM_SIZE, IPC_EXCL | S_IRUSR | S_IWUSR);
    if (shmid == -1) {
        perror("Erro ao localizar a memória compartilhada");
        return 1;
    }

    // Faz o attach à memória compartilhada
    char *shared_memory = (char *)shmat(shmid, NULL, 0);
    if (shared_memory == (char *)(-1)) {
        perror("Erro ao fazer o attach à memória compartilhada");
        return 1;
    }

    // Exibe a mensagem armazenada
    printf("Mensagem do dia: %s\n", shared_memory);

    // Libera a memória (detach)
    if (shmdt(shared_memory) == -1) {
        perror("Erro ao liberar a memória compartilhada");
        return 1;
    }

    // Remove a memória compartilhada
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Erro ao remover a memória compartilhada");
        return 1;
    }

    printf("Memória compartilhada liberada.\n");
    return 0;
}

