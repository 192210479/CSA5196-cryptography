#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char playfairMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void getPosition(char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (playfairMatrix[i][j] == letter || (playfairMatrix[i][j] == 'I' && letter == 'J')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char *message) {
    int len = strlen(message);
    for (int i = 0; i < len; i++) {
        if (!isalpha(message[i])) {
            continue;
        }

        if (message[i] == 'J') {
            message[i] = 'I';
        }

        int row1, col1, row2, col2;
        getPosition(message[i], &row1, &col1);

        if (i + 1 < len && isalpha(message[i + 1])) {
            if (message[i + 1] == 'J') {
                message[i + 1] = 'I';
            }
            getPosition(message[i + 1], &row2, &col2);

            if (row1 == row2) {
                message[i] = playfairMatrix[row1][(col1 + 1) % SIZE];
                message[i + 1] = playfairMatrix[row2][(col2 + 1) % SIZE];
            } else if (col1 == col2) {
                message[i] = playfairMatrix[(row1 + 1) % SIZE][col1];
                message[i + 1] = playfairMatrix[(row2 + 1) % SIZE][col2];
            } else {
                message[i] = playfairMatrix[row1][col2];
                message[i + 1] = playfairMatrix[row2][col1];
            }
            i++;
        }
    }
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once";
    int len = strlen(message);
    char processedMessage[len * 2];
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            processedMessage[j++] = toupper(message[i]);
        }
    }
    processedMessage[j] = '\0';

    printf("Original Message: %s\n", processedMessage);

    encrypt(processedMessage);

    printf("Encrypted Message: %s\n", processedMessage);

    return 0;
}