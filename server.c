
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 9001
#define BUFFER_SIZE 1024

void process_request(char *buffer) {
    for (int i = 0; buffer[i]; i++)
        buffer[i] = toupper(buffer[i]);
}

int main() {
    int serv_sock, client_sock;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_sock, 5);
    printf("🖥️ Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        client_sock = accept(serv_sock, (struct sockaddr *)&client_addr, &addr_len);
        memset(buffer, 0, BUFFER_SIZE);
        read(client_sock, buffer, BUFFER_SIZE);

        process_request(buffer);
        send(client_sock, buffer, strlen(buffer), 0);

        close(client_sock);
    }

    close(serv_sock);
    return 0;
}
