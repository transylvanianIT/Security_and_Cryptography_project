#ifndef TEA_H
#define TEA_H

#include <stdint.h>

void tea_encrypt_block(uint32_t* v, uint32_t* k);
void tea_decrypt_block(uint32_t* v, uint32_t* k);

void tea_encrypt_cbc(const char* in_filename, const char* out_filename, uint32_t* key, uint32_t* iv);
void tea_decrypt_cbc(const char* in_filename, const char* out_filename, uint32_t* key, uint32_t* iv);

#endif
