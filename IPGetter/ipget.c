#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// compilar -> ./compilar ipget

int main() {
	// codigo base pego do studymite.com
	
	char hostbuffer[256];
	char *ipbuffer;
	struct hostent* host_entry;
	int hostname;

	hostname = gethostname (hostbuffer, sizeof(hostbuffer));
	printf ("%s\n", hostbuffer);

	host_entry = gethostbyname (hostbuffer);

	ipbuffer = inet_ntoa (*((struct in_addr*) host_entry -> h_addr_list[0]));
	printf ("IP: %s\n", ipbuffer);

	return 0;
}
