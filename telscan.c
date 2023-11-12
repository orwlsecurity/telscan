#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int
telnet_check(const char* dest_ip, uint16_t port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket() failed");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, dest_ip, &server_addr.sin_addr) <= 0) {
        perror("inet_pton() failed");
        close(sock);
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect() failed");
        close(sock);
        return 1;
    }

    printf("Telnet connection to %s:%d is successful.\n", dest_ip, port);

    close(sock);
    return 0;
}

int
main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Usage: %s <destination_ip> <port>\n", argv[0]);
        return 1;
    }

    const char* dest_ip = argv[1];
    uint16_t port = atoi(argv[2]);

    return telnet_check(dest_ip, port);
}
