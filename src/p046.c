#include <openssl/evp.h>
#include <openssl/aes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void handleErrors() {
    fprintf(stderr, "Error occurred\n");
    exit(1);
}

void aes256_encrypt(const char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext) {
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
    char message[1024];
    printf("Message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    unsigned char key[32];
    unsigned char iv[16];
    if (!read_key_and_iv("key_iv.txt", key, iv)) {
        return 1;
    }

    unsigned char ciphertext[2048];
    aes256_encrypt(message, key, iv, ciphertext);

    for (int i = 0; i < sizeof(ciphertext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    memset(key, 0, sizeof(key));
    memset(iv, 0, sizeof(iv));

    return 0;
}
