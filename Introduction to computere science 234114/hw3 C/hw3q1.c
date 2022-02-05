#include <stdio.h>
#include <stdbool.h>

#define N 11
// Print welcome message and get the board's size
// 5 Lines
int Welcome_message()
{
    int size=0;
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
    printf("Please enter board size (1 to %d):\n", N);
    scanf(" %d", &size);
    return size;
}
// Initializing the board with "_"
// 3 Lines
void Initial_board(char Board[N][N] , int size )
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size ; j++)
        {
          Board[i][j]='_';
        }
    }
}
// Print the board
// 8 Lines
void print_board(char Board[N][N] , int size , int player_index)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < size; i++)
    {
        printf("|");
        for (int j = 0; j < size; j++)
        {
            printf("%c|", Board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}
//Check if there is a combo of same sign per column
// 10 Lines
bool scan_column(char Board[N][N] , int size)
{
    int counter1=0;
    bool answer = false;
    for (int i = 0; i<size;i++) {
        for (int j = 0; j < size-1 ; j++) {
            if ((Board[j][i] == Board[j + 1][i]) && (Board[j][i] != '_'))
                counter1++;
        }

        if (counter1 == size - 1)
        {
            answer = true;
        }
        counter1 = 0;
    }
    return answer;
}
//Check if there is a combo of same sign per raw
// 10 Lines
bool scan_raw(char Board[N][N] , int size)
{
    int counter2 = 0;
    bool answer = false;
    for (int i = 0; i < size ; i++) {
        for (int j = 0; j < size-1 ; j++) {
            if (Board[i][j] == Board[i][j + 1] && Board[i][j] != '_')
                counter2++;
        }
        if (counter2 == size - 1)
        {
            answer = true;
        }
        counter2 = 0;
    }
    return answer;
}
//Check if there is a combo of same sign cross
// 12 Lines
bool scan_cross(char Board [N][N], int size )
{
   int counter3=0 , counter4=0;
    bool answer = false;
    for (int i = 0; i < size - 1; i++)
    {
        if (Board[i][i] == Board[i + 1][i + 1] && Board[i][i] !='_')
            counter3++;
    }
    if (counter3 == size-1)
        answer =true;

    for (int i = size -1 ; i>0 ; i--)
    {
        if (Board[i][size-i-1] == Board[i - 1][size-i] && Board[i][size-i-1] !='_' )
            counter4++;
    }
    if ( counter4 == size-1) answer = true;
    return answer;
}
// Check if any of the players won the game
// 3 Lines
bool check_game_status(char Board[N][N] , int size )
{
    if (scan_raw(Board, size) == true || scan_column(Board, size)== true || scan_cross(Board,size) == true)
    {
        return true ;
    }
    else {
        return false ;
    }
}
// Changing player and the sign he use
// 4 Lines
void change_player(int *player_number , char*player_sign)
{
    *player_number=3-*player_number;
    if(*player_number==1)
        *player_sign='X';
    else
        *player_sign = 'O';
}
// Filling the board
// 3 Lines
void fill_board(char board[N][N],char* board_memory[N*N], char player_sign , int* ptr_counter , int raw , int column )
{
    board[raw-1][column-1]=player_sign;

    board_memory[*ptr_counter]=&board[raw-1][column-1];
    *ptr_counter = *ptr_counter + 1;
}
// Undo player move
//10 Lines
bool undo(int *raw , char *board_memory[N*N] , int *ptr_counter ) // 10 Lines
{
    *raw = -1 * *raw;
    if (*raw % 2 != 0 && *ptr_counter >= *raw) {
        for (int i = 0; i < *raw; i++) {
            *board_memory[*ptr_counter - i - 1] = '_';
        }
        *ptr_counter = *ptr_counter - *raw;
        *raw= -1 ;
        return true ;
    }
    else{
        *raw=-1;
        return false ;
    }
}
// Operating the player's move
// 12 Lines
void player_turn(char board[N][N] , int size ,int *ptr_counter , char* board_memory[N*N] , char player_sign )
{
    int raw=0 , column=0;
    bool move_complete = false;
    while (move_complete == false)
    {
      scanf("%d", &raw) ;
        if (raw < 0)
        {
                move_complete = undo(&raw, board_memory,ptr_counter );
            }
        if (raw >= 0)
        {
            scanf("%d", &column);
            if (raw > 0 && raw <= size && column <= size && column > 0 && board[raw - 1][column - 1] == '_')
                {
                    fill_board(board, board_memory, player_sign, ptr_counter , raw, column);
                    move_complete = true;
                }
            }
        if (move_complete == false) printf ("Illegal move!!!, please try again:\n");
        }
    }
    // Print that's a tie and end the game
    // 8 Lines
    void Tie(char Board[N][N],int size )
        {
            printf("\nCurrent board:\n");
            for (int i = 0; i < size; i++)
            {
                printf("|");
                for (int j = 0; j < size; j++)
                {
                    printf("%c|", Board[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        printf("It's a tie!\n");
}
// Print the who is the winner and end the game
// 8 Lines
    void Win(char board[N][N],int size,int player_index ) //9 Lines
    {
            printf("\nCurrent board:\n");
            for (int i = 0; i < size; i++)
            {
                printf("|");
                for (int j = 0; j < size; j++)
                {
                    printf("%c|", board[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        printf("Player %d Wins! Hooray!\n", player_index);
        }
    int main() // 13 Lines
    {

        char Board[N][N], Player_sign = 'X', *Board_memory[N * N];
        int Player_index = 1, counter = 0 , Game_over = 0 ;
        int size = Welcome_message();
        Initial_board(Board, size);
        while (!((bool)Game_over) && (counter != (size*size) ) )
        {
            print_board(Board, size , Player_index);
            player_turn(Board, size, &counter, Board_memory, Player_sign);
            change_player(&Player_index, &Player_sign);
            Game_over = check_game_status(Board, size);
        }
        if ( Game_over == true)
        {
            Win(Board, size, Player_index);
        }
        else {
            Tie(Board , size );
        }
        return 0;
    }
