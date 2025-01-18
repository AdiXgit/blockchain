//sha256.c
#include<stdio.h>
#include<string.h>

void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]){
    for(int i = 0;i<SHA256_DIGEST_LENGTH;i++){
        printf("%02x",hash[i]);
    }
    printf("\n");
}

void calculate_sha256(char *str,unsigned char hash[SHA256_DIGEST_LENGTH]){
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, str, strlen(str));
    SHA256_Final(hash, &sha256_ctx);
}

