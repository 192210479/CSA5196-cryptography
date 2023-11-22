#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void prepareKeyMatrix(char *key, char keyMatrix[SIZE][SIZE]) {
    int i, j, k;
    char *keyPointer, *uniqueKey;
    int isPresent[26] = {0};
    uniqueKey = (char *)malloc(strlen(key) * sizeof(char));
    j = 0;
    for (i = 0; i < strlen(key); i++) {
        if (!isPresent[key[i] - 'A'] && key[i] != 'J') {
            uniqueKey[j++] = toupper(key[i]);
            isPresent[key[i] - 'A'] = 1;
        }
    }
    keyPointer = uniqueKey;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (k < strlen(uniqueKey))
                keyMatrix[i][j] = *keyPointer++;
            else {
                for (k = 0; k < 26; k++) {
                    if (!isPresent[k] && k != ('J' - 'A')) {
                        keyMatrix[i][j] = 'A' + k;
                        isPresent[k] = 1;
                        break;
                    }
                }
            }
        }
    }

    free(uniqueKey);
}
void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptDigraph(char keyMatrix[SIZE][SIZE], char digraph[2], char cipher[2]) {
    int row1, col1, row2, col2;

    findPosition(keyMatrix, digraph[0], &row1, &col1);
    findPosition(keyMatrix, digraph[1], &row2, &col2);

    if (row1 == row2) {
        cipher[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        cipher[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        cipher[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        cipher[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        cipher[0] = keyMatrix[row1][col2];
        cipher[1] = keyMatrix[row2][col1];
    }
}
void playfairEncrypt(char keyMatrix[SIZE][SIZE], char *input, char *output) {
    int i, j;
    char digraph[2], cipher[2];

    for (i = 0; i < strlen(input); i += 2) {
        digraph[0] = toupper(input[i]);
        digraph[1] = toupper(input[i + 1]);

        encryptDigraph(keyMatrix, digraph, cipher);

        output[i] = cipher[0];
        output[i + 1] = cipher[1];
    }
	output[i] = '\0';
}
int main() {
    char key[20];
    char keyMatrix[SIZE][SIZE];
    char input[100];
    char output[100];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    printf("Enter the plaintext: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    prepareKeyMatrix(key, keyMatrix);
    playfairEncrypt(keyMatrix, input, output);
    printf("Encrypted text: %s\n", output);
	return 0;
}

