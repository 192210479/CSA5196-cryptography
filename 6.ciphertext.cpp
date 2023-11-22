#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
void generateCipherTable(char *keyword, char *cipherTable)
 {
    int i, j, k;
    int keywordLength = strlen(keyword);
    char keyTable[ALPHABET_SIZE] = {0};
    for (i = 0; i < keywordLength; ++i) 
	{
        keyword[i] = toupper(keyword[i]);
        if (!keyTable[keyword[i] - 'A']) 
		{
            keyTable[keyword[i] - 'A'] = 1;
            cipherTable[i] = keyword[i];
        }
    }
    for (j = 0, k = keywordLength; j < ALPHABET_SIZE; ++j) 
	{
        if (!keyTable[j])
		 {
            cipherTable[k++] = 'A' + j;
        }
    }
     cipherTable[ALPHABET_SIZE] = '\0'; 
}
void encryptMonoalphabetic(char *message, char *cipherTable) 
{
    int i;
    for (i = 0; message[i] != '\0'; ++i)
	 {
        char ch = message[i];
        if (isalpha(ch)) {
            int index = toupper(ch) - 'A';
            if (islower(ch)) {
                message[i] = tolower(cipherTable[index]);
            } else {
                message[i] = cipherTable[index];
            }
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char cipherTable[ALPHABET_SIZE + 1];
    char message[100];
    generateCipherTable(keyword, cipherTable);
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n')
	 {
        message[len - 1] = '\0';
    }
    encryptMonoalphabetic(message, cipherTable);
    printf("Encrypted message: %s\n", message);

    return 0;
}