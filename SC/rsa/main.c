#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rsa.h"

int main() {
    uint64_t n, e, d;
    generate_keys(&n, &e, &d);

    printf("Public key:  (e=%lu, n=%lu)\n", e, n);
    printf("Private key: (d=%lu, n=%lu)\n", d, n);

    uint64_t msg;
    printf("Enter number to encrypt (as uint64_t): ");
    scanf("%lu", &msg);

    uint64_t enc = encrypt(msg, e, n);
    printf("Encrypted: %lu\n", enc);

    uint64_t dec = decrypt(enc, d, n);
    printf("Decrypted: %lu\n", dec);

    return 0;
}
