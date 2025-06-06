#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "rc4.h"

int main(int argc, char* argv[]) {
    if (argc != 6 || strcmp(argv[1], "-a") != 0 || strcmp(argv[2], "rc4") != 0) {
        printf("Usage:\n  %s -a rc4 input_file key_file output_file\n", argv[0]);
        return 1;
    }

    const char* in_filename = argv[3];
    const char* key_filename = argv[4];
    const char* out_filename = argv[5];

    FILE* in = fopen(in_filename, "rb");
    FILE* keyfile = fopen(key_filename, "rb");
    FILE* out = fopen(out_filename, "wb");

    if (!in || !keyfile || !out) {
        perror("File error");
        return 1;
    }

    uint8_t key[256];
    size_t keylen = fread(key, 1, sizeof(key), keyfile);
    if (keylen == 0) {
        fprintf(stderr, "Key file is empty!\n");
        return 1;
    }

    uint8_t state[256];
    rc4_init(state, key, keylen);
    rc4_crypt(state, in, out);

    fclose(in);
    fclose(out);
    fclose(keyfile);

    return 0;
}
