#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]){
	char usageLn1[30] = "Como usar o compilador?:";
	char usageLn2[80] = "Requisitos -> ter o arquivo com a extensao .c no mesmo local do compilador";
	char usageLn3[90] = "Forma de uso - > Execute './compilador <nome do arquivo> [-r: executar apos compilar]'";
	char usageLn4[80] = "Não é necessario colocar a extensao '.c' no final do nome do arquivo!";
	char usageLn5[30] = "Tire bom proveito!";
	bool minimalMode = false;
	bool runningMode = false;

	if (argc < 2){
		printf ("%s\n%s\n", usageLn1, usageLn2);
		printf ("%s\n%s\n", usageLn3, usageLn4);
		printf ("%s\n", usageLn5);
		return 1;
	}
	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			if (strcmp(argv[i], "-r")==0){
				runningMode = true;
			}
			if (strcmp(argv[i], "-m")==0){
				minimalMode = true;
			}
		}
	} 
	if (minimalMode==false&&runningMode==false) {
		if (argc > 2){
			printf ("ERRO: O programa exige apenas 1 ou 2 argumento, mas foram  detectados %i!\n\n%s\n%s\n", argc - 1, usageLn1, usageLn2);
			printf ("%s\n%s\n", usageLn3, usageLn4);
			printf ("%s\n", usageLn5);
			return 1;
		}
	}
	
	// logica de checagem da existencia do arquivo
	char filechk[200];
	snprintf (filechk, sizeof(filechk), "%s.c", argv[1]);
	if (access(filechk, F_OK)!=0){
		printf ("ERRO: O arquivo especificado não existe!\n\n%s\n%s\n", usageLn1, usageLn2);
		printf ("%s\n%s\n", usageLn3, usageLn4);
		printf ("%s\n", usageLn5);
		return 1;

	} else {
		if (minimalMode==false){
			printf ("COMPILADOR: O arquivo %s foi encontrado, iniciando.\n", filechk);
		}
	}
	// o que essa logica faz?
	// 	char filechk -> declara a string do nome do arquivo
	// 	snprintf -> pega o nome passado no argumento e adiciona a extensao .c no final
	// 	if access(filechk, F_OK) -> ele vai tentar acessar o arquivo salvo em filechk
	// 		se ele conseguir, vai marcar q o arquivo ta ok e vai retornar 0, ignorando o if e continuando
	// 		se ele nao conseguir, ele vai retornar algum outro numero pra indicar que nao teve sucesso, caindo na logica do if e barrando bugs
	
	// treino pra limpar memoria
	usageLn1[0] = '\0';
	usageLn2[0] = '\0';
	usageLn3[0] = '\0';
	usageLn4[0] = '\0';
	usageLn5[0] = '\0';

	char cmd[300];

	snprintf (cmd, sizeof(cmd),"gcc %s.c -o %s", argv[1], argv[1]);
	//  snprintf = vai armazenar o output do que o comando vai gerar, dentro ca string cmd
	//  sizeof(cmd) bem auto explicativo, vai checar o tamanho do cmd (300)
	//  o comando do gcc sera rodado no terminal
	//  pra finalizar, os %s vai ser trocado pelo argumento passado pelo usuario, no caso o nome do arquivo

	if (minimalMode==false){
		printf ("COMPILADOR: Compilando %s\n", filechk);
	}
	
	filechk[0] = '\0';

	int op = system(cmd);

	if (op!=0){
		printf ("COMPILADOR: Houve um erro ao compilar, com codigo %i!", op);
		return op;
	} else {
		if (minimalMode==false){
			printf ("COMPILADOR: O arquivo foi compilado com sucesso com codigo %i!\n", op);
		}
		
	}

	if (runningMode==false){
		return op;
	}

	char runner[100];
	snprintf (runner, sizeof(runner), "./%s", argv[1]);

	op = system(runner);

	if (op!=0){
		printf ("COMPILADOR: Houve um erro ao executar, codigo %i!\n", op);
		return op;
	} else {
		if(minimalMode==false){
			printf ("COMPILADOR: Arquivo executado com sucesso com codigo %i!\n", op);
		}
		return op;
	}
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
