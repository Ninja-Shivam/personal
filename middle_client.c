
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MIDDLE_PORT 9000
#define SERVER_PORT 9001
#define BUFFER_SIZE 1024

int main() {
    int mid_sock, client_sock;
    struct sockaddr_in mid_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    mid_sock = socket(AF_INET, SOCK_STREAM, 0);
    mid_addr.sin_family = AF_INET;
    mid_addr.sin_port = htons(MIDDLE_PORT);
    mid_addr.sin_addr.s_addr = INADDR_ANY;

    bind(mid_sock, (struct sockaddr *)&mid_addr, sizeof(mid_addr));
    listen(mid_sock, 5);
    printf("🌉 Middle Client Listening on port %d...\n", MIDDLE_PORT);

    while (1) {
        client_sock = accept(mid_sock, (struct sockaddr *)&client_addr, &addr_len);
        memset(buffer, 0, BUFFER_SIZE);
        read(client_sock, buffer, BUFFER_SIZE);

        int server_sock;
        struct sockaddr_in server_addr;
        char response[BUFFER_SIZE];

        server_sock = socket(AF_INET, SOCK_STREAM, 0);
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

        if (connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            perror("server connect");
            close(client_sock);
            continue;
        }

        send(server_sock, buffer, strlen(buffer), 0);
        memset(response, 0, BUFFER_SIZE);
        read(server_sock, response, BUFFER_SIZE);
        send(client_sock, response, strlen(response), 0);

        close(server_sock);
        close(client_sock);
    }

    close(mid_sock);
    return 0;
}
