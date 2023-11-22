#include <stdio.h>
#include <string.h>

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4.)4);806*;48860))85;;]8*;:8+83(88)5+;46(;88*96*?;8)(;485);5*12:‡(;4956*2(5*-4)88*;4069285);)6+8)4‡‡;1(19;48081;8:81;48†85;4)485†528806*81(‡9;48;(88;4(234;48)4;161;:188;‡?;";
    int frequency[256] = {0};
    int i, maxFreq = 0;
    char possibleE;
    
    for (i = 0; i < strlen(ciphertext); i++) {
        frequency[(int)ciphertext[i]]++;
    }


    for (i = 0; i < 256; i++) {
        if (frequency[i] > maxFreq) {
            maxFreq = frequency[i];
            possibleE = (char)i;
        }
    }

    printf("Possible 'e' character: %c\n", possibleE);

    return 0;
}