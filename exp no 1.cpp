#include <stdio.h>
#include <string.h>
void caesarCipher(char *text, int key) {
    int i;
    for (i = 0; i < strlen(text); i++)
	 {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            text[i] = (text[i] - 'A' + key) % 26 + 'A';
        }
        else if (text[i] >= 'a' && text[i] <= 'z') {
            text[i] = (text[i] - 'a' + key) % 26 + 'a';
        }
    }
}
int main() {
    char input[100];
    int key;
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    for (key = 1; key <= 25; key++) {
        char encrypted[100];
        strcpy(encrypted, input);
        caesarCipher(encrypted, key);
        printf("Key %d: %s", key, encrypted);
    }
    return 0;
}
