#include "rc4.h"

void rc4_init(uint8_t* state, const uint8_t* key, size_t keylen) {
    for (int i = 0; i < 256; i++) {
        state[i] = i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + state[i] + key[i % keylen]) % 256;
        uint8_t temp = state[i];
        state[i] = state[j];
        state[j] = temp;
    }
}

void rc4_crypt(uint8_t* state, FILE* in, FILE* out) {
    uint8_t S[256];
    for (int i = 0; i < 256; i++) {
        S[i] = state[i];
    }

    int i = 0, j = 0, c;
    while ((c = fgetc(in)) != EOF) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;

        uint8_t temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        uint8_t K = S[(S[i] + S[j]) % 256];
        fputc(c ^ K, out);
    }
}

