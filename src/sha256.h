#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

#define SHA256_DIGEST_LENGTH 32  // SHA-256 outputs a 32 byte digest
#define HASH_SIZE 65  // 64 characters for SHA-256 hex string + null terminator

typedef struct {
    uint8_t data[64];
    uint32_t datalen;
    uint64_t bitlen;
    uint32_t state[8];
} SHA256_CTX;

void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const uint8_t data[], size_t len);
void sha256_final(SHA256_CTX *ctx, uint8_t hash[]);

void calculate_sha256(const char *str, unsigned char hash[SHA256_DIGEST_LENGTH]);
void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]);
void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]);


#endif