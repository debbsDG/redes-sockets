#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_fd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    int server_addr_len = sizeof(server_addr);
    int bytes;

    // 1. Inicializar Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Error al inicializar Winsock.\n");
        return 1;
    }

    // 2. Crear socket
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        printf("Error al crear el socket.\n");
        WSACleanup();
        return 1;
    }

    // 3. Configurar dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 4. Enlazar (bind)
    if (bind(server_fd, (struct sockaddr*)&server_addr, server_addr_len) == SOCKET_ERROR) {
        printf("Error en bind.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // 5. Escuchar conexiones
    if (listen(server_fd, 1) == SOCKET_ERROR) {
        printf("Error en listen.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Servidor esperando conexiones en el puerto 8080...\n");

    // 6. Aceptar cliente
    client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == INVALID_SOCKET) {
        printf("Error en accept.\n");
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Cliente conectado.\n");

    // 7. Recibir mensajes
    while (1) {
        bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        buffer[bytes] = '\0';
        printf("Mensaje recibido: %s\n", buffer);
    }

    // 8. Cerrar sockets y limpiar
    closesocket(client_fd);
    closesocket(server_fd);
    WSACleanup();

    return 0;
}
