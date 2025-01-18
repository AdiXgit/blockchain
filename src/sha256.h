#ifndef SHA256_H
#define SHA256_H



#define SHA256_DIGEST_LENGTH 32  //it produces a 256-bit (32-byte) hash

// Function to calculate the SHA-256 hash of a given input string
void calculate_sha256(const char *str, unsigned char hash[SHA256_DIGEST_LENGTH]);

// Helper function to print the SHA-256 hash as a hexadecimal string
void print_hash(unsigned char hash[SHA256_DIGEST_LENGTH]);

#endif
