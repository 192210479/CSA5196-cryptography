#include <stdio.h>
#include <stdint.h>
uint32_t circularLeftShift(uint32_t value, int shift) {
    return ((value << shift) | (value >> (28 - shift))) & 0x0FFFFFF;
}

void generateSubkeys(uint64_t key) {
    const int PC1_1[] = {57, 49, 41, 33, 25, 17, 9,
                        1, 58, 50, 42, 34, 26, 18,
                        10, 2, 59, 51, 43, 35, 27,
                        19, 11, 3};

    const int PC1_2[] = {63, 55, 47, 39, 31, 23, 15,
                        7, 62, 54, 46, 38, 30, 22,g
                        14, 6, 61, 53, 45, 37, 29,
                        21, 13, 5};

    const int PC2[] = {14, 17, 11, 24, 1, 5, 3, 28,
                        15, 6, 21, 10, 23, 19, 12, 4,
                        26, 8, 16, 7, 27, 20, 13, 2,
                        41, 52, 31, 37, 47, 55, 30, 40,
                        51, 45, 33, 48, 44, 49, 39, 56,
                        34, 53, 46, 42, 50, 36, 29, 32};

    uint64_t permutedKey_1 = 0;
    uint64_t permutedKey_2 = 0;

    for (int i = 0; i < 28; i++) {
        permutedKey_1 |= ((key >> (64 - PC1_1[i])) & 1) << (27 - i);
        permutedKey_2 |= ((key >> (64 - PC1_2[i])) & 1) << (27 - i);
    }
    uint32_t C1 = (uint32_t)(permutedKey_1 >> 28) & 0xFFFFFF;
    uint32_t D1 = (uint32_t)(permutedKey_1 & 0xFFFFFF);
    uint32_t C2 = (uint32_t)(permutedKey_2 >> 28) & 0xFFFFFF;
    uint32_t D2 = (uint32_t)(permutedKey_2 & 0xFFFFFF);

    printf("Subkeys with Disjoint 24-bit Subsets:\n");
    for (int round = 1; round <= 16; round++) {
        int shift = (round == 1 || round == 2 || round == 9 || round == 16) ? 1 : 2;

        C1 = circularLeftShift(C1, shift);
        D1 = circularLeftShift(D1, shift);
        C2 = circularLeftShift(C2, shift);
        D2 = circularLeftShift(D2, shift);

        uint64_t merged = ((uint64_t)C1 << 28) | D1;
        merged |= ((uint64_t)C2 << 28) | D2;

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
