//Felippe Petrasso Fonseca Hübner	2110870 
//Breno Pinheiro Gallo de Sá	2110183 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 10

void exec_command(const char *command)
{
  char *args[MAX_ARGS];
  int arg_count = 0;
  char arg[MAX_COMMAND_LENGTH];
  int i = 0;

  while (command[i] != '\0' && arg_count < MAX_ARGS - 1)
  {
    int j = 0;
    while (command[i] != ' ' && command[i] != '\0')
    {
      arg[j++] = command[i++];
    }
    arg[j] = '\0';
    args[arg_count] = malloc(strlen(arg) + 1); // Alocar memória para o argumento
    strcpy(args[arg_count], arg); // Copiar o argumento para a lista de argumentos
    arg_count++;

    while (command[i] == ' ')
    {
      i++;
    }
  }

    args[arg_count] = NULL;

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Este é o processo filho
        execvp(args[0], args);
        perror("Execvp failed");
        exit(1);
    } else {
        // Este é o processo pai
        int status;
        waitpid(pid, &status, 0);
    }

    // Liberar a memória alocada para os argumentos
    for (int i = 0; i < arg_count; i++) {
        free(args[i]);
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        input[strlen(input) - 1] = '\0';

        exec_command(input);
    }

return 0;
}

/*
Ex4 – Programar uma shell e executar os seus programas meuecho, meucat e os utilitários do 
Unix echo, cat, ls
Ex: >minhashell
$meuecho alo alo Realengo aquele abraço
alo alo Realengo aquele abraço
*/