#include <stdio.h>

int main()
{
    char str[29] = "IDAEKGGEFGILKNLIJKCHMEABAKHLM";
    int i = 0;
    
    printf("%s\n", str);
    
    for(int j=0; j<29; j++) {
        str[j] -= 'A';    
    }
    
    for(int j=0; j<29; j++) {
        str[28 - j] ^= str[(28 - j + 1) % 29];   
    }
    
    for(int j=0; j<29; j++) {
        str[j] += 'A';    
    }
    
    printf("%s\n", str);
    
    return 0;
}