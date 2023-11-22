#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void calculateLetterFrequencies(const char *text, int *frequencies) {
    for (size_t i = 0; i < strlen(text); ++i) {
        char currentChar = text[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            frequencies[currentChar - base]++;
        }
    }
}

void decryptAdditive(const char *ciphertext, int shift, char *plaintext) {
    size_t textLength = strlen(ciphertext);
    for (size_t i = 0; i < textLength; ++i) {
        char currentChar = ciphertext[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            plaintext[i] = ((currentChar - base - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = currentChar; 
        }
    }
    plaintext[textLength] = '\0'; 
}


void printTopPlaintexts(const char *ciphertext, int topN) {
    int letterFrequencies[ALPHABET_SIZE] = {0};
    calculateLetterFrequencies(ciphertext, letterFrequencies);

    printf("Top %d Possible Plaintexts:\n", topN);

    for (int i = 0; i < topN; ++i) {
        int maxFrequency = -1;
        int maxShift = 0;
        for (int shift = 0; shift < ALPHABET_SIZE; ++shift) {
            if (letterFrequencies[shift] > maxFrequency) {
                maxFrequency = letterFrequencies[shift];
                maxShift = shift;
            }
        }
        char plaintext[1000];
        decryptAdditive(ciphertext, maxShift, plaintext);
          printf("[%d] Shift %d: %s\n", i + 1, maxShift, plaintext);
        letterFrequencies[maxShift] = -1;
    }
}

int main() {
    char ciphertext[1000];
    int topN;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
   printTopPlaintexts(ciphertext, topN);

    return 0;
}
