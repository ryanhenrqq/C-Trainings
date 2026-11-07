#include <stdio.h> // padrao

#include <sys/socket.h>  // libs de internet
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>

#include <unistd.h>      // libs para uso no unix e definiçoes no c
#include <stdlib.h>	
#include <string.h>
#include <unistd.h>

// compilar e iniciar -> ./compilar listenport -r

//o que esse programa faz?:
//	ele vai criar um socket pela internet inteira (0.0.0.0) e abrir na porta 8123

//	apos abrir a porta, ele vai entrar num loop esperando contato direto, variando de acordo do ip,
//	tipo -> <ip local>:8123 
//	exemplo -> 192.168.0.50:8123

//	para fazer um contato direto a essa porta, voce pode usar o netcat
//	exemplo (usando o ip ficticio 192.168.0.50):

//		$ nc 192.168.0.50 8123
//		olá, mundo

//	-> comportamento: apos o usuario digitar olá mundo e pressionar enter, o servidor vai receber essa mensagem e mostrar na tela

//	Para quem for baixar e testar, é importante dizer que isso foi feito no linux fedora, que ja vem com muitas ferramentas pré
//	instaladas. No caso do windows, mac ou até outra distro linux pode exigir alguma instalação separada.

int main(){
	// atributos para o servidor
	int serv, client; // socket de ambos sao definidos como integers
	char buffer[1024]; // armazena apenas a mensagem, usa lá embaixo
	struct sockaddr_in address; //vai montar todos os paramentros do socket pra rede usando esse struct sockaddr_in
	struct sockaddr_in addr_client; // pra uso la embaixo em detectar ip da pessoa conectada
	serv = socket(AF_INET, SOCK_STREAM, 0); // criaçao do socket
	address.sin_family = AF_INET;           // esse AF_INET é uma constante padrao de uso no socket
	address.sin_port = htons (8123);        // define porta, usando htons
	address.sin_addr.s_addr = htonl (INADDR_ANY); // aqui define o endereço, e esse ANY define como 0.0.0.0, o que libera pra qualquer um na 
						      // rede | obs posterior: parece que qui nao precisa usar htonl, podendo so colocar INADDR_ANY
	socklen_t client_len = sizeof(addr_client);   

	//atributos para descobrir ip local - baseado no arquivo local em /IPGetter/ipget.c
	char hostbuffer[256];          		// aqui é armazenado nome do host, tipo 'fedora' ou 'windows-PC'
	char *ipbuffer;                		// declaraçao de onde vai ser armazenado o ip
	struct hostent* host_entry;   		// declaraçao do hostentry, com estrutura do hostent
	int hostname;                  		// aqui é so pra armazenar o resultado do gethostbyname, se for 0 deu certo
	hostname = gethostname (hostbuffer, sizeof(hostbuffer));                      // chama o gethostname e grava no host buffer
	host_entry = gethostbyname (hostbuffer);                                      // fiquei confuso aqui nao minto
	ipbuffer = inet_ntoa (*((struct in_addr*) host_entry -> h_addr_list[0]));     // aqui nem se fala

	if (bind (serv, (struct sockaddr *)&address, sizeof (address)) < 0) {         // aqui ele vai bindar o socket do serv com todos os paramentros no struct do address
									              // e ja vai lidar sozinho se der erro de bind (geralmente se a porta tiver ocupada)
		printf ("Bind Error!\n");
		close (serv);
		return 1;
	}

	if (listen (serv, 5) < 0){                   // aqui ele vai rodar o comando pra começar a escutar no serv, e ja vai lidar com erro
						     // se esse comando retornar menos que 0 (o que significa que deu erro).
		printf ("Listen Error!\n");
		close (serv);
		return 1;
	}

	printf ("Ta aberto no servidor %s:8123\n", ipbuffer);  // pequeno debug pra indicar que deu tudo certo, e ja mostra o ip local pra facilitar

	while (1){
		client = accept (serv, (struct sockaddr *)&addr_client, &client_len); // o cliente vai ser definido aqui

		if (client < 0) {
			// bug
			// 	dps que eu coloquei a mensagem automatica de conexao nova com o ip do dispositivo, ele ta sempre caindo em loop aqui
			// 	por conta do fechamento do socket ali embaixo dps da resposta. nao sei ainda como vou fazer pra manter o
			// 	ip e a troca de mensagem sem quebrar na 2 mensagem de volta.
			printf ("Erro de comunicação com o cliente!");
			return 1;
		} else { 							    // --> aqui o servidor ira pegar o endereço ip do cliente e logar <--
			char ip[INET_ADDRSTRLEN];                                   // declarar o ip do cliente, e ja pega automatico o tamanho necessario pra armazena-lo
			inet_ntop(AF_INET, &addr_client.sin_addr, ip, sizeof(ip));  // aqui parece que chama essa funçao do socket, pega o addr client definido no accept ali encima
										    // , vai atras do parametro sin_addr (ja que é o struct) e grava ele na string ip.
			printf ("\nNova conexão: %s\n", ip);                        // log no terminal indicando que alguem esta conectado.
		}

   		char welcome[12] = "Mensagem: ";                                    // definir a palavra inicial que vai aparecer no terminal da pessoa conectada
		send (client, welcome, strlen(welcome), 0);                         // envia essa mensagem definida pro cliente
		ssize_t bytes = recv (client, buffer, sizeof(buffer) -1, 0); 	    // aqui ele vai começar a escutar o que o cliente digitar no terminal dele, e ja vai definir
										    // o tamanho da mensagem recebida no integer bytes, assim caindo na funçao abaixo.

		if (bytes > 0){
			buffer[bytes] = '\0';                                       // vai colocar o \0 no final da mensagem
			printf ("\nRecebido: %s\n", buffer);                        // vai logar a mensagem recebida do cliente pro servidor
			send (client, "Respondendo, aguarde...\n", 26, 0);          // vai dar um 'callback' pro cliente aguardar enquanto servidor digita uma mensagem

			// resposta do servidor (experimental)
			char res[30];                                               // define o conteudo digitado
			char resback[50];					    // define a mensagem que sera enviada
			printf ("Digite uma resposta: ");			    // loga pro servidor que ele pode digitar algo
			fgets (res, sizeof(res), stdin);			    // pega o que for digitado
			snprintf (resback, sizeof(resback), "Resposta: %s\n", res); // monta a mensagem que sera enviada
			send (client, resback, strlen(resback), 0);		    // manda pro cliente a mensagem montada
		}
	}

	close (serv);

	return 0;
}

// comentario aleatorio: sem brincadeira, esse foi o melhor codigo que 
// montei em c kkkk fiquei 50x mais interessado dps de fazer esse comunicador de rede
