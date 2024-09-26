// Felippe Petrasso Fonseca Hübner 2110870
// Breno Pinheiro Gallo de Sá 2110183

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int pid1, pid2;
void sig_handler(int sinal) {
  if (sinal == SIGALRM) {
    kill(pid1, SIGSTOP);
    kill(pid2, SIGCONT);
  } else if (sinal == SIGUSR1) {
    kill(pid2, SIGSTOP);
    kill(pid1, SIGCONT);
  }
}
int main() {
  void (*p)(int);
  p = signal(SIGALRM, sig_handler);
  p = signal(SIGUSR1, sig_handler);
  pid1 = fork();
  if (pid1 == 0) {
    char *args[] = {"./filho", NULL};
    execvp(args[0], args);
    perror("execvp");
    exit(1);
  }
  pid2 = fork();
  if (pid2 == 0) {
    char *args[] = {"./filho2", NULL};
    execvp(args[0], args);
    perror("execvp");
    exit(1);
  }
  alarm(15);
  sleep(15);
  kill(pid1, SIGKILL);
  kill(pid2, SIGKILL);
  return 0;
}
