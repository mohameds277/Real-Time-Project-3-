#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include <time.h>
#include <math.h>








int detergent_products_threshold;// number of detergent products 
int time_simulation; // time f simulation 
int trucks_A; // Factory A has trucks 
int trucks_B; // Factory B has trucks 
int CA; // capacity of A trucks
int CB; // capacity of B trucks
int detergent_products_in_cartonBox;// number of detergent products in cartonBox
int L3_time_threshold; // the storage employee will become absent for a certain user-defined period of time 
int S_2_of_manufactured_detergents_max; // the storage area S 2 can contain ( maximum threshold)
int S_1_area; // storage s1 area 
int S_2_area;
int S_2_of_manufactured_detergents_min; // the storage area S 2 can contain ( mmin threshold)
int cartons_in_each_trip; // number of cartons in each trip
int unavilible_truck; // truck becomes unavailable for a user-defined period 


pthread_mutex_t unloading;
pthread_mutex_t s1_area_mutexa;
pthread_mutex_t s1_area_mutexb;
pthread_mutex_t s2_area_mutex;
pthread_mutex_t truck_mutex;
pthread_mutex_t mutex_technichal;


pthread_mutex_t truck_mutexA [5];
int trucks_A_arr[5];

pthread_mutex_t truck_mutexB [5];
int trucks_B_arr[5];


pthread_mutex_t mutex;
pthread_mutex_t mutex_l3;


int cartanos_in_each_line[5] = {0,0,0,0,0};
int ready_product_line[5] = {0,0,0,0,0};


int flag_employee = 1 ;
pthread_cond_t cond1;
pthread_cond_t cond_s2;
pthread_cond_t cond_arr[10];
int  thread_ids_employee [10] = {1,2,3,4,5,6,7,8,9,10};  

int flag_ta = 0 ;
int flag_tb = 0 ;
int number_raw_a = 0;
int number_raw_b = 0;


void*  truck_A_fun(void* data);

double a_b_ratio = 0 ;


int size_line[5]; 







void* L_1Emplyees_unloading_B(int id)
{
    //pthread_mutex_lock(&unloading);
    pthread_mutex_lock(&s1_area_mutexb);




    
       while(trucks_B_arr[flag_tb] != 0 ){
           //CA = CA - 5;
           number_raw_b = number_raw_b + 5;
           S_1_area = S_1_area + 5;
           trucks_B_arr[flag_tb] = trucks_B_arr[flag_tb]- 5;
         
    printf("L_1 employee [%d] unload the Truck B[%d] to S_1. so this become as CA: [%d] and S_1: [%d] \n",id,flag_tb,trucks_B_arr[flag_tb],S_1_area); 
      //  pthread_mutex_unlock(&unloading);
        pthread_mutex_unlock(&s1_area_mutexb);
        sleep(2);
    
    }


}



void* L_1Emplyees_unloading_A (int id)
{
    pthread_mutex_lock(&unloading);
    pthread_mutex_lock(&s1_area_mutexa);

    


    
       while(trucks_A_arr[flag_ta] != 0 ){
           //CA = CA - 5;
           number_raw_a = number_raw_a + 5;
           S_1_area = S_1_area + 5;
           trucks_A_arr[flag_ta] = trucks_A_arr[flag_ta]- 5;
         
    printf("L_1 employee [%d] unload the Truck A[%d] to S_1. so this become as CA: [%d] and S_1: [%d] \n",id,flag_ta,trucks_A_arr[flag_ta],S_1_area); 
        pthread_mutex_unlock(&unloading);
        pthread_mutex_unlock(&s1_area_mutexa);
        sleep(2);
    
    }

    


}


void* L_1Emplyees_unloading (int* id)
{
   int th = (int*)id; 
    

    L_1Emplyees_unloading_A(th);
    //sleep(2);

     L_1Emplyees_unloading_B(th);

    
}





void* L_2Emplyees_moving (int id)
{

int line_rad = (int)(0 + (rand() % (5- 0 )));
 pthread_mutex_lock(&s1_area_mutexa);
  

    S_1_area = S_1_area - 5;
    printf("L_2 employee [%d] carry the boxes in S_1 to line [%d].  so this become as S_1_area: [%d]  \n",id,id,S_1_area);

    
    cartanos_in_each_line[id] += 5; 
    
        pthread_mutex_unlock(&s1_area_mutexa);
}








