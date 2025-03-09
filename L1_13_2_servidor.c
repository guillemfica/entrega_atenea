#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	//INICIALITZACION
	//Obrim el socket
	if((sock_listen = socket(AD_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	//Fem el bind al port
	memset(&serv.adr, 0, sizeof(Serv_adr));//inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	//asocia el socket a cualquiera de las IP de la maquina.
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr = htonl(INADDR_ANY);
	//escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if(bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf("Error al bind");
	
	if(listen(sock_listen, 3)< 0)
		printf("Error en el listen");
	
	//Solo atendemos 5 peticiones
	int i;
	for (i = 0; i<5;i++)
	{		
		printf("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		//Ahora recibimos su nombre, que dejamos en el buff
		ret = read(sock_conn, peticion, sizeof(peticion));
		printf("Recibido\n");
		
		//Tenemos que a￱adirle la marca de fin de string
		//Para que no escriba lo que hay despues en el buffer
		peticion[ret] = '\0';
		
		//Escribimos el nombre en la consola
		printf("Peticion: %s\n", peticion);
		
		//vamos a ver que quieren
		char *p = strtok(peticion, "/");
		int codigo = atoi(p);
		p = strtok(NULL, "/");
		float temperature;
		strcpy(temperature, p);
		float resultado;
		printf("Codigo: %d, Nombre: %f\n", codigo, temperature);
		
		if(codigo == 1) //piden la conversion de C -> F
			resultado = (temperature -32)*5/9;
			sprinf(respuesta, "%f,", resultado);
		if(codigo == 2) //piden la conversion de F -> C
			resultado = (temperature +32)*9/5;
			sprinf(respuesta, "%f,", resultado);
		// Y lo enviamos
		write(sock_conn, respuesta, strlen(respuesta));
		//se acabo el servicio para este cliente
		close(sock_conn);
	}
}
