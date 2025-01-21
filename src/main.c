#include "blockchain.h"
#include "p2p.h"
#include "sha256.h"
#include <stdio.h>

int main() {
    Blockchain *blockchain = create_blockchain();

    // Add a transaction
    Transaction tx = {"Alice", "Bob", 10.0};
    Block new_block = create_block(blockchain, &tx, 1);
    add_block(blockchain, new_block);

    // Validate the blockchain
    if (validate_blockchain(blockchain)) {
        printf("Blockchain is valid.\n");
    } else {
        printf("Blockchain is invalid.\n");
    }

    // Start the P2P network
    start_p2p_server();

    // Free the blockchain
    free_blockchain(blockchain);

    return 0;
}