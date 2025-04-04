#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

extern Blockchain *blockchain;

void *handle_connection(void *arg) {
    int client_sock = *(int *)arg;
    Block incoming_block;
    recv(client_sock, &incoming_block, sizeof(Block), 0);
    close(client_sock);

    // Basic verification
    if (is_valid_hash(incoming_block.hash)) {
        add_block(blockchain, incoming_block);
        printf("Received block #%d from peer\n", incoming_block.index);
    }

    return NULL;
}

void start_server(int port) {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_sock, 5);

    printf("Server started on port %d\n", port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_len);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_connection, &client_sock);
        pthread_detach(tid);
    }
}

void send_block(Block *block, const char *ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &server_addr.sin_addr);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    send(sock, block, sizeof(Block), 0);
    close(sock);
}
