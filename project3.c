#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void* routine_thread_test()
{
    printf("Test from threads\n");
    sleep(3);
    printf("ENDING THREAD\n");

}




int main(int argc , char* argv[])
{
    pthread_t line1; //thread 1 
    pthread_t line2; //thread 2
    pthread_t line3; //thread 3
    pthread_t line4; //thread 4
    pthread_t line5; //thread 5 

    if(pthread_create(&line1 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 1 
    {
        perror("Failed to create a  thread 1 ");
    } 

    if(pthread_create(&line2 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    {
        perror("Failed to create a  thread 2 ");
    } 
     if(pthread_create(&line3 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    {
        perror("Failed to create a  thread 2 ");
    } 
     if(pthread_create(&line4 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    {
        perror("Failed to create a  thread 2 ");
    } 
     if(pthread_create(&line5 , NULL , &routine_thread_test , NULL) != 0 ) // intilizing the thread 2 
    {
        perror("Failed to create a  thread 2 ");
    } 



    pthread_join(line1 , NULL); //wait for the thread 
    pthread_join(line2 , NULL);
    pthread_join(line3 , NULL);
    pthread_join(line4 , NULL);
    pthread_join(line5 , NULL);







    return 0;

}