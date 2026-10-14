#include <openssl/evp.h>
#include <openssl/aes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void handleErrors() {
    fprintf(stderr, "Error occurred\n");
    exit(1);
}

void aes256_encrypt(const char *plaintext, unsigned char *ciphertext, const unsigned char *key, const unsigned char *iv) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) handleErrors();

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)plaintext, strlen(plaintext))) handleErrors();
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
}

void hex_to_bytes(const char *hex, unsigned char *bytes, int size) {
    for (int i = 0; i < size; i++) {
        sscanf(hex + 2 * i, "%2hhx", &bytes[i]);
    }
}

void bytes_to_hex(const unsigned char *bytes, char *hex, int size) {
    for (int i = 0; i < size; i++) {
        sprintf(hex + 2 * i, "%02x", bytes[i]);
    }
    hex[size * 2] = '\0';
}

int read_key_and_iv(const char *filename, unsigned char *key, unsigned char *iv) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        return 0;
    }

    char key_hex[65];
    char iv_hex[33];

    if (fscanf(file, "%64s %32s", key_hex, iv_hex) != 2) {
        fprintf(stderr, "Invalid format in file: %s\n", filename);
        fclose(file);
        return 0;
    }

    fclose(file);

    hex_to_bytes(key_hex, key, 32);
    hex_to_bytes(iv_hex, iv, 16);

    return 1;
}

int main() {
    char sensitiveText[1024];
    printf("Sensitive text: ");
    fgets(sensitiveText, sizeof(sensitiveText), stdin);
    sensitiveText[strcspn(sensitiveText, "\n")] = '\0';

    unsigned char key[32];
    unsigned char iv[16];
    if (!read_key_and_iv("key_iv.txt", key, iv)) {
        return 1;
    }

    unsigned char ciphertext[2048];
    aes256_encrypt(sensitiveText, ciphertext, key, iv);

    char hex[4097];
    bytes_to_hex(ciphertext, hex, sizeof(ciphertext));
    printf("Encrypted: %s\n", hex);

    memset(key, 0, sizeof(key));
    memset(iv, 0, sizeof(iv));
    memset(sensitiveText, 0, sizeof(sensitiveText));

    return 0;
}
