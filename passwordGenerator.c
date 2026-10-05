#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	int alpLen = 0;
	int outer = 0; // necessario pra guardar o valor qdo usuario digita algo q nn é numero
	int outerBreak = 5; // limite de erros
	bool validLen = false; // destravar o loop quando o tamanho batee
	printf("-=-=-=-Gerador de Senhas-=-=-=-\n");
	while (validLen!=true){
		printf("Quantos caracteres deve ter a sua senha?: ");
		outer = scanf("%d", &alpLen); // se usuario digitar letra, o outer vai dedurar que deu erro e mandar um 0
		if (outer==0){
			if (outerBreak<=0){
				printf("ERRO: Numero de tentativas excedido, finalizando.\n");
				break;
			}
			outerBreak-=1;
			printf("ERRO: Digite um numero!\n");
			while (getchar()!='\n');
			continue;
		}
		if (alpLen<8){
			printf("Senha muito curta!\n");
		} else if (alpLen>24){
			printf("Senha muito longa!\n");
		} else {
			validLen = true;
		}
	}
	if (outerBreak<=0){ // finalizar programa - limite erros
		return 0;
	}
	char password[25] = ""; // senha gerada armazena aq
	for (int n=0;n<alpLen;n++){
		int r = rand()%62; // lista contém 62 items
		int s = alphabet[r]; 
		password[n] = s;
	}
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("SUCESSO! Copie a sua senha: %s\n", password); // mostrar senha pro usuario
	return 0;
}