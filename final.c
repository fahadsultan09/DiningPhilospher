#include <pthread.h>	
#include <semaphore.h>	
#include <stdio.h>	
#include <unistd.h>	
#define	N 5	
#define	THINKING 2	
#define	HUNGRY 1	
#define	EATING 0	
#define	LEFT (phnum + 4) % N	
#define	RIGHT (phnum + 1) % N	
		
sem_t p1,p2,p3,p4,p5;	
sem_t f1,f2,f3,f4,f5;	
sem_t mutex;	
	
void putfork(sem_t left,sem_t Right,int	i);			
void pickfork(sem_t left,sem_t Right,int i){	
		
//	sem_wait(&mutex);	
	
	sem_wait(&mutex);
	sem_wait(&left);
	printf("\nPhilosopher %d Picking Left",i);	
	sem_post(&mutex);	
	
	sem_wait(&mutex);
	sem_wait(&Right);	
	printf("\nPhilosopher %d Picking Right",i);		
	printf("\nPhilosopher %d start	Eating",i);				
	sem_post(&mutex);		
	putfork(left,Right,i);	
	
//	sem_post(&mutex);
	
}

void putfork(sem_t left,sem_t Right,int i){	
	
	sem_wait(&mutex);		
	sem_post(&left);	
	sem_post(&Right);	
	printf("\nPhilosopher %d free the chopsticks",i);	
	sem_post(&mutex);
	
}	

void philosopher1(void *ptr){		 	

	//sem_wait(&p1);	
	//sleep(1);		
	pickfork(f1,f5,1);	
	//sem_post(&p1);		
	
}

void philosopher2(void *ptr){		 	
	
	//sem_wait(&p2);	
	pickfork(f2,f1,2);	
	//sem_post(&p2);	
}	

void philosopher3(void *ptr){		 	

	//sem_wait(&p3);	
	pickfork(f3,f2,3);		
	//sem_post(&p3);	
	
	//printf("\nPhilosopher	3	is	free\n\n");	
}	
		
void philosopher4(void *ptr){		 	
	
	//sem_wait(&p4);	
	pickfork(f4,f3,4);	
	//sem_post(&p4);	
	
	//printf("\nPhilosopher	4	is	free\n\n");	
}	
	
void philosopher5(void *ptr){		 	
	
	//sem_wait(&p5);	
	pickfork(f5,f4,5);	
	//sem_post(&p5);		

}	
	
int main(){	
	
	sem_init(&mutex,0,1);	
	sem_init(&p1,0,1);	sem_init(&p2,0,1);	sem_init(&p3,0,1);	sem_init(&p4,0,1);	sem_init(&p5,0,1);
	sem_init(&f1,0,1);	sem_init(&f2,0,1);	sem_init(&f3,0,1);	sem_init(&f4,0,1);	sem_init(&f5,0,1);
	
	pthread_t tid1, tid2, tid3, tid4, tid5;	
	pthread_create(&tid1,NULL,&philosopher1,NULL);	
	pthread_create(&tid2,NULL,&philosopher2,NULL);	 		
	pthread_create(&tid3,NULL,&philosopher3,NULL);	 		
	pthread_create(&tid4,NULL,&philosopher4,NULL);	 		
	pthread_create(&tid5,NULL,&philosopher5,NULL);	 		
	pthread_join(tid1,NULL);	
	pthread_join(tid2,NULL);	
	pthread_join(tid3,NULL);	
	pthread_join(tid4,NULL);	
	pthread_join(tid5,NULL);	
	
	return 0;	
}

