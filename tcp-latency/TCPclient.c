#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

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

    char server_ip[20];
    int interval;

    printf("Enter Server IP: ");
    scanf("%s", server_ip);

    printf("Enter interval (ms): ");
    scanf("%d", &interval);

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    int flag = 1;
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char*)&flag, sizeof(flag));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(server_ip);

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed\n");
        return 1;
    }

    printf("Connected...\n");

    double send_time, recv_time;
    int total, bytes;

    while (1) {
        send_time = get_time();

        send(sock, (char*)&send_time, sizeof(send_time), 0);

        total = 0;

        while (total < sizeof(double)) {
            bytes = recv(sock, ((char*)&recv_time) + total, sizeof(double) - total, 0);
            if (bytes <= 0) {
                printf("Disconnected\n");
                closesocket(sock);
                WSACleanup();
                return 0;
            }
            total += bytes;
        }

        double now = get_time();
        double rtt = (now - send_time) * 1000;

        printf("Latency: %.3f ms\n", rtt);

        Sleep(interval);
    }
}