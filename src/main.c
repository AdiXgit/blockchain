#include "blockchain.h"
#include <stdio.h>

int main() {
    Blockchain *blockchain = create_blockchain();

    Block block1 = create_block(blockchain, "Alice pays Bob 5 BTC");
    add_block(blockchain, block1);

    Block block2 = create_block(blockchain, "Bob pays Charlie 3 BTC");
    add_block(blockchain, block2);

    print_blockchain(blockchain);

    free_blockchain(blockchain);
    return 0;
}
