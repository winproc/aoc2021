#include <stdio.h>

int char_to_int(char c) {
    return c - '0'; // return ascii offset from 0
}

int main() {

    const int offset = 2;

    int depth = 0;
    int h_distance = 0;
    int aim = 0;

    char input_buffer[30000];
    FILE* input_file = fopen("input.txt", "r");

    size_t bytes_read = fread(input_buffer, sizeof(char), 30000, input_file);

    for (int i = 0; i < bytes_read; i++) {
        if (input_buffer[i] == 'f') { // starting char of 'forward'
            i += (6 + offset);
            int inc = char_to_int(input_buffer[i]);
            h_distance += char_to_int(input_buffer[i]);
            depth += (inc * aim);         

        } else if (input_buffer[i] == 'd') { // starting char of 'down'
            i += (3 + offset);
            aim += char_to_int(input_buffer[i]);
        } else if (input_buffer[i] == 'u') { // starting char of 'up'
            i += (1 + offset);
            aim -= char_to_int(input_buffer[i]);
        }
    }

    printf("%d", depth * h_distance);


    return 0;
}