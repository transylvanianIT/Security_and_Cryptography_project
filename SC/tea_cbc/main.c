#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "tea.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage:\n");
        printf("  %s -e|-d input_file key_file output_file iv_file\n", argv[0]);
        return 1;
    }

    uint32_t key[4], iv[2];
    FILE* kf = fopen(argv[3], "rb");
    FILE* ivf = fopen(argv[5], "rb");
    if (!kf || !ivf) {
        perror("Key or IV file error");
        return 1;
    }
    fread(key, sizeof(uint32_t), 4, kf);
    fread(iv, sizeof(uint32_t), 2, ivf);
    fclose(kf);
    fclose(ivf);

    if (strcmp(argv[1], "-e") == 0) {
        tea_encrypt_cbc(argv[2], argv[4], key, iv);
    } else if (strcmp(argv[1], "-d") == 0) {
        tea_decrypt_cbc(argv[2], argv[4], key, iv);
    } else {
        printf("Invalid mode. Use -e or -d\n");
        return 1;
    }

    return 0;
}
