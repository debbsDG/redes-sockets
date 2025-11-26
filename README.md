# Trabajo de redes - Sockets en C de Windows

Este repositorio contiene dos programas en C:

- `servidor.c`: abre un socket IPv4 en el puerto 8080, escucha conexiones y muestra en consola los mensajes que recibe.
- `cliente.c`: se conecta al servidor (127.0.0.1:8080) y envía los mensajes que el usuario escribe por teclado.

Ambos programas usan la librería Winsock de Windows (`winsock2.h`).

## Cómo compilar (MSYS2 UCRT64)

```bash
gcc servidor.c -o servidor.exe -lws2_32
gcc cliente.c -o cliente.exe -lws2_32
