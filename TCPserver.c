#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET server_fd, client_sock;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);

    double timestamp;

    // Initialize Winsock
    WSAStartup(MAKEWORD(2,2), &wsa);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    // Listen
    listen(server_fd, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept client
    client_sock = accept(server_fd, (struct sockaddr *)&client, &c);
    printf("Client connected\n");

    while (1) {
        int recv_size = recv(client_sock, (char*)&timestamp, sizeof(timestamp), 0);
        if (recv_size <= 0) break;

        // Echo back
        send(client_sock, (char*)&timestamp, sizeof(timestamp), 0);
    }

    closesocket(client_sock);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}