#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define POS 1
#define NEG -1
#define EQ 0
#define LEX 1
#define LET_DIVER 2
#define MAX_LEN 21
int charCompare(char char1 , char char2 ,int rule )
{
    char A=char1;
    char B=char2;

    if (A >='A' && A <='Z') A = A-'A'+'a';
    if (B >='A' && B<='Z') B=B-'A'+'a';
   if ((A<'a' || A>'z') && ( B<'a' || B>'z') && rule ==LET_DIVER) return EQ ;
    if (A > B) return POS;
    else if (A < B) return NEG;
    else return EQ;
}
int lexComapre (char* str1 , char*str2 ,int rule)
{
    int i=0 ;
    while (charCompare(str1[i],str2[i],rule)==EQ && str1[i] != 0 && str2[i] !=0 )
    {
       i++ ;
    }
    if (charCompare(str1[i],str2[i],rule)==POS) return POS;
    else if (charCompare(str1[i],str2[i],rule) == NEG ) return NEG;
    else if  (charCompare(str1[i],str2[i],rule) == EQ ) return EQ;
    else if (strlen(str1) > strlen(str2))  return POS;
    else return NEG;
}
int chrCount (char *str,int rule)
{
    int i = 0;
    int counter = 0;
    int length = (int)strlen(str);
    while (i < length-1)
    {
        int semicounter = 0 ;
        for (int j = i+1 ; j < length; j++)
        {
            if (charCompare(str[i],str[j],rule) != EQ) semicounter++;
        }

        if (semicounter == length-i-1) counter++;

        i++;
    }
    if((str[length-1]>='A' && str[length-1]<='Z') || (str[length-1]>='a' && str[length-1]<='z') ) counter++;
return counter;
}
int letCompare (char* str1,char *str2,int rule)
{
    int arr1 = chrCount(str1,rule);
    int arr2 = chrCount(str2,rule);
    if (arr1>arr2) return POS;
    else if (arr1<arr2) return NEG;
    else return EQ;
}
int compareStrHelper (char *str1, char *str2, int rule)
{

    if (rule==LEX) return lexComapre(str1,str2,rule);
    if (rule==LET_DIVER) return letCompare(str1,str2,rule);
    else exit(1);

}
int compareStr(const char *str1, const char *str2, int rule)
{
return compareStrHelper((char*)str1,(char*)str2,rule);
}
void swap(char *str_arr[] , int i)
{
    char *changer=str_arr[i] ;
    str_arr[i] = str_arr[i+1];
    str_arr[i+1] = changer;
}
void sortStringHelper(char *str_arr[], int n, int rule)
{
  for(int i=0;i<n-1;i++)
  {
      for(int j=0;j<n-i-1;j++)
      {
          if (compareStr(str_arr[j],str_arr[j+1],rule) == POS) swap(str_arr,j);
      }
  }
}
void sortString(const char *str_arr[], int n, int rule)
{
  sortStringHelper((char **) str_arr, n, rule) ;
}
// Print Functions
void printNumStringsInputMessage() {
    printf("Please enter the number of strings:\n");
}

void printStringsInputMessage(int n) {
    printf("Please enter the %d strings:\n", n);
}

void printRuleOfComparisonInputMessage() {
    printf("Please enter the rule of comparison between strings.\n");
    printf("%d: Lexicographic order.\n", LEX);
    printf("%d: By the diversity of letters.\n", LET_DIVER);
}

void printSortedStrings(const char *str_arr[], int n) {
    printf("The sorted strings are:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", str_arr[i]);
    }
}

void printAllocationError() {
    printf("ERROR: allocation failed.\n");
}
int main()
{
    int n,rule;
printNumStringsInputMessage();
    scanf (" %d",&n);
    char**  str_arr=(char**)malloc(n*sizeof(char*)) ;
if (str_arr == NULL)
   {
       printAllocationError();
       return 1;
   }
printStringsInputMessage(n);
for (int i=0;i<n;i++)
{
    str_arr[i] = (char *) malloc(MAX_LEN * sizeof(char)) ;
    if (str_arr[i] == NULL)
    {
        printAllocationError();
        return 1;
    }
    scanf ("%s",str_arr[i]);
}
    printRuleOfComparisonInputMessage();
scanf("%d",&rule);
sortString((const char **) str_arr, n, rule);
printSortedStrings((const char **) str_arr, n);
free(str_arr);
    return 0;
}
