#include "blockchain.h"
#include <stdio.h>

int main() {
    Blockchain *blockchain = create_blockchain();

    Block block1 = create_block(NULL, "Alice pays Bob 5 BTC"); 
    Block block2 = create_block(&block1, "Bob pays Charlie 3 BTC");

    print_blockchain(blockchain);

    free_blockchain(blockchain);
    return 0;
}
