#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

typedef int bool ;
typedef char string;


pthread_mutex_t mutex;
int number_of_lines;
int number_of_employess;
int truck_A_capacity;
int truck_B_capacity;
int number_of_manufactored_producs;
int min_threshold;
int number_of_working_minutes;


long x = 0 ; 
void* routine_thread_test()
{
    pthread_mutex_lock(&mutex);
    for ( int i = 0 ; i < 1000000 ; i++)
         x = x + 5 ;
    pthread_mutex_unlock(&mutex);
}





int main(int argc , char* argv[])
{

    //argument check !! 3 arguments only requiedred 


    if( argc != 3 )
    {
        printf("3 arguments only required !! ");
        exit(1);
    }


    pthread_mutex_init(&mutex , NULL);


    //creating and joining threads lines
    pthread_t lines[5];
    

    for ( int i = 0 ; i <5 ; i++)
    {
        if(pthread_create(&lines[i] , NULL , &routine_thread_test , NULL) != 0 )
        {
            perror("Threads lines Error : ");
            exit(1);
        }

    }
    for ( int i = 0 ; i < 5 ; i++)
    {
        printf("Line %d starts working \n"  , i  );
        if (pthread_join(lines[i], NULL) != 0)
        {
            perror("Failed to join the lines threads ");
            exit(2);
        }
        printf("Line %d done working \n\n"  , i  );
    }


    pthread_mutex_destroy(&mutex);
    printf("threads total working : %ld\n" , x);

    return 0;

}    






int employee_speed_skill()
{
    srand(time());
    int speed ;

    speed = rand() % 30 + 1 ;
    
    return speed ; s

}


 void detergent_manufacturing_process()
 {
     int steps = 0 ; 
     while(steps == 10 )
     {
         return ;
     }
 }


 int factory_A_suppliments()
 {
    int raw_matters;


    return raw_matters;
 }


  int factory_B_suppliments()
 {
    int raw_matters;


    return raw_matters;
 }









 void arguments_file_reader()
 {
     FILE* file_input ; 
     string line_buffer[25];
     char *token;

     if( file_input = fopen("arguments.txt" , "r") == -1 )
     {
         perror("File Error :");
         exit(8);
     }


     while(fgets(line_buffer , 25 , file_input) != NULL )
     {

     }




 }
 






























// if(pthread_create(&line1 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 1 










    // {
    //     perror("Failed to create a  thread 1 ");
    // } 

    // if(pthread_create(&line2 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    // {
    //     perror("Failed to create a  thread 2 ");
    // } 
    //  if(pthread_create(&line3 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    // {
    //     perror("Failed to create a  thread 2 ");
    // } 
    //  if(pthread_create(&line4 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    // {
    //     perror("Failed to create a  thread 2 ");
    // } 
    //  if(pthread_create(&line5 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    // {
    //     perror("Failed to create a  thread 2 ");
    // } 