void* L_3Emplyees_moving (int id)
{



    pthread_mutex_lock(&s2_area_mutex);
    L3_time_threshold = 4;

    if(ready_product_line[id] != 0 ){
        
        S_2_area = S_2_area + ready_product_line[id];
        ready_product_line[id] =  ready_product_line[id]--; 
        printf("L_3 employee[%d] start carry the boxes in the end of the line [%d].  so this become as S_2_area: [%d]  \n",id,id,S_2_area);
        pthread_mutex_unlock(&s2_area_mutex);
       sleep(L3_time_threshold);
    }
     
    
  
      
       
      
}


void* Trucks_loading_fun (int* id)
{

unavilible_truck = 5;
cartons_in_each_trip = 0;


pthread_mutex_lock(&truck_mutex);

    if (S_2_area !=0 ){
        cartons_in_each_trip = S_2_area + cartons_in_each_trip ;
        S_2_area = S_2_area - 5;
        printf("Truck of this Factory [%d] is ready and load the boxes.The capacity is : %d \n",id,cartons_in_each_trip);
    }
     

      pthread_mutex_unlock(&truck_mutex);
      sleep(unavilible_truck);
}







int rand_speed =0;

void* lines_fun(int id)
{



            
        if (id == 0){
      
    //printf("Line [%d] starts : -----\n",id);

    for (int i = 0; i < 10; i++)
    {


        rand_speed = (0 + (rand() % (5- 0 )));
        if (i == 0 ){
            if ( number_raw_a < 2)
            {
           printf("Empl#%d: lack in material A \n",i+1);
           

            }else{
                  printf("Empl#%d: Take 2 A ,1 b \n",i);
                     number_raw_a = number_raw_a - 2 ;
                     number_raw_b = number_raw_b -1 ;
                     sleep(rand_speed);
            }
        
        }
        
        else if ( i == 9 ){

        printf("Empl#%d: Put Ready product  \n",i+1);
        ready_product_line[id] = ready_product_line[id] + 1;
        printf("Empl#%d: Ready produts become %d  \n",i+1,ready_product_line[id]);
             sleep(rand_speed);

        }

        else{
            printf("Empl#%d: do  another step  \n",i+1);
            sleep(rand_speed);
            
        } 



    }


        } // end id :0 
       
        else if (id == 1){

           
    //printf(" \t \t \t \t \t  Line [%d] starts : -----\n",id);

    for (int i = 0; i < 10; i++)
    {


        rand_speed = (0 + (rand() % (5- 0 )));
        if (i == 0 ){
            if ( number_raw_a < 2)
            {
           printf("\t \t \t \t \t Empl#%d: lack in material A \n",i+1);
           

            }else{
                  printf("\t \t \t \t \t Empl#%d: Take 2 A ,1 b \n \n",i);
                     number_raw_a = number_raw_a - 2 ;
                     number_raw_b = number_raw_b -1 ;
                     sleep(rand_speed);
            }
        
        }
        
        else if ( i == 9 ){

        printf("\t \t \t \t \t Empl#%d: Put Ready product  \n",i+1);
        ready_product_line[id] = ready_product_line[id] + 1;
        printf("\t \t \t \t \t Empl#%d: Ready produts become %d  \n",i+1,ready_product_line[id]);
             sleep(rand_speed);

        }

        else{
            printf("\t \t \t \t \t Empl#%d: do  another step  \n",i+1);
            sleep(rand_speed);
            
        } 



    }
        
        } //end id 1
        else if(id == 2){
           //  printf(" \t \t \t \t \t \t \t \t \t \t Line [%d] starts : -----\n",id);

    for (int i = 0; i < 10; i++)
    {


        rand_speed = (0 + (rand() % (5- 0 )));
        if (i == 0 ){
            if ( number_raw_a < 2)
            {
           printf("\t \t \t \t \t \t \t \t \t \t Empl#%d: lack in material A \n",i+1);
           

            }else{
                  printf("\t \t \t \t \t \t \t \t \t \t Empl#%d: Take 2 A ,1 b \n \n",i);
                     number_raw_a = number_raw_a - 2 ;
                     number_raw_b = number_raw_b -1 ;
                     sleep(rand_speed);
            }
        
        }
        
        else if ( i == 9 ){

        printf("\t \t \t \t \t \t \t \t \t \t Empl#%d: Put Ready product  \n",i+1);
        ready_product_line[id] = ready_product_line[id] + 1;
        printf("\t \t \t \t \t \t \t \t \t \t Empl#%d: Ready produts become %d  \n",i+1,ready_product_line[id]);
             sleep(rand_speed);

        }

        else{
            printf("\t \t \t \t \t \t \t \t \t \t Empl#%d: do  another step  \n",i+1);
            sleep(rand_speed);
            
        } 



    }
        }
        
        else if(id == 3){
        //printf("\t \t \t \t \t \t \t \t \t \t ");
         //printf("\t \t \t \t \t \t \t \t \t \t Line [%d] starts : -----\n",id);

    for (int i = 0; i < 10; i++)
    {


        rand_speed = (0 + (rand() % (5- 0 )));
        if (i == 0 ){
            if ( number_raw_a < 2)
            {
           printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: lack in material A \n",i+1);
           

            }else{
                  printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: Take 2 A ,1 b \n \n",i);
                     number_raw_a = number_raw_a - 2 ;
                     number_raw_b = number_raw_b -1 ;
                     sleep(rand_speed);
            }
        
        }
        
        else if ( i == 9 ){
            
           
        printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: Put Ready product  \n",i+1);
        ready_product_line[id] = ready_product_line[id] + 1;
        printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: Ready produts become %d  \n",i+1,ready_product_line[id]);
             sleep(rand_speed);

        }

        else{
            printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: do  another step  \n",i+1);
            sleep(rand_speed);
            
        } 



    }


        }
        else{
          
    for (int i = 0; i < 10; i++)
    {


        rand_speed = (0 + (rand() % (5- 0 )));
        if (i == 0 ){
            if ( number_raw_a < 2)
            {
           printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t  Empl#%d: lack in material A \n",i+1);
           

            }else{
                  printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t Empl#%d: Take 2 A ,1 b \n\n",i);
                     number_raw_a = number_raw_a - 2 ;
                     number_raw_b = number_raw_b -1 ;
                     sleep(rand_speed);
            }
        
        }
        
        else if ( i == 9 ){

        printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t Empl#%d: Put Ready product  \n",i+1);
        ready_product_line[id] = ready_product_line[id] + 1;
         printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t Empl#%d: Ready produts become %d  \n",i+1,ready_product_line[id]);
             sleep(rand_speed);

        }

        else{
            printf("\t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t \t Empl#%d: do  another step  \n",i+1);
            sleep(rand_speed);
            
        } 



    }

        }


    
            

        

  
} // end lines function 










