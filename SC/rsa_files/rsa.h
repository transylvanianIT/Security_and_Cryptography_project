#ifndef RSA_H
#define RSA_H

#include <stdint.h>

void generate_keys(uint64_t* n, uint64_t* e, uint64_t* d);
uint64_t encrypt(uint64_t msg, uint64_t e, uint64_t n);
uint64_t decrypt(uint64_t cipher, uint64_t d, uint64_t n);

#endif
