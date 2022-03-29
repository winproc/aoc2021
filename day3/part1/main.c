#include <stdio.h>

int pow_l(int x, int p) {
    int temp = x;
    for (int i = 0; i < p - 1; i++) {
        x *= temp;
    }
    return x;
}

int main() {
    const int nxbin_offset = 13;

    char input_buffer[40000];
    FILE* file;

    char gamma[14];
    char epsilon[14];
    

    file = fopen("input.txt", "r");
    size_t bytes_read = fread(input_buffer, sizeof(char), 40000, file);
    int binary_nums = (bytes_read+1)/(nxbin_offset);

    for (int i = 0; i < nxbin_offset - 1; i++) {
        char gamma_bit = '0';
        int gm_occurences = 0;

        for (int m = 0; m < binary_nums; m++) {
            char bin = input_buffer[i + (nxbin_offset * m)];
            if (bin - '0') {
                gm_occurences++;
            }
        }

        // if occurences of 1 is greater than half of the total, then 1 is the most common bit
        if (gm_occurences > binary_nums/2) {
            gamma_bit = '1';
        }
        
        gamma[i] = gamma_bit;
        epsilon[i] = gamma_bit == '1' ? '0' : '1'; // the bits of epsilon rate is the opposite of gamma rate
    }

    // convert gamma and epsilon to decimal and print the product

    int gm_result = 0;
    int ep_result = 0;

    // conversion
    for (int i = nxbin_offset - 2; i > -1; i--) {
        if (gamma[i] != '0') {
            if ((nxbin_offset - 2) - i != 0) {
                gm_result += pow_l(2, (nxbin_offset - 2) - i);
            } else {
                gm_result += 1;
            }
        }
        if (epsilon[i] != '0') {
            if ((nxbin_offset - 2) - i != 0) {
                ep_result += pow_l(2, (nxbin_offset - 2) - i);
            } else {
                ep_result += 1;
            }
        }
    }

    printf("%d", gm_result * ep_result);
    

    return 0;
}