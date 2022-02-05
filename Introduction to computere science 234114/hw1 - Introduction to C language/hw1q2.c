#include <stdio.h>
int main() {
    char Letter;
    char User_String=0 ;
    int i =0 ;
    printf ("Enter letter to count:\n");           // The counting letter part and the restrict for only letters .
    if (scanf (" %c", &Letter)  != 1 ) return 1 ;
    if ( (Letter<'A' || Letter>'Z') && (Letter<'a' || Letter >'z' ) ) return 1 ;
    printf ("Enter the char sequence:\n");            // The user input the string he wants and we count the letter .
        while ( User_String != '#')
        {
            if (scanf (" %c",&User_String) != 1 ) return 1 ;
            if ( (User_String==Letter) || (Letter==User_String-'a'+'A') || (Letter==User_String-'A'+'a') ) i++;
        }
    printf ("The letter appeared %d times\n",i);   // The last part the program outpus the counting of the counting letter
    return 0;
}
