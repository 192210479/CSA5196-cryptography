#include <stdio.h>

#define MOD 26

void hillEncrypt(int plaintext[], int keyMatrix[][3], int encrypted[], int length) {
    int i, j, k;

    for (i = 0; i < length; i += 3) {
        for (j = 0; j < 3; j++) {
            encrypted[i + j] = 0;
            for (k = 0; k < 3; k++) {
                encrypted[i + j] += keyMatrix[j][k] * plaintext[i + k];
            }
            encrypted[i + j] %= MOD;
        }
    }
}

void recoverKey(int plaintext[], int ciphertext[], int keyMatrix[][3], int length) {
    int i, j, k;

    for (i = 0; i < length; i += 3) {
        for (j = 0; j < 3; j++) {
            keyMatrix[j][i / 3] = 0;
            for (k = 0; k < 3; k++) {
                keyMatrix[j][i / 3] += (plaintext[i + k] * plaintext[i + k + j]) % MOD;
            }
            keyMatrix[j][i / 3] %= MOD;
        }
    }
}

int main() {
    int plaintext[] = {3, 4, 7, 2, 0, 6, 1, 5, 7}; 
    int ciphertext[] = {20, 21, 23, 8, 19, 18, 12, 5, 10};
    int keyMatrix[3][3] = {0}; 

    int encrypted[9] = {0}; 

    int length = sizeof(plaintext) / sizeof(plaintext[0]);

   
    recoverKey(plaintext, ciphertext, keyMatrix, length);


    hillEncrypt(plaintext, keyMatrix, encrypted, length);

    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    printf("\nEncrypted Text using Recovered Key Matrix:\n");
    for (int i = 0; i < length; i++) {
        printf("%d ", encrypted[i]);
    }
    printf("\n");

    return 0;
}