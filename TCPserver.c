#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

// Thread function to handle each client
DWORD WINAPI handle_client(LPVOID socket_desc) {
    SOCKET client_sock = *(SOCKET*)socket_desc;
    free(socket_desc);

    double timestamp;

    while (1) {
        int recv_size = recv(client_sock, (char*)&timestamp, sizeof(timestamp), 0);
        if (recv_size <= 0) {
            printf("Client disconnected\n");
            break;
        }

        // Echo back timestamp
        send(client_sock, (char*)&timestamp, sizeof(timestamp), 0);
    }

    closesocket(client_sock);
    return 0;
}

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_sock;
    struct sockaddr_in server, client;
    int c = sizeof(struct sockaddr_in);

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Setup server
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        return 1;
    }

    // Listen
    listen(server_fd, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept multiple clients
    while (1) {
        new_sock = accept(server_fd, (struct sockaddr*)&client, &c);
        if (new_sock == INVALID_SOCKET) {
            printf("Accept failed\n");
            continue;
        }

        printf("Client connected\n");

        SOCKET *pclient = malloc(sizeof(SOCKET));
        *pclient = new_sock;

        // Create thread for each client
        CreateThread(NULL, 0, handle_client, pclient, 0, NULL);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}