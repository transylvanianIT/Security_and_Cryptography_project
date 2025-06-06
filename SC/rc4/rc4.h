#ifndef RC4_H
#define RC4_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h> // ✅ necesar pentru tipul FILE

void rc4_init(uint8_t* state, const uint8_t* key, size_t keylen);
void rc4_crypt(uint8_t* state, FILE* in, FILE* out);

#endif

