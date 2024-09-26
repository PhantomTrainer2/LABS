//Felippe Petrasso Fonseca Hübner	2110870 
//Breno Pinheiro Gallo de Sá	2110183 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE *arq;
    char c;

    // Verificar se há argumentos suficientes
    if (argc < 2) {
        printf("Uso: %s arquivo1 arquivo2 ...\n", argv[0]);
        return 1;
    }

    // Iterar sobre todos os argumentos fornecidos
    for (int i = 1; i < argc; i++) {
        arq = fopen(argv[i], "r");
        if (arq == NULL) {
            printf("Erro ao abrir o arquivo %s\n", argv[i]);
            continue; // Continuar com o próximo arquivo
        }

        // Ler e imprimir o conteúdo do arquivo
        while ((c = fgetc(arq)) != EOF) {
            printf("%c", c);
        }
        fclose(arq);
    }

    return 0;
}

/*
Ex 3 – Programar funcionalidades do utilitário do unix “cat”
Ex: $meucat echo.c cat.c
(exibe os arquivos echo.c e cat.c) 
*/






