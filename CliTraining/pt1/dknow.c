#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(){
	int status = 0;
	int i=0;
	char name[][6] = {"Ryan", "Nome", "NOme"};

	for (i=0;i<3;i++){
		printf ("Nome: %s\n", name[i]);
	}

	openeer();

	return status;
}

static void openeer(){
	char *cmm;
	asprintf (&cmm, "xdg-open https://www.youtube.com/");
	system (cmm);
	free (cmm);
}
