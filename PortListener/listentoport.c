#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// compilar e iniciar -> ./compilar listenport -r

//o que esse programa faz?:
//	ele vai criar um socket pela internet inteira (0.0.0.0) e abrir na porta 8123
//
//	apos abrir a porta, ele vai entrar num loop esperando contato direto, variando de acordo do ip,
//	tipo -> <ip local>:8123 
//	exemplo -> 192.168.0.50:8123
//
//	para fazer um contato direto a essa porta, voce pode usar o netcat
//	exemplo (usando o ip ficticio 192.168.0.50):
//
//		$ nc 192.168.0.50 8123
//		olá, mundo
//
//	-> comportamento: apos o usuario digitar olá mundo e pressionar enter, o servidor vai receber essa mensagem e mostrar na tela

int main(){
	// atributos para o servidor
	int serv, client;
	char buffer[1024];
	struct sockaddr_in address;
	serv = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_port = htons (8123);
	address.sin_addr.s_addr = htonl (INADDR_ANY);

	//atributos para descobrir ip local - baseado no arquivo local em /IPGetter/ipget.c
	char hostbuffer[256];
	char *ipbuffer;
	struct hostent* host_entry;
	int hostname;
	hostname = gethostname (hostbuffer, sizeof(hostbuffer));
	host_entry = gethostbyname (hostbuffer);
	ipbuffer = inet_ntoa (*((struct in_addr*) host_entry -> h_addr_list[0]));

	if (bind (serv, (struct sockaddr *)&address, sizeof (address)) < 0) {
		printf ("Bind Error!\n");
		close (serv);
		return 1;
	}

	if (listen (serv, 5) < 0){
		printf ("Listen Error!\n");
		close (serv);
		return 1;
	}

	printf ("Listening on %s:8123\n", ipbuffer);

	while (1){
		client = accept (serv, NULL, NULL);

		if (client < 0) {
			printf ("Communication error!");
			continue;
		}

		ssize_t bytes = recv (client, buffer, sizeof(buffer) -1, 0);

		if (bytes > 0){
			buffer[bytes] = '\0';
			printf ("received: %s\n", buffer);

			// resposta do servidor (experimental)
			char res[30];
			printf ("Digite uma resposta: ");
			fgets (res, sizeof(res), stdin);
			send (client, res, strlen(res), 0);
		}

		close (client);
	}

	close (serv);

	return 0;
}

// comentario aleatorio: sem brincadeira, esse foi o melhor codigo que 
// montei em c kkkk fiquei 50x mais interessado dps de fazer esse comunicador de rede
