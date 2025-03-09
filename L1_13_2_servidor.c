#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h> // Para inet_pton

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sock, ret;
    struct sockaddr_in serv_adr;
    char buff[1024];
    int opcion;
    float temperatura;

    // Crear socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error("Error creando socket");

    // Configurar la dirección del servidor
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_port = htons(9050);  // Puerto del servidor

    // Convertir la IP del servidor
    if (inet_pton(AF_INET, "192.168.56.102", &serv_adr.sin_addr) <= 0)
        error("Dirección IP no válida");

    // Conectar al servidor
    if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) < 0)
        error("Error al conectar con el servidor");

    // Solicitar información al usuario
    printf("Introduce la temperatura: ");
    scanf("%f", &temperatura);

    printf("Elige la conversión:\n1. Celsius a Fahrenheit\n2. Fahrenheit a Celsius\n");
    scanf("%d", &opcion);

    // Formatear el mensaje y enviarlo al servidor
    snprintf(buff, sizeof(buff), "%d, %.2f", opcion, temperatura);
    write(sock, buff, strlen(buff));

    // Recibir respuesta del servidor
    ret = read(sock, buff, sizeof(buff) - 1);
    if (ret > 0) {
        buff[ret] = '\0';  // Agregar terminador de cadena
        printf("Respuesta del servidor: %s\n", buff);
    }

    // Cerrar el socket
    close(sock);
    return 0;
}
