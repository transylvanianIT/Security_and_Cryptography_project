#include "rsa.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_keys(uint64_t* n, uint64_t* e, uint64_t* d) {
    srand(time(NULL));
    uint64_t p, q;
    do { p = rand() % 100 + 100; } while (!is_prime(p));
    do { q = rand() % 100 + 100; } while (!is_prime(q) || q == p);

    *n = p * q;
    uint64_t phi = (p - 1) * (q - 1);

    *e = 3;
    while (gcd(*e, phi) != 1) (*e) += 2;

    *d = modinv(*e, phi);

    printf("Generated primes p=%lu, q=%lu\n", p, q);
}

uint64_t encrypt(uint64_t msg, uint64_t e, uint64_t n) {
    return powmod(msg, e, n);
}

uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n) {
    return powmod(cipher, d, n);
}
