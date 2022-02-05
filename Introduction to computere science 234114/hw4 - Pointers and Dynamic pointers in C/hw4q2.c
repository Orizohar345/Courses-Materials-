#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX 32
#define NOUN_DIC_LEN 6
#define VERB_DIC_LEN 5
#define ADJ_DIC_LEN 6
#define TWO 2
#define ONE 1
#define EMPTY '\0'
#define DOT '.'
char char_capital_to_small(char word);
void print_stats(int num_of_nouns, int num_of_verbs, int num_of_adjs );
void string_capital_to_small(char* str);
int char_finder(char* str ,int index );
void fill_string_array(char* str1,char* str2,int n);
void init(char str[],int n);
bool is_suffix_in_dict(char *str, char *dict[], int n);
bool read_sentence(char *noun_suffixes[], int noun_suffixes_len,char *verb_suffixes[], int verb_suffixes_len,char *adj_suffixes[], int adj_suffixes_len,int *num_of_nouns, int *num_of_verbs, int *num_of_adjs);


char char_capital_to_small(char word)
{

    if (word<='Z' && word>='A')
    {
        word =  (char)(word-'A' +'a');
    }
    return word;
}
void string_capital_to_small(char* str)
{
    for (int i=0 ; i<MAX; i++)
    {
        str[i]= char_capital_to_small(str[i]);
    }
}
int char_finder(char* str ,int index )
{
    bool answer = false;
    while (answer == false && index > 0 )
    {
        index--;
        if ((str[index] >= 'a' && str[index] <= 'z') || (str[index] >= 'A' && str[index] <= 'Z'))
        {
         answer=true;
        }
    }
    return index ;
}
void fill_string_array(char* str1,char* str2,int n)
{
    int good_index=MAX;
    for (int i=0;i<n;i++)
    {
        good_index=char_finder(str1,good_index);
        str2[i]=str1[good_index];
    }
}
void init(char str[],int n)
{
    for (int i=0 ; i<n; i++)
    {
        str[i]='\0';
    }
}
bool is_suffix_in_dict(char *str, char *dict[], int n)
{

    int l=0 , r=n-1 , m;
    while(l<=r)
    {
        m=(l+r)/TWO;
       int length=(int)strlen(dict[m]);
        char checker[MAX];
        m=(l+r)/TWO;
        init(checker,MAX);
        fill_string_array(str,checker,length);
        string_capital_to_small(checker);
        if(strcmp(dict[m],checker)>0) r=m-1;
        else if ((strcmp(dict[m],checker)<0)) l=m+1;
        else return true ;
    }
    return false;
}
bool read_sentence(char *noun_suffixes[], int noun_suffixes_len,char *verb_suffixes[], int verb_suffixes_len,char *adj_suffixes[], int adj_suffixes_len,int *num_of_nouns, int *num_of_verbs, int *num_of_adjs)
{
        bool scanstatus = false;
        int checker;
        char word[MAX];
        init(word,MAX);
        while (scanstatus==false)
    {
            init(word,MAX);
        if(scanf(" %s",word) == EOF) return false;
        checker=(int)strlen(word);
        for(int i = 0; i<checker ; i++)
        {
            if ( word[i] == DOT)
            {
                scanstatus = true;
                word[i]=EMPTY ;
                break;
            }
        }
        if(is_suffix_in_dict(word,noun_suffixes,noun_suffixes_len))  *num_of_nouns=*num_of_nouns+1;
       if(is_suffix_in_dict(word, verb_suffixes,verb_suffixes_len))  *num_of_verbs=*num_of_verbs+1 ;
       if(is_suffix_in_dict(word, adj_suffixes,adj_suffixes_len)) *num_of_adjs=*num_of_adjs+1;
    }
    print_stats(*num_of_nouns,*num_of_verbs,*num_of_adjs);
    return true ;
}
void print_stats(int num_of_nouns, int num_of_verbs, int num_of_adjs )
{
    printf("The sentence had %d special nouns, %d special verbs and %d special adjectives.\n",
           num_of_nouns, num_of_verbs, num_of_adjs);
}
int main()
{
    bool answer=true;
        char *noun_suffixes[] = {"msi", "re", "sci", "ssen", "tnem", "tsi"};
        char *verb_suffixes[] = {"de", "eta", "ezi", "gni", "yfi"};
        char *adj_suffixes[] = {"elba", "evi", "hsi", "la", "luf", "suo"};
    printf("Enter text to analyze:\n");
while(answer==true)
    {
        int  num_of_verbs=0,num_of_adjs=0,num_of_nouns=0;
        answer=read_sentence(noun_suffixes,NOUN_DIC_LEN,verb_suffixes,VERB_DIC_LEN,adj_suffixes,ADJ_DIC_LEN,&num_of_nouns,&num_of_verbs,&num_of_adjs);

    }
        return 0;
    }
