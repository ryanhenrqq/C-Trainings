#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	char usageLn1[30] = "Como usar o compilador?:";
	char usageLn2[80] = "Requisitos -> ter o arquivo com a extensao .c no mesmo local do compilador";
	char usageLn3[80] = "Forma de uso - > Execute './compilador <nome do arquivo>'";
	char usageLn4[80] = "Não é necessario colocar a extensao '.c' no final do nome do arquivo!";
	char usageLn5[30] = "Tire bom proveito!";

	if (argc < 2){
		printf ("%s\n%s\n", usageLn1, usageLn2);
		printf ("%s\n%s\n", usageLn3, usageLn4);
		printf ("%s\n", usageLn5);
		return 1;
	}
	if (argc > 2){
		printf ("%s\n%s\n", usageLn1, usageLn2);
		printf ("%s\n%s\n", usageLn3, usageLn4);
		printf ("%s\n", usageLn5);
		return 1;
	}

	char cmd[300];

	snprintf (cmd, sizeof(cmd),"gcc %s.c -o %s", argv[1], argv[1]);
	//  snprintf = vai armazenar o output do que o comando vai gerar, dentro ca string cmd
	//  sizeof(cmd) bem auto explicativo, vai checar o tamanho do cmd (300)
	//  o comando do gcc sera rodado no terminal
	//  pra finalizar, os %s vai ser trocado pelo argumento passado pelo usuario, no caso o nome do arquivo

	printf ("COMPILADOR: Compilando %s.c\n", argv[1]);

	return system(cmd);
	// resumo desse codigo:
	// 	int argc -> vai pegar a quantidade de argumentos passada pela execuçao
	// 	char argv[] -> monta string com os argumentos passados e vira uma array aparentemente
	// 	verificaçao padrao do argc < 2 => se eu rodar "programa main", o argc vai ter o valor de 2 por serem 2 argumentos
	// 	cmd é so uma declaraçao, padrao.
	// 	snprintf vai montar a string usando dos paramentros que eu passei, e vai armazenar na string ja declarada cmd
	// 	printf é so um retorno basico pro usuario
	// 	return system(cmd) => o system() vai pegar o conteudo que tem no cmd e vai simplesmente executa-lo no terminal
	//
	// 	FORMA DE USO:
	// 		./compilar <nome do arquivo>
	// 		(não é necessario colocar a extensao .c no final)
	//
	// 	PARA COMPILAR ESSE CODIGO DO COMPILADOR:
	// 		gcc code-compilador.c -o compilar
	// 		(necessario ter gcc instalado e configurado.)
}
