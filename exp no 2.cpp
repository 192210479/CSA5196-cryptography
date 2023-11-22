#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void monoalphabetic_substitution(char *plaintext, char *ciphertext, char *input_text) {
    int i;
    for (i = 0; i < strlen(input_text); i++) {
        char current_char = input_text[i];
        if (isupper(current_char)) {
            input_text[i] = ciphertext[current_char - 'A'];
        }
        else if (islower(current_char)) {
            input_text[i] = tolower(ciphertext[current_char - 'a']);
        }
    }
}
int main() {
    char plaintext_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char ciphertext_alphabet[] = "XPMGTDHLYONZBWEARKJUFSCIQV";
    char input_text[100];
    printf("Enter the text to be encrypted: ");
    fgets(input_text, sizeof(input_text), stdin);
    monoalphabetic_substitution(plaintext_alphabet, ciphertext_alphabet, input_text);
    printf("Encrypted text: %s\n", input_text);

    return 0;
}

