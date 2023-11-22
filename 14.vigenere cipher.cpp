#include <stdio.h>
#include <string.h>
#include<ctype.h>

void vigenereEncrypt(char *plaintext, int *key, int keyLength) {
    int i, len = strlen(plaintext);
    printf("Ciphertext: ");

    for (i = 0; i < len; i++) {
        if (plaintext[i] != ' ') {
            int shift = key[i % keyLength]; 
            char encryptedChar = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            printf("%c", encryptedChar);
        } else {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int keyLength = sizeof(key) / sizeof(key[0]);

    for (int i = 0; plaintext[i]; i++) {
        plaintext[i] = tolower(plaintext[i]);
    }

    vigenereEncrypt(plaintext, key, keyLength);

    return 0;
}