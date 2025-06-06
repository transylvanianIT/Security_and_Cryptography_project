#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "tea.h"

#define BLOCK_SIZE 8
#define DELTA 0x9e3779b9
#define ROUNDS 32

void tea_encrypt_block(uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    for (int i = 0; i < ROUNDS; i++) {
        sum += DELTA;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    v[0] = v0; v[1] = v1;
}

void tea_decrypt_block(uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = DELTA * ROUNDS;
    for (int i = 0; i < ROUNDS; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= DELTA;
    }
    v[0] = v0; v[1] = v1;
}

void tea_encrypt_cbc(const char* in_filename, const char* out_filename, uint32_t* key, uint32_t* iv) {
    FILE* in = fopen(in_filename, "rb");
    FILE* out = fopen(out_filename, "wb");
    if (!in || !out) {
        perror("File error");
        exit(1);
    }

    uint8_t buffer[BLOCK_SIZE], xor_block[BLOCK_SIZE];
    size_t n;

    memcpy(xor_block, iv, BLOCK_SIZE);

    while ((n = fread(buffer, 1, BLOCK_SIZE, in)) > 0) {
        if (n < BLOCK_SIZE) memset(buffer + n, BLOCK_SIZE - n, BLOCK_SIZE - n); // PKCS-style padding

        for (int i = 0; i < BLOCK_SIZE; i++) buffer[i] ^= xor_block[i];

        tea_encrypt_block((uint32_t*)buffer, key);
        fwrite(buffer, 1, BLOCK_SIZE, out);

        memcpy(xor_block, buffer, BLOCK_SIZE);
    }

    fclose(in);
    fclose(out);
}

void tea_decrypt_cbc(const char* in_filename, const char* out_filename, uint32_t* key, uint32_t* iv) {
    FILE* in = fopen(in_filename, "rb");
    FILE* out = fopen(out_filename, "wb");
    if (!in || !out) {
        perror("File error");
        exit(1);
    }

    uint8_t buffer[BLOCK_SIZE], prev[BLOCK_SIZE], tmp[BLOCK_SIZE];
    size_t n;

    memcpy(prev, iv, BLOCK_SIZE);

    while ((n = fread(buffer, 1, BLOCK_SIZE, in)) > 0) {
        memcpy(tmp, buffer, BLOCK_SIZE);

        tea_decrypt_block((uint32_t*)buffer, key);
        for (int i = 0; i < BLOCK_SIZE; i++) buffer[i] ^= prev[i];

        fwrite(buffer, 1, BLOCK_SIZE, out);

        memcpy(prev, tmp, BLOCK_SIZE);
    }

    fclose(in);
    fclose(out);
}