int main(int argc , char* argv[])
{

 printf(" \n ************** Simulation of Detergent Factory ************** \n\n");
   fflush(stdout);

    trucks_A = 5;
    trucks_B = 6;

    S_2_of_manufactured_detergents_max = 30;
    S_2_of_manufactured_detergents_min = 3;

    
    CA = 30;
    CB = 25;
    
    
    S_1_area = 0 ;
    time_simulation = 10 ; 
    cartons_in_each_trip = 5;
    

	detergent_products_in_cartonBox = 0 ;
	detergent_products_threshold = 50 ;
	
	

	
	
while ( detergent_products_in_cartonBox < detergent_products_threshold  ){
	


  
  //--------------------------------SimulatION OF Factory A and B 
    
    trucks_A_arr[flag_ta] = CA;
    trucks_B_arr[flag_tb] = CB;


    printf("// Trucks of Factory \n\n");
    printf("Truck A [%d] is arrived and ready to unloaded. the capacity is %d  \n",flag_ta,CA);
    printf("Truck B [%d] is arrived and ready to unloaded. the capacity is %d  \n",flag_tb,CB);


	
	// -------------------------employees loading L_1 

	printf("\nL_1 Employees unloading the A and B to Storge Area S_1 \n");
	
	
	  pthread_t L_1[5];
	for ( int i = 0 ; i <5 ; i++)
        {
        if(pthread_create(&L_1[i] , NULL , &L_1Emplyees_unloading, i) != 0 )
        {
            perror("Threads lines Error : ");
            exit(1);
        }
          //  printf("thread [%d]  ::: CA : , ",i,CA);     

    }
    
    
    
    
    for ( int i = 0 ; i < 5 ; i++)
    {
        //printf("L_1 [%d] starts working \n"  , i  );
        if (pthread_join(L_1[i], NULL) != 0)
        {
            perror("Failed to join the L_1 threads ");
            exit(2);
        }
      // printf("L_1 [%d] derement the CA and become [%d] \n",i,CA);  
        printf("L_1 [%d] done working \n"  , i  );
    }

printf("\n");
// ----------------------------------------------		
    


// -------------------------employees loading L_2 

pthread_t L_2[5];
    

    for ( int i = 0 ; i <5 ; i++)
    {
        if(pthread_create(&L_2[i] , NULL , &L_2Emplyees_moving  , i) != 0 )
        {
            perror("L_2 threads Error : ");
            exit(1);
        }

    }
    for ( int i = 0 ; i < 5 ; i++)
    {
        //printf("L_2 [%d]   starts working \n"  , i);
        if (pthread_join(L_2[i], NULL) != 0)
        {
            perror("Failed to join the L_2 threads ");
            exit(2);
        }
        printf("L_2 [%d] done working \n"  , i  );
    }
printf("\n");
// ----------------------------------------------		







// -------------------------Lines
printf(" // Lines as : \n");

printf("line 0 \t \t \t \t \t line 1 \t \t \t \t \t line 2 \t \t \t \t \t line 3 \t \t \t \t line 4\n");
pthread_t lines[5];
    

    for ( int i = 0 ; i <5 ; i++)
    {
        if(pthread_create(&lines[i] , NULL , &lines_fun , i) != 0 )
        {
            perror("Threads lines Error : ");
            exit(1);
        }
        
        
        
        
    }
    for ( int i = 0 ; i < 5 ; i++)
    {
       // printf("Line [%d]  has [%d] cartones starts working \n"  , i,cartanos_in_each_line[i]  );
        if (pthread_join(lines[i], NULL) != 0)
        {
            perror("Failed to join the lines threads ");
            exit(2);
        }
        printf("Line [%d] done working \n"  , i  );
    }


int r=0 ;
r =number_raw_a / number_raw_b ;

if ( r < 2)
        {
             printf("Ratio is <2  : %d then waitin to \n",r);


        }else{
            printf("Ratio is exceedds,then waitin to \n");
            pthread_cond_wait(&cond1,&mutex);
        }
    


    // ----------------------------------------------
    
    
   
    
  // -------------------------employees loading L_3  
printf("\n");    
pthread_t L_3[5];
    



    for ( int i = 0 ; i <5 ; i++)
    {
        if(pthread_create(&L_3[i] , NULL , &L_3Emplyees_moving  , i) != 0 )
        {
            perror("L_3 Threads lines Error : ");
            exit(1);
        }

    }
    for ( int i = 0 ; i < 5 ; i++)
    {
        //printf("L_3 [%d]   starts working \n"  , i);
        if (pthread_join(L_3[i], NULL) != 0)
        {
            perror("Failed to join the L_3 threads ");
            exit(2);
        }
        printf("L_3 [%d] done working \n"  , i  );
    }
printf("\n");    
    // ----------------------------------------------
    
    detergent_products_in_cartonBox = detergent_products_in_cartonBox + S_2_area;


    
    



// loading to truck 


    if ( S_2_area > S_2_of_manufactured_detergents_min && S_2_area < S_2_of_manufactured_detergents_max){


// -------------------------Trucks_loading  
printf("\n");    
pthread_t Trucks_loading[5];
    



    for ( int i = 0 ; i <5 ; i++)
    {
        if(pthread_create(&Trucks_loading[i] , NULL , &Trucks_loading_fun  , i) != 0 )
        {
            perror("Trucks_loading Threads lines Error : ");
            exit(1);
        }

    }
    for ( int i = 0 ; i < 5 ; i++)
    {
        //printf("Trucks_loading [%d]   starts working \n"  , i);
        if (pthread_join(Trucks_loading[i], NULL) != 0)
        {
            perror("Failed to join the lines threads ");
            exit(2);
        }
        printf("Trucks_loading [%d] done working \n"  , i  );
    }
printf("\n");      
    
  // ----------------------------------------------
    


    }else{
        printf("waiting S2_area become between min and max thershold  \n");
        pthread_cond_wait(&cond_s2,&s2_area_mutex);
    }

    





    
    
    if(flag_ta < 5)
    flag_ta++;
    else
    flag_ta = 0;

    if(flag_tb < 5)
    flag_tb++;
    else
    flag_tb = 0;


    
    
    


    
   }// end simulation 
   
   
   printf("The simulation is end and  the Detergent products is %d: \n",detergent_products_in_cartonBox);
   printf("The simulation is end since time solution is ended : \n");
    
    
    
    



    return 0;

}


























