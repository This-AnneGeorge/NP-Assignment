#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

DWORD WINAPI handle_client(LPVOID socket_desc) {
    SOCKET client_sock = *(SOCKET*)socket_desc;
    free(socket_desc);

    double timestamp;
    int total, bytes;

    while (1) {
        total = 0;

        while (total < sizeof(double)) {
            bytes = recv(client_sock, ((char*)&timestamp) + total, sizeof(double) - total, 0);
            if (bytes <= 0) {
                printf("Client disconnected\n");
                closesocket(client_sock);
                return 0;
            }
            total += bytes;
        }

        send(client_sock, (char*)&timestamp, sizeof(timestamp), 0);
    }
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_sock;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);

    WSAStartup(MAKEWORD(2,2), &wsa);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    int flag = 1;
    setsockopt(server_fd, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));

    int bufsize = 8192;
    setsockopt(server_fd, SOL_SOCKET, SO_RCVBUF, (char*)&bufsize, sizeof(bufsize));
    setsockopt(server_fd, SOL_SOCKET, SO_SNDBUF, (char*)&bufsize, sizeof(bufsize));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 5);

    printf("Server running on port %d...\n", PORT);

    while (1) {
        new_sock = accept(server_fd, (struct sockaddr*)&client, &c);

        SOCKET *pclient = malloc(sizeof(SOCKET));
        *pclient = new_sock;

        CreateThread(NULL, 0, handle_client, pclient, 0, NULL);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}