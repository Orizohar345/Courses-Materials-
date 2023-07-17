#include <stdio.h>
#include <string.h>

int find_index_in_array(char c, const char* arr, int len)
{
    for (int i = 0; i < len; i++) {
        if (arr[i] == c) {
            return i;
        }
    }

    return -1;
}

int main(int argc, char** argv)
{
    const char *chars_array = ".5`>AdIG-*8Ee}@BDRFkzw]ZYgrsm1q\\2|3Jj(KuX !':_v6aWf{y\"C;+L<S4HO[0?$bh%/MtoT9,N)&l=xUpV^7~n#ciQP";
    int len_chars_array = strlen(chars_array);
    char* input_string = argv[1];
    int len_input_string = strlen(input_string);

    for (int i = 0; i < len_input_string; i++) {
        int curr = find_index_in_array(input_string[i], chars_array, len_chars_array);
        curr += 32;
        printf("%c", curr);
    }

    return 0;
}