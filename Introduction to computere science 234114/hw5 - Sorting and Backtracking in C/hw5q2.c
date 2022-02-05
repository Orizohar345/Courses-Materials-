#include <stdio.h>
#include <stdlib.h>
void printNumCoinsInputMessage() {
    printf("Please enter coins num:\n");
}

void printCoinValsInputMessage() {
    printf("Please enter coins vals:\n");
}

void printSumInputMessage() {
    printf("Please enter the requested sum:\n");
}

void printLimitInputMessage() {
    printf("Please enter the coins limit:\n");
}

void printAnswerMessage(int n) {
    printf("There are %d possible partitions.\n", n);
}

void printAllocationError() {
    printf("ERROR: allocation failed.\n");
}
int counter(int *arr,int n,int sum, int k ,int initial_sum , int index)
{
    if (initial_sum == sum  )  return 1;
    if ( n==0 || k<=0 || initial_sum > sum || index>=n) return 0 ;
    {
        return counter(arr , n, sum, k-1 , initial_sum+arr[index] ,index) + counter(arr, n, sum, k, initial_sum,index+1);
    }
}
int counting_sums ( int *arr,int n,int sum, int k )
{
    int index=0;
    int initial_sum=0;
    return counter(arr,n,sum,k,index,initial_sum) ;
}
int main() {
    int *coins_arr, coins_num, requested_sum, max ,counter_of_sums ;
    printNumCoinsInputMessage();
    scanf("%d", &coins_num);
    coins_arr = (int *) malloc(coins_num * sizeof(int));
        if (coins_arr == NULL)
        {
            printAllocationError();
            return 1;
        }
        printCoinValsInputMessage();
        for (int i = 0; i < coins_num ; i++) {
            scanf("%d", coins_arr + i);
        }
        printSumInputMessage();
        scanf("%d", &requested_sum);
        printLimitInputMessage();
        scanf("%d", &max);
        counter_of_sums = counting_sums(coins_arr, coins_num, requested_sum , max);
        printAnswerMessage(counter_of_sums);
        free(coins_arr);
        return 0;
    }