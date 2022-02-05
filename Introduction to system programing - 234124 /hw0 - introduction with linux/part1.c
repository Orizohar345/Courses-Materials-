#include <stdio.h>
#include <stdlib.h>
int inputFun();
int* arrayBuild(int a);
void getNumbers(int *arr , int amount_of_numbers);
void arrayDestroy (int* arr);
int check2Exponenet(int specific_number);
void checkAndSumPowers(int *arr , int amount_of_numbers);
int inputFun()
{
    int amount_of_numbers ;
    printf ("Enter size of input:\n");
    scanf ("%d", &amount_of_numbers);
    if (amount_of_numbers<=0)
    {
        printf("Invalid size\n");
        exit (1);
    }
    else return amount_of_numbers;
}
int* arrayBuild(int amount_of_numbers){
    int* arr = (int*) malloc(amount_of_numbers*sizeof(int));
    if (arr==NULL) exit(1);
    return arr ;
}
void arrayDestroy (int* arr)
{
    free(arr);
}
void getNumbers(int *arr , int amount_of_numbers)
{
    printf ("Enter numbers:\n");
    for (
            int i = 0;
            i<amount_of_numbers;
            i++)
    {
        int specific_number;
        if (scanf ("%d",&specific_number)==0)
        {
            printf("Invalid number\n");
            exit(1);
        }
        arr[i]=specific_number;
    }
}
int check2Exponenet(int specific_number)
{
    int exponent=0;
    if(specific_number==0) return -1;
    while (specific_number != 1)
    {
        if (specific_number%2==0)
        {
            specific_number=specific_number/2 ;
            exponent++;
        }
        else return -1;
    }
    return exponent;
}
void checkAndSumPowers(int *arr , int amount_of_numbers)
{
    int sum_of_powers = 0;
    for (int i=0 ; i<amount_of_numbers ;i++)
    {
        int power = check2Exponenet(arr[i]);
        if (power>=0) {
            printf("The number %d is a power of 2: %d = 2^%d\n", arr[i], arr[i], power);
            sum_of_powers = sum_of_powers + power;
        }

    }
    printf ("Total exponent sum is %d\n",sum_of_powers);
}
int main() {
    int amout_of_numbers=inputFun();
    int* arr= arrayBuild(amout_of_numbers);
    getNumbers(arr,amout_of_numbers);
    checkAndSumPowers(arr,amout_of_numbers);
    arrayDestroy(arr);
    return 0;
}
