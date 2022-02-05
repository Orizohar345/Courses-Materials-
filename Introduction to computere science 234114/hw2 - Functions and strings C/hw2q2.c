#include <stdio.h>
#define N 10
int S_Counter(int S)   // Function for checking the sequnce character's number
{
    int virtual_counter=S;
    int nums_counter=1;
    while (virtual_counter >= 10)
    {
        nums_counter = nums_counter + 1;
        virtual_counter = virtual_counter / 10;
    }
    return nums_counter;
}
int length_adder(int K) // Function that taking the length of the palindrome the the program needs to search
{
    printf("Please enter a length:\n");
    scanf("%d", &K);
    return K;
}
int sequence_adder(int S) // Function that taking the sequence from the account
{
    printf("Please enter a sequence:\n");
    scanf("%d", &S);
    return S;
}
int Success_checker(int palindrome[] , int K , int counter ) // Function to check and print if we found the palindrome
{
    int answer=0;
    if (counter == K / 2) {
        answer = 1;
        printf("The requested palindrome is: ");
        for (int l = 0; l < K; l++) {
            printf("%d", palindrome[l]);
        }
    }
        return answer;
    }
     int main() {
int m = 0, p = 0, K = length_adder(m), S = sequence_adder(p), counter = 0,
        nums_counter = S_Counter(S) , sequence_in_raw[N], palindrome[N];
        for (int i = nums_counter - 1; i >= 0; i--) // Printing the sequence to array
        {
            sequence_in_raw[i] = S % 10;
            S = S / 10;
        }
        for (int first_place = 0; first_place <= (nums_counter - K); first_place++) // Checking the sequence to find palindrome from left to right
        {
            for (int j = 0; j < K; j++) {
                palindrome[j] = sequence_in_raw[first_place + j];
            }
            for (int t = 0 ; t < K / 2; t++)
            {
                if (palindrome[t] == palindrome[K - t - 1]) {
                    counter++;
                }
                if (Success_checker(palindrome, K, counter)==1)
                {
                    return 1;
                }}
         counter = 0;
            }
         printf("There is no such palindrome.");
         return 1; }


