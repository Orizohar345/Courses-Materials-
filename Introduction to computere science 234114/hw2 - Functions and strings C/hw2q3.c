#include <stdio.h>
#define N 10
void GRADES_PRINTER(int number) // Function that prints the histogram base
{
for (int i = 1;i <= number ; i++)
{
printf("%d ", i);
}
}
char CHAR_SCAN(char C) // Function that take a char from the account to print the histogram with
{
    printf("Please enter a character:\n");
    scanf(" %c", &C);
    return C ;
}


void NUM_SCAN(int GRADES_ARR[] , int number ) // Function that print to array how much studens get a grade
{
    printf("Please enter grades:\n");
    while (scanf("%d", &number) != EOF )
    {
        GRADES_ARR[number - 1]++;
    }
}
int Maximum(const int GRADES_ARR[],int Max) // Function that equalateד which grade most gotten
{
    for (int i = 0; i < N ; i++)
    {
        if (GRADES_ARR[i] > Max)
        {
            Max = GRADES_ARR[i];
        }

    }
    return Max;
}
void HISTOGRAM_PRINTER(int GRADES_ARR[],int Max ,char CHARACTER , char SPACE ) // Function that prints the histogram
{
    printf("Histogram:\n");
    while (Max > 0)
    {
        for (int i = 0; i < N; i++) {
            if (GRADES_ARR[i] >= Max) {
                printf("%c ", CHARACTER);
            }
            else
            {
                printf("%c ", SPACE);
            }
        }
        Max--;
        printf("\n");
    }
}
int main()
{
    char C=0 , CHARACTER = CHAR_SCAN(C) , SPACE = ' ';
    int Max = 0 , GRADES_ARR[N]={0} , num=0 ;
    NUM_SCAN(GRADES_ARR,num);
    Max=Maximum(GRADES_ARR,Max);
    HISTOGRAM_PRINTER(GRADES_ARR,Max,CHARACTER,SPACE);
    GRADES_PRINTER(N);
    return 0;

    }

