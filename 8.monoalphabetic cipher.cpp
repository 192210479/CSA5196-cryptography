#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherKey(char keyword[], char cipherKey[]) {
    int len = strlen(keyword);
    int index = 0;
    int i, j;

    strcpy(cipherKey, keyword);

    for (i = 0; i < len; i++) {
        cipherKey[i] = toupper(cipherKey[i]);
        for (j = 'A'; j <= 'Z'; j++) {
            if (cipherKey[i] == j) {
                cipherKey[j - 'A'] = '*'; 
                break;
            }
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (cipherKey[i] != '*') {
            cipherKey[i] = 'A' + index;
            index++;
        }
    }
}

void encrypt(char plaintext[], char cipherKey[], char ciphertext[]) {
    int len = strlen(plaintext);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char originalChar = toupper(plaintext[i]);
            if (originalChar >= 'A' && originalChar <= 'Z') {
                ciphertext[i] = islower(plaintext[i]) ?
                               tolower(cipherKey[originalChar - 'A']) :
                               cipherKey[originalChar - 'A'];
            }
        } else {
           
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World!";
    char cipherKey[ALPHABET_SIZE];
    char ciphertext[100];

    generateCipherKey(keyword, cipherKey);

    printf("Generated Cipher Key: %s\n", cipherKey);

    encrypt(plaintext, cipherKey, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}