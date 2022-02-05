#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STUDENTS 10
#define MAX_NAME 100
#define INFO 2
#define INIT 100
#define ADD 200
#define DEL 300
#define SUCCESS 0
#define FAILURE -1

void init_db(int students_info[][INFO], char* students_names[], int n);
int read_students_info(int students_info[][INFO], char* students_names[], int n);
void add_student(int students_info[][INFO], char* students_names[],int n);
void delete_student(int students_info[][INFO], char* students_names[],int n);
void clean_db(char* students_names[],int n);

void init_db(int students_info[][INFO], char* students_names[], int n){
    int i=0;
    while (i<n)
    {
        students_names[i] = SUCCESS;
        for (int j=0 ; j<INFO;j++)
        {
            students_info[i][j]=FAILURE;
        }
        i++;
    }
}
int read_students_info(int students_info[][INFO], char* students_names[], int n)
{
    int M;
    scanf(" %d",&M);
   if (M>n)
   {
       printf ("Too many students!! Aborting!!\n");
       return -1;
   }
   for (int i=0 ; i<M; i++ )
   {
       char name[MAX_NAME];
       scanf(" %s",name);
      int counter=0;
       while (name[counter])
       {
           counter++;
       }
       students_names[i]  = (char*)malloc(counter+1 * sizeof(char) );
       strcpy(students_names[i],name);
for (int j=0;j<INFO;j++)
{
  scanf(" %d",&students_info[i][j]);

}
}
    printf ("First %d students were added to the database!!\n",M);
   return 0;
}
void add_student(int students_info[][INFO], char* students_names[],int n)
{
    int data[INFO], counter = SUCCESS , empty =0 ;
    char name[MAX_NAME];
    scanf(" %s",name);
    for (int j = 0; j < INFO; j++)
    {

        scanf(" %d", &data[j]);

    }
for (int i=0 ; i<n ; i++)
{
  if (data[SUCCESS] == students_info[i][SUCCESS])
  {
    printf ("Student %d already exists!!\n",data[SUCCESS]);
    return ;
  }
    if(students_info[i][SUCCESS] != FAILURE) counter++;
    else empty =i ;
}
    if (counter == n)
    {
        printf ("Cannot add student %d, class already full!!\n",data[SUCCESS]);
        return ;
    }
    else
    {
        students_names[empty]=(char*)malloc((strlen(name))*sizeof(char));
        students_names[empty]=name;
        for (int j = 0; j < INFO; j++)
        {

            students_info[empty][j]=data[j];
        }
      printf ("Student %d was successfully added to the system!!\n",data[SUCCESS]);
        return;
    }
}
void delete_student(int students_info[][INFO], char* students_names[],int n)
{
    int id;
    scanf (("%d"),&id);
    for (int i=0; i<n;i++)
    {
     if (students_info[i][SUCCESS]==id)
     {
         students_names[i]=NULL;
        free(students_names[i]);
         for (int j = 0; j < INFO; j++)
         {

             students_info[i][j]=-1;
         }
         printf("Student %d information were deleted from the system!!!\n",id);
         return;
     }
    }
printf ("Student %d does not exist!!!\n",id) ;
}
void clean_db(char* students_names[],int n)
{
    int counter=0;
    for (int i=0;i<n;i++) {
    if (students_names[i] != NULL)
        {
            counter++;
            students_names[i]=NULL;
            free(students_names[i]);
        }
    }
    printf("All %d entries were deleted!!!\n",counter);
     }
/* main Function */
int main()
{
    int students_info[MAX_STUDENTS][INFO];
    char* students_names[MAX_STUDENTS];
    init_db(students_info, students_names,MAX_STUDENTS);
    int op = INIT;
    while (scanf("%d", &op) != EOF )
    {

        switch(op){
            case INIT: if (read_students_info(students_info, students_names,MAX_STUDENTS )!= SUCCESS){return FAILURE;} break;
            case ADD: add_student(students_info, students_names,MAX_STUDENTS); break;
            case DEL: delete_student(students_info, students_names,MAX_STUDENTS); break;
            default: break;
        }
    }
    clean_db(students_names,MAX_STUDENTS);
    return 0;
}