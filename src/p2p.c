#include "p2p.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_PEERS 10\

int peer_count = 0;
struct sockaddr_in peer_addresses[MAX_PEERS];
void add_peer(struct sockaddr_in peer_addr) {
    if (peer_count < MAX_PEERS) {
        peer_addresses[peer_count++] = peer_addr;
        printf("Peer added: %s:%d\n", inet_ntoa(peer_addr.sin_addr), ntohs(peer_addr.sin_port));
    } else {
        printf("Max peer limit reached. Cannot add more peers.\n");
    }
}

void start_p2p_server(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        perror("failed");exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;server_addr.sin_port = htons(PORT);server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
        perror("failed");close(server_socket);exit(EXIT_FAILURE);
    }

    listen(server_socket,5);

    printf("p2p listening on port %d\n",PORT);
    while(1){
        int client_socket = accept(server_socket,NULL,NULL);
        if(client_socket<0){
            perror("failed");continue;
        }
        handle_incoming_connection(client_socket);
    }
}

void handle_incoming_connection(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer));
    if (bytes_read > 0) {
        printf("Received: %s\n", buffer);

        // Broadcast the received message to all peers
        broadcast_message(buffer);
    }
    close(client_socket);
}

void broadcast_message(const char *message) {
    for (int i = 0; i < peer_count; ++i) {
        int peer_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (peer_socket < 0) {
            perror("Socket creation failed for broadcast");
            continue;
        }

        if (connect(peer_socket, (struct sockaddr *)&peer_addresses[i], sizeof(peer_addresses[i])) < 0) {
            perror("Broadcast connection failed");
            close(peer_socket);
            continue;
        }

        send(peer_socket, message, strlen(message), 0);
        printf("Message broadcasted to %s:%d\n", inet_ntoa(peer_addresses[i].sin_addr),
               ntohs(peer_addresses[i].sin_port));
        close(peer_socket);
    }
