#include <stdio.h>

int main(){
	int number = 0;
	printf("Escreva o numero pra saber se é par ou não: ");
	scanf("%d", &number);
	int par = number % 2;
	if (par == 0){
		printf("É par!\n");
	} else {
		printf("Não é par!\n");
	}
	return 0;
}