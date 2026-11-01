#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h> // adc -> funções essenciais para manipulaçao da memoria

/*-----bibliotecas do tutorial no stack overflow---------*/
#include <sys/types.h> // definir dados de utilidade do SO, aqui usa size.
#include <unistd.h> // funçoes relacionadas a unix - bem util aprender tambem
/*-----=========================================---------*/

// compila -> bash comp downloader

int main(){
	// manipulaçao de arquivo externo :D
	FILE *arquivo;
	FILE *arquivoLer;

        int status = 0;
        int timer = 5;
        char qtdLinha[10];

        arquivoLer = fopen ("data.txt", "r");
        while (fgets (qtdLinha, 10, arquivoLer)) {
        	// aqui ta acontecendo uma quebra de linha na palavra passou (pas \n sou)
        	printf ("%s\n", qtdLinha);
        }

        fclose (arquivoLer);

        arquivo = fopen ("data.txt", "w");

        while (1) {
        	printf ("timer: %i\n", timer);
        	fprintf(arquivo, "Timer passou %i\n", timer);
        	sleep (1);
        	timer-=1;
        	if (timer<=0) break;
        }

        fclose (arquivo);

        return status;
};