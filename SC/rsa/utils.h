#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

uint64_t gcd(uint64_t a, uint64_t b);
uint64_t modinv(uint64_t a, uint64_t m);
uint64_t powmod(uint64_t base, uint64_t exp, uint64_t mod);
int is_prime(uint64_t n);

#endif
