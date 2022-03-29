#include <stdio.h>


int main() {
    const int nxbin_offset = 13;

    char input_buffer[40000];
    
    FILE* file;

    char* oxygen_gen_rating;
    char* co_rating;

    file = fopen("input.txt", "r");
    size_t bytes_read = fread(input_buffer, sizeof(char), 40000, file);

    int binary_nums = (bytes_read+1)/(nxbin_offset);
    int binary_nums_c = binary_nums;
    int binary_nums_c_co = binary_nums;

    char* parsed_buffer[1000];
    char* parsed_buffer_co[1000];
    int pb_trcker = 0;
    
    for (int i = 0; i < bytes_read; i++) {
        parsed_buffer[pb_trcker] = &input_buffer[i];
        parsed_buffer_co[pb_trcker] = &input_buffer[i];
        while (input_buffer[i] != '\n') {
            i++;
        }
        pb_trcker++;
    }

    for (int i = 0; i < nxbin_offset - 1; i++) {

        int z_count = 0;
        int o_count = 0;

        char ox_bit = '1';
        char co_bit = '0';

        for (int j = 0; j < binary_nums; j++) {
            if (parsed_buffer[j] != NULL) {
                if (parsed_buffer[j][i] == '0') {
                    z_count++;
                }
            }
            if (parsed_buffer_co[j] != NULL) {
                if (parsed_buffer_co[j][i] == '1') {
                    o_count++;
                }
            }
            
        }

        if (z_count > (double)binary_nums_c/2) {
            ox_bit = '0';
        }
        if (o_count < (double)binary_nums_c_co/2) {
            co_bit = '1';
        }

        for (int j = 0; j < binary_nums; j++) {
            if (parsed_buffer[j] != NULL) { 
                if (parsed_buffer[j][i] != ox_bit) {
                    if (binary_nums_c != 1) {
                        parsed_buffer[j] = NULL;
                        binary_nums_c -= 1;
                    }
                }
            }
            if (parsed_buffer_co[j] != NULL) {
                if (parsed_buffer_co[j][i] != co_bit) {
                    if (binary_nums_c_co != 1) {
                        parsed_buffer_co[j] = NULL;
                        binary_nums_c_co -= 1;
                    }
                }
            }
        }
        
    }
    
    int ptr = 0;
    while (parsed_buffer[ptr] == NULL) { ptr++; };

    oxygen_gen_rating = parsed_buffer[ptr];
    oxygen_gen_rating[nxbin_offset - 1] = '\0';

    ptr = 0;
    while (parsed_buffer_co[ptr] == NULL) { ptr++; };

    co_rating = parsed_buffer_co[ptr];
    co_rating[nxbin_offset - 1] = '\0';

    int gm_result = 0;
    int ep_result = 0;

    // conversion
    for (int i = nxbin_offset - 2; i > -1; i--) {
        if (oxygen_gen_rating[i] != '0') {
            if ((nxbin_offset - 2) - i != 0) {
                gm_result += pow_l(2, (nxbin_offset - 2) - i);
            } else {
                gm_result += 1;
            }
        }
        if (co_rating[i] != '0') {
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