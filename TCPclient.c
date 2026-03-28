#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define SERVER_IP "127.0.0.1"

// High-resolution timer
double get_time() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / freq.QuadPart;
}

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in server;

    double send_time, recv_time;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Setup server address
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 1;
    }

    printf("Connected to server...\n");

    while (1) {
        send_time = get_time();

        // Send timestamp
        send(sock, (char*)&send_time, sizeof(send_time), 0);

        // Receive echo
        if (recv(sock, (char*)&recv_time, sizeof(recv_time), 0) <= 0) {
            printf("Server disconnected\n");
            break;
        }

        double now = get_time();
        double rtt = (now - send_time) * 1000; // convert to ms

        printf("Latency: %.3f ms\n", rtt);

        Sleep(1000); // 1 second delay
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}