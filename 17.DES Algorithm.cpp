#include <stdio.h>
#include <stdint.h>

uint32_t circularLeftShift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFFF;
}

void generateSubkeys(uint64_t key) {
    const int PC1[] = {57, 49, 41, 33, 25, 17, 9,
                      1, 58, 50, 42, 34, 26, 18,
                      10, 2, 59, 51, 43, 35, 27,
                      19, 11, 3, 60, 52, 44, 36,
                      63, 55, 47, 39, 31, 23, 15,
                      7, 62, 54, 46, 38, 30, 22,
                      14, 6, 61, 53, 45, 37, 29,
                      21, 13, 5, 28, 20, 12, 4};

    const int PC2[] = {14, 17, 11, 24, 1, 5, 3, 28,
                      15, 6, 21, 10, 23, 19, 12, 4,
                      26, 8, 16, 7, 27, 20, 13, 2,
                      41, 52, 31, 37, 47, 55, 30, 40,
                      51, 45, 33, 48, 44, 49, 39, 56,
                      34, 53, 46, 42, 50, 36, 29, 32};

    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        permutedKey |= ((key >> (64 - PC1[i])) & 1) << (55 - i);
    }

    uint32_t C = (uint32_t)(permutedKey >> 28) & 0x0FFFFFFF;
    uint32_t D = (uint32_t)(permutedKey & 0x0FFFFFFF);

    printf("Subkeys for Decryption:\n");
    for (int round = 1; round <= 16; round++) {
        int shift = (round == 1 || round == 2 || round == 9 || round == 16) ? 1 : 2;

        C = circularLeftShift(C, shift);
        D = circularLeftShift(D, shift);

      
        uint64_t merged = (((uint64_t)C) << 28) | D;
        uint64_t subkey = 0;
        for (int i = 0; i < 48; i++) {
            subkey |= ((merged >> (56 - PC2[i])) & 1) << (47 - i);
        }

        printf("Round %2d: %012llx\n", round, subkey);
    }
}

int main() {
    
    uint64_t key = 0x133457799BBCDFF1;

    printf("Initial Key: %016llx\n", key);

    generateSubkeys(key);

    return 0;
}