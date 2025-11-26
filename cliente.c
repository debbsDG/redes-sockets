#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
    WSADATA wsa;
    SOCKET client_fd;
    struct sockaddr_in server_addr;
    char mensaje[1024];

    // 1. Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error al inicializar Winsock.\n");
        return 1;
    }

    // 2. Crear socket
    client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_fd == INVALID_SOCKET) {
        printf("Error al crear el socket.\n");
        WSACleanup();
        return 1;
    }

    // 3. Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    // 127.0.0.1 = localhost (tu propia compu)
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 4. Conectarse al servidor
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Error al conectar con el servidor.\n");
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }

    printf("Conectado al servidor.\n");

    // 5. Enviar mensajes en un ciclo
    while (1) {
        printf("Escribí un mensaje (o 'salir' para terminar): ");
        if (fgets(mensaje, sizeof(mensaje), stdin) == NULL) {
            break;
        }

        // Si el usuario escribe "salir\n" salimos
        if (strncmp(mensaje, "salir", 5) == 0) {
            break;
        }

        send(client_fd, mensaje, strlen(mensaje), 0);
    }

    // 6. Cerrar socket y limpiar
    closesocket(client_fd);
    WSACleanup();

    return 0;
}
