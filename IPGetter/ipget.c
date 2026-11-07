#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// compilar -> ./compilar ipget

int main(int argc, char *argv[]) {
	// codigo base pego do studymite.com
	
	char hostbuffer[256];
	char *ipbuffer;
	struct hostent* host_entry;
	int hostname;
	bool showHostname = false;

	if (argc == 2){
		if (strcmp(argv[1], "-hostname")==0){
			showHostname = true;
		} else {
			printf ("Argumento invalido! Uso: ipget [-hostname: mostrar o nome do host]\n");
			return 1;
		}
	}
	if (argc > 2){
		printf ("ERRO: Esperado apenas 0 ou 1 argumentos, mas foi recebido %i!\n", argc-1);
		return 1;
	}

	hostname = gethostname (hostbuffer, sizeof(hostbuffer));
	if (showHostname==true){
		printf ("Nome do host: %s\n", hostbuffer);
	}

	host_entry = gethostbyname (hostbuffer);

	ipbuffer = inet_ntoa (*((struct in_addr*) host_entry -> h_addr_list[0]));
	printf ("IP Local: %s\n", ipbuffer);

	return 0;
}
