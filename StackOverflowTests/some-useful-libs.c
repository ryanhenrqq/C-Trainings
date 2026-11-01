/*-----bibliotecas do tutorial no stack overflow---------*/
#include <sys/socket.h> // usado pra rede, criaçao de sockets e comunicação e etc. ESSENCIAL PRIORIZAR ESSE.
#include <sys/types.h> // definir dados de utilidade do SO, aqui usa size.
#include <netinet/in.h> // pra definiçao de protocolos de rede, tambem muito essencial priorizar esse
#include <netdb.h> // pra mexer com nomes de maquinas, dns, serviços de rede; permite descobrir ip de um dominio tb
#include <unistd.h> // funçoes relacionadas a unix - bem util aprender tambem
#include <errno.h> // permite consultar cod de erro gerado no SO -> definido por errno
#include <arpa/inet.h> // conversao de ip para binarios do sistema, de uso interno do SO - IMPORTANTE PRIORIZAR