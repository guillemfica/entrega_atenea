#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int sock, n, i;
	struct hostent *host;
	struct sockaddr_in serv_adr;
	 //inicialitzacions
	char buff[1024];
	
	//preparem l'adre￧a del servidor
	memset(&serv_adr, 0, sizeof(serv_adr));//inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	memcpy(&serv_adr.sin_addr, host -> h_addr, host -> h_length);
	serv_adr.sin_port = htons(9050);
	
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Creant socket");
	if(inet_pton(AF_INET,"192.168.56.102", &serv_adr.sin_addr)<=0)
		error("Direccion IP no válida");
	if(connect(sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr))<0)
		error("connect");
	
	//Servei
	write(1, "Enter Message for Server <Enter to Stop>: ", 42)
	ret=read(1, buff, sizeof(buff));
	buff[○ret]='\0';
	write(sock, buff, strlen(buff));
	
	close(sock);
	
	exit(0);
}