#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// utility function
int file_to_int_array(FILE* file_ptr, int* put_buffer) {
    
    int array_read_ptr = 0;
    char rd_temp_buf[10000];

    size_t read_bytes = fread(rd_temp_buf, sizeof(char), 10000, file_ptr);

    for (int i = 0; i < read_bytes; i++) {
        char intb[20];
        int intb_ptr = 0;
        while (rd_temp_buf[i] != '\n') {
            intb[intb_ptr] = rd_temp_buf[i];
            intb_ptr++;
            i++;
        }

        put_buffer[array_read_ptr] = atoi(intb);
        array_read_ptr++;
        
    }

    return array_read_ptr;
}

int main(int argc, char** argv) {
    

    FILE* input_file;
    input_file = fopen("input.txt", "r");
    int array[4000];

    int elements = file_to_int_array(input_file, array);
    int incr_sumf_elements = 0;

    for (int i = 1; i < elements - 1; i++) {
        if ((array[i] + array[i + 1] + array[i + 2]) > (array[i - 1] + array[i] + array[i + 1])) {
            incr_sumf_elements++;
        }
    }

    printf("%d", incr_sumf_elements);

    return 0;
}