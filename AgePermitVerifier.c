#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
	// declaração (e ja o set up) das listas variaveis
	char api[][10] = {"pessoa1", "Test2", "yo3", "teste4", "segurança"};
	bool permit[] = {false, true, true, false, true};
	int age[] = {17, 29, 21, 16, 35};

	// constantes do tamanho das listas
	const int j = sizeof(api)/sizeof(api[0]); // <----- usado no loop abaixo
	const int k = sizeof(permit)/sizeof(permit[0]);
	const int l = sizeof(age)/sizeof(age[0]);
	printf("tamanho nomes: %d\ntamanho booleans: %d\ntamanho booleans: %d\n\n", j, k, l); // debug no terminal

	for (int n=0;n<j;n++) {
		char graphPermit[10] = "";
		if (permit[n]==0){
			strcpy(graphPermit, "Negado");
		} else {
			strcpy(graphPermit, "Permitido");
		}
		printf("%s - %d anos - %s\n", api[n], age[n], graphPermit); // sai do tipo "pessoa1 - Negado"
	} // proxima ideia: manipulaçao direta apos pessoa informar idade, em controle de ingrassos.
	return 0;
}