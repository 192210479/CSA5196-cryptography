#include <stdio.h>
#include<string.h>

int main() {
    int key[2][2] = {{9, 4}, {5, 7}};
    int inverse_key[2][2] = {{7, 22}, {21, 9}};
    char ciphertext[] = "mo os ip jw hm kl iu ar rf";
    int len = strlen(ciphertext);
    int i, j;
    int pairs[len / 2][2];
    
    for (i = 0; i < len; i += 2) {
        pairs[i / 2][0] = ciphertext[i] - 'a';
        pairs[i / 2][1] = ciphertext[i + 1] - 'a';
    }

    printf("Decrypted message: ");
    for (i = 0; i < len / 2; i++) {
        for (j = 0; j < 2; j++) {
            int value = (inverse_key[j][0] * pairs[i][0] + inverse_key[j][1] * pairs[i][1]) % 26;
            printf("%c", value + 'a');
        }
        printf(" ");
    }
    printf("\n");

    return 0;
}