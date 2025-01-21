#ifndef P2P_H
#define P2P_H

#include <winsock2.h>
#include <ws2tcpip.h>

extern int peer_count;
extern struct sockaddr_in peer_addresses[];

void add_peer(struct sockaddr_in peer_addr);
void handle_client(int client_socket);
void start_p2p_server();

#endif

