#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>

// Key for encryption and decryption
const static unsigned char aes_key[]={ 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x23, 0x6d, 0x62 };

// ECB mode encryption
void encrypt_ecb(const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY aes_key_struct;
    AES_set_encrypt_key(aes_key, 128, &aes_key_struct);

    AES_encrypt(plaintext, ciphertext, &aes_key_struct);
}

// ECB mode decryption
void decrypt_ecb(const unsigned char *ciphertext, unsigned char *decrypted) {
    AES_KEY aes_key_struct;
    AES_set_decrypt_key(aes_key, 128, &aes_key_struct);

    AES_decrypt(ciphertext, decrypted, &aes_key_struct);
}

int main() {
    // Example plaintext
    unsigned char plaintext[16] = "Hello, World!";

    // Buffer for ciphertext
    unsigned char ciphertext[16];

    // Buffer for decrypted text
    unsigned char decrypted[16];

    // Encrypting the plaintext
    encrypt_ecb(plaintext, ciphertext);

    // Printing the encrypted text
    printf("Encrypted Text: ");
    for (int i = 0; i < 16; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Decrypting the ciphertext
    decrypt_ecb(ciphertext, decrypted);

    // Printing the decrypted text
    printf("Decrypted Text: %s\n", decrypted);

    return 0;
}
