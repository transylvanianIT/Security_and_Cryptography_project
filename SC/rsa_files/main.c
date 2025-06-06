#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rsa.h"

void load_key(const char* filename, uint64_t* a, uint64_t* n) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Key file error");
        exit(1);
    }
    fscanf(f, "%lu %lu", a, n);
    fclose(f);
}

void rsa_encrypt_file(const char* in_file, const char* key_file, const char* out_file) {
    uint64_t e, n;
    load_key(key_file, &e, &n);

    FILE* in = fopen(in_file, "rb");
    FILE* out = fopen(out_file, "w");
    if (!in || !out) {
        perror("File error");
        exit(1);
    }

    int c;
    while ((c = fgetc(in)) != EOF) {
        uint64_t encrypted = encrypt((uint64_t)(unsigned char)c, e, n);
        fprintf(out, "%lu\n", encrypted);  // scriem câte un număr pe linie
    }

    fclose(in);
    fclose(out);
}

void rsa_decrypt_file(const char* in_file, const char* key_file, const char* out_file) {
    uint64_t d, n;
    load_key(key_file, &d, &n);

    FILE* in = fopen(in_file, "r");
    FILE* out = fopen(out_file, "wb");
    if (!in || !out) {
        perror("File error");
        exit(1);
    }

    uint64_t encrypted;
    while (fscanf(in, "%lu", &encrypted) == 1) {
        uint64_t decrypted = decrypt(encrypted, d, n);
        fputc((char)decrypted, out);
    }

    fclose(in);
    fclose(out);
}


int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage:\n  %s -e|-d input keyfile output\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        rsa_encrypt_file(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "-d") == 0) {
        rsa_decrypt_file(argv[2], argv[3], argv[4]);
    } else {
        printf("Invalid mode. Use -e or -d\n");
        return 1;
    }

    return 0;
}
