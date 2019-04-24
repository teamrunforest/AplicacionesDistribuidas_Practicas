
// Cliente.
// Fuente de apoyo: https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Sockets.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>


#define SERV_ADDR 1234 // (cambio) #define SERV_ADDR 1981

//(IPPORT_RESERVED+1)
#define DATA "##--##--##----***----##--##--##"

int main(int argc, char **argv) // (cambio) void main(int argc, char** argv)
{
	int sock;
	struct sockaddr_in server;
	struct hostent *hp; // (cambio) struct hostent *hp, *gethostbyname();
	
	if(argc < 2) 
	{
		printf("Uso: %s nombre_host\n",argv[0]);
		return -1; // (cambio) exit(1);
	}

	// (cambio) este código estaba fuera del main -->
	sock= socket (PF_INET, SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("No se ha podido conseguir un socket :(");
		return -1; // (cambio) exit(1);
	}

	server.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	if(hp==0)
	{
		fprintf(stderr, "%s: No conozco a esa compu\n",argv[1]);
		return -2; // (cambio) exit(1);
	}

	memcpy((char *)&server.sin_addr, (char *)hp->h_addr,hp->h_length);
	server.sin_port=htons(SERV_ADDR);
	if (connect(sock, (struct sockaddr *)&server,sizeof (server))<0)
	{
		perror("Conexion no aceptada!!!!");
		return 0; // (cambio) exit(1);
	}
	if (write(sock, DATA,strlen(DATA)+1)<0)
	{
		perror("No he podido escribir el mensaje");
		close(sock);
		return -3; // (cambio) exit(0);
	}

	// (cambio) este código estaba fuera del main <--
	return 0; // (cambio) linea adicional.
}