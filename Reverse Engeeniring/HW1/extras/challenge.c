#include <stdio.h>

int main() {
    int resources[5] = {0, 0, 0, 0, 0}; 

    while (1) {
        char str[12] = {0};

        int scanf_res = scanf("%s", &str);
        if (scanf_res == -1)
            break;

        if (str[0] == 'r') {
            resources[0] += 1;
            resources[1] += 1;
        }
        else if (str[0] == 's') {
            resources[0] += 1;
            resources[1] += 1;
            resources[2] += 1;
            resources[3] += 1;
        }
        else if (str[0] == 'c') {
            resources[3] += 2;
            resources[4] += 3;
        }
        else if (str[0] == 'd') {
            resources[2] += 1;
            resources[3] += 1;
            resources[4] += 1;
        }
    }

    for(int i=0; i<4; i++) {
        if (resources[i] > 100)
            printf("99 ");
        else
            printf("%02d ", resources[i]);
    }

    if (resources[4] > 100)
        printf("99\n");
    else
        printf("%02d\n", resources[4]);

    return 0;
}