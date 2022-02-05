#include <stdio.h>
#include <stdbool.h>
#define N  4
int is_strong (int mat[N][N] , int raw , int column )      // Function that check if number in the mat bigger than all his neighbor
{
bool left_checker = 0 , right_checker = 0 , up_checker = 0 , down_checker = 0 ;
int  checking_counter = 0 , good_checking = 0  ;
left_checker = !(column == 0) ;
right_checker = !(column == N-1) ;
up_checker = !(raw == 0) ;
down_checker = !(raw == N-1) ;
checking_counter= up_checker + down_checker + left_checker + right_checker ;
good_checking = (mat[raw][column]>mat[raw][column-left_checker]);
good_checking=good_checking+(mat[raw][column]>mat[raw-up_checker][column]);
good_checking=good_checking+(mat[raw][column]>mat[raw+down_checker][column]);
good_checking=good_checking+(mat[raw][column]>mat[raw][column+right_checker]);
bool answer = (good_checking == checking_counter) ;
return (int)answer ;
}
int space_rank (int mat[N][N] , int raw , int column ) // Function that check the diffrence between two numbers
{
    int right = 1 ;
    bool right_checker = column == N-1 ;
    int  check = right - right_checker ;
    int diffrence = mat[raw][column]-mat[raw][column+check] ;
    bool value = (diffrence < 0) ;
    int space = diffrence - 2 * value * diffrence ;
    return space ;
}

int main()
{
    int mat[N][N],i,j,sum = 0,counter =0;
    printf ("Please enter a matrix:\n");  // The account adding number to the math
    for (i=0 ;i < N ;i++)
    {
        for (j=0 ; j<N ; j++ )
        {
            scanf ("%d",&mat[i][j]) ;
        }

    }
    for (i=0 ;i < N ;i++)   // The program searching for any number his space rank the check if he is strong number
    {
        for (j = 0; j < N; j++) {
            int the_space = space_rank(mat, i, j);
            sum += the_space;
            int the_strong = is_strong(mat, i, j);
            counter += the_strong ;
        }
    }
   printf ("Strong elements: %d\nSpace rank: %d",counter,sum );

    return 0;
}
