//Felippe Petrasso Fonseca Hübner	2110870 
//Breno Pinheiro Gallo de Sá	2110183 
#include <stdio.h>

int main(int argc, char** argv)
{
	for(int i = 1; i<argc; i++)
		printf("%s ", argv[i]);

	printf("\n");
	return 0;
}


/*
Ex2 – Programar funcionalidades dos utilitários do unix - “echo”
Ex: $meuecho bom dia (exibe os parâmetros de meuecho)
bom dia
*/