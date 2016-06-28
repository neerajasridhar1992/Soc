

#include <stdio.h>
#include <pthread.h>

#define MAX 10                                  

int number;                                     

pthread_mutex_t mu= PTHREAD_MUTEX_INITIALIZER;  


void *consumer(void *dummy)
{
  int printed= 0;

  printf("Consumer : \"Hello I am consumer #%ld. Ready to consume numbers"
         " now\"\n", pthread_self());

  while (1)
  {
    pthread_mutex_lock(&mu);
    
    printf("Consumer #%ld : %d\n", pthread_self(), number);
    
    
    pthread_mutex_unlock(&mu);

    
    if (number == MAX)
    {
      printf("Consumer done.. !!\n");
      break;
    }
  }
}


void *producer(void *dummy)
{
  printf("Producer : \"Hello I am producer #%ld. Ready to produce numbers"
         " now\"\n", pthread_self());

  while (1)
  {
    pthread_mutex_lock(&mu);
    number ++;
    printf("Producer : %d\n", number);
   
    if (number != MAX)
   

   
    pthread_mutex_unlock(&mu);

   
    if (number == MAX)
    {
      printf("Producer done.. !!\n");
      
      break;
    }
  }
}

int main()
{
  int rc, i;
  pthread_t t[2];

  number= 0;

  
 
  if ((rc= pthread_create(&t[1], NULL, producer, NULL)))

    printf("Error creating the producer thread..\n");
  if ((rc= pthread_create(&t[0], NULL, consumer, NULL)))
    printf("Entered an error while creating the 1st consumer thread..\n");
  if ((rc= pthread_create(&t[2], NULL, consumer, NULL)))
    printf("Entered an error while creating the 2nd consumer thread..\n");
  
  for (i= 0; i < 2; i ++)
    pthread_join(t[i], NULL);

  printf("Done..\n");
  return number;

}
