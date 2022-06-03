#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


void* routine()
{
    printf("Test from threads\n");
    sleep(3);
    printf("ENDING THREAD\n");

}
int main(int argc , char* argv[])
{

    pthread_t t1; //thread 1
    pthread_t t2; //thread 2

    if(pthread_create(&t1 , NULL , &routine , NULL) != 0 ) // intilizing the thread 1 
    {
        perror("Failed to create a  thread 1 ");
    } 


    if(pthread_create(&t2 , NULL , &routine , NULL) != 0 ) // intilizing the thread 2 
    {
        perror("Failed to create a  thread 2 ");
    } 


    pthread_join(t1 , NULL); //wait for the thread 
    pthread_join(t2 , NULL);
    






    return 0;

}