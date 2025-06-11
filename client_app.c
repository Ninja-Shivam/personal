
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MIDDLE_PORT 9000
#define BUFFER_SIZE 1024

void client_app_send(const char *buffer) {
    int sock;
    struct sockaddr_in addr;
    char response[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(MIDDLE_PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        close(sock);
        return;
    }

    send(sock, buffer, strlen(buffer), 0);

    memset(response, 0, BUFFER_SIZE);
    read(sock, response, BUFFER_SIZE);

    printf("✅ Server Response: %s\n", response);
    close(sock);
}
