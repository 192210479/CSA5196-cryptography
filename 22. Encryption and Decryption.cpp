#include <stdio.h>
#include <stdint.h>

/* S-DES Functions */
uint8_t initial_permutation(uint8_t plaintext);
uint8_t inverse_initial_permutation(uint8_t ciphertext);
void generate_round_keys(uint8_t key);
uint8_t apply_permutation(uint8_t input, const int permutation[], int size);
uint8_t f_function(uint8_t input, uint8_t key);
uint8_t encrypt_decrypt(uint8_t plaintext, uint8_t key, uint8_t iv, int is_encrypt);

/* S-DES Constants */
const int initial_perm[] = {1, 5, 2, 0, 3, 7, 4, 6};
const int inverse_initial_perm[] = {3, 0, 2, 4, 6, 1, 7, 5};
const int p8_perm[] = {5, 2, 6, 3, 7, 4, 9, 8};
const int p4_perm[] = {1, 3, 2, 0};
const int expansion_perm[] = {3, 0, 1, 2, 1, 2, 3, 0};
const int s0_box[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};
const int s1_box[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

/* S-DES Variables */
uint8_t round_keys[2];

int main() {
    uint8_t plaintext = 0b0000001100100011; // Binary plaintext: 0000 0001 0010 0011
    uint8_t key = 0b011111101; // Binary key: 0111 1110 1
    uint8_t iv = 0b10101010; // Binary initialization vector: 1010 1010

    printf("Plaintext: %04x\n", plaintext);
    printf("Key: %02x\n", key);
    printf("Initialization Vector: %02x\n", iv);

    generate_round_keys(key);

    uint8_t ciphertext = encrypt_decrypt(plaintext, key, iv, 1); // Encrypt
    printf("Encrypted Ciphertext: %04x\n", ciphertext);

    uint8_t decrypted_plaintext = encrypt_decrypt(ciphertext, key, iv, 0); // Decrypt
    printf("Decrypted Plaintext: %04x\n", decrypted_plaintext);

    return 0;
}

uint8_t initial_permutation(uint8_t plaintext) {
    return apply_permutation(plaintext, initial_perm, 8);
}

uint8_t inverse_initial_permutation(uint8_t ciphertext) {
    return apply_permutation(ciphertext, inverse_initial_perm, 8);
}

void generate_round_keys(uint8_t key) {
    uint8_t p10_key = apply_permutation(key, p8_perm, 8);

    uint8_t left_half = p10_key >> 4;
    uint8_t right_half = p10_key & 0x0F;

    left_half = ((left_half << 1) | (left_half >> 3)) & 0x0F;
    right_half = ((right_half << 1) | (right_half >> 3)) & 0x0F;

    uint8_t p8_key = ((left_half << 3) | right_half) & 0xFF;
    round_keys[0] = p8_key;

    left_half = ((left_half << 2) | (left_half >> 2)) & 0x0F;
    right_half = ((right_half << 2) | (right_half >> 2)) & 0x0F;

    p8_key = ((left_half << 3) | right_half) & 0xFF;
    round_keys[1] = p8_key;
}

uint8_t apply_permutation(uint8_t input, const int permutation[], int size) {
    uint8_t result = 0;
    for (int i = 0; i < size; i++) {
        result <<= 1;
        result |= (input >> permutation[i]) & 1;
    }
    return result;
}

uint8_t f_function(uint8_t input, uint8_t key) {
    uint8_t expanded_input = apply_permutation(input, expansion_perm, 8);
    uint8_t xored_input = expanded_input ^ key;

    uint8_t s0_row = ((xored_input >> 4) & 0x02) | (xored_input & 0x01);
    uint8_t s0_col = (xored_input >> 1) & 0x03;
    uint8_t s0_output = s0_box[s0_row][s0_col];

    uint8_t s1_row = ((xored_input >> 3) & 0x02) | ((xored_input >> 2) & 0x01);
    uint8_t s1_col = (xored_input >> 1) & 0x03;
    uint8_t s1_output = s1_box[s1_row][s1_col];

    uint8_t combined_output = (s0_output << 2) | s1_output;
    return apply_permutation(combined_output, p4_perm, 4);
}

uint8_t encrypt_decrypt(uint8_t plaintext, uint8_t key, uint8_t iv, int is_encrypt) {
    uint8_t counter = is_encrypt ? iv : plaintext >> 8;
    uint8_t ip = is_encrypt ? plaintext & 0xFF : plaintext;

    uint8_t result = 0;

    for (int i = 0; i < 8; i++) {
        ip ^= counter;
        uint8_t encrypted_key = round_keys[0];
        uint8_t output = f_function(initial_permutation(ip), encrypted_key);

        if (is_encrypt) {
            result = (result << 1) | ((output >> 3) & 1);
        } else {
            result = (result << 1) | (ip & 1);
        }

        ip >>= 1;
        counter = output;
    }

    return is_encrypt ? result : (iv << 8) | inverse_initial_permutation(result);
}