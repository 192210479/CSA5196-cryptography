#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void encrypt(char plaintext[], char key[]);
void decrypt(char ciphertext[], char key[]);

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character if present
    if (strlen(plaintext) > 0 && plaintext[strlen(plaintext) - 1] == '\n') {
        plaintext[strlen(plaintext) - 1] = '\0';
    }

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline character if present
    if (strlen(key) > 0 && key[strlen(key) - 1] == '\n') {
        key[strlen(key) - 1] = '\0';
    }

    // Convert the key to uppercase
    for (int i = 0; key[i] != '\0'; i++) {
        key[i] = toupper(key[i]);
    }

    encrypt(plaintext, key);
    printf("Encrypted text: %s\n", plaintext);

    decrypt(plaintext, key);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

void encrypt(char plaintext[], char key[]) {
    int keyLength = strlen(key);
    int textLength = strlen(plaintext);
    int i, j = 0;

    for (i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = islower(plaintext[i]) ? 'a' : 'A';
            int shift = key[j % keyLength] - 'A';

            plaintext[i] = base + (plaintext[i] - base + shift) % ALPHABET_SIZE;
            key[keyLength + j] = plaintext[i];
            j++;
        }
    }
}

void decrypt(char ciphertext[], char key[]) {
    int keyLength = strlen(key);
    int textLength = strlen(ciphertext);
    int i, j = 0;

    for (i = 0; i < textLength; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            int shift = key[j % keyLength] - 'A';

            ciphertext[i] = base + (ciphertext[i] - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
            key[keyLength + j] = ciphertext[i];
            j++;
        }
    }
}
