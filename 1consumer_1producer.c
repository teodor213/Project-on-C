// 1 producer 1 consumer without using mutex, spinlock. Race condition was solved by while loops. Later I would upload a version with multiple producers and consumers without mutex and spinlock.
// 1 issue is that if a producer doesnt fill up all the way the memory then the consumer would not consume the memory. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct producer{
	unsigned int stack1[5]; 
	unsigned int stack2[5]; 
	unsigned int stack3[5]; 
}producer;

typedef struct middleman{
	unsigned int availableProd[3], availableCons[3];  
		
}middleman;

typedef struct available_Memory{
	unsigned int availableMemory[3];
	int consumerFlag;
	unsigned int *pointerToMemory[3];
	int fullMemory;
}available_Memory;


void setter(available_Memory am, producer pd){
		
	am.availableMemory[0] = 1;
	am.availableMemory[1] = 1;
	am.availableMemory[2] = 1;
	
	am.pointerToMemory[0] = pd.stack1;
	am.pointerToMemory[1] = pd.stack1;
	am.pointerToMemory[2] = pd.stack1;
	am.consumerFlag = 1;
	
	am.fullMemory = 0;
}

void producer1(void *available_Memory){
	
	int memorySpace = 0, available = 0;
	
	
	for(int c = 0; c != 6; c++){
		
		
		while(am.fullMemory == 3){}
		
		for(; memorySpace != 3; memorySpace++){
			
			if(am.availableMemory[memorySpace] == 1){
				available = 1;
				break;
			}
			
		}
		
		if(available == 1){
			
			am.availableMemory[memorySpace] = 0;
			
			
			for(int j = 0; j != 5; j++){
					am.pointerToMemory[memorySpace][j] = j;
					printf("Producing[%d]:%d\n", memorySpace, pd.stack1[j]);
			}
				am.fullMemory++;
				printf("Produced\n");
				am.consumerFlag = 0;
		}
		else{
			printf("No memory available\n");

		}
		memorySpace = 0;
		available = 0;
	}
}


void consumer1(available_Memory am, producer pd){
	int a = 0, available = 0;
	
	
	
	for(int c = 0; c != 6; c++){
		
		
		while(am.fullMemory == 0){}
		
		while(am.consumerFlag){
		}
		
		for(; a != 3; a++){
			if(am.availableMemory[a] == 0){
				printf("Found available memory for consuming\n");
				available = 1;
				break;
			}
			//printf("Memory[%d] is in status:%d\n", a, am.availableMemory[a] );
		}
		
		if(available){
			for(int j = 0; j!= 5; j++)
				printf("%d\n", pd.stack1[j]);
			printf("Memory:%d consumed\n", a);
			am.availableMemory[a] = 1;
			am.fullMemory--;
		}
		else
			printf("There are no memory available for consuming\n");
		
		a = 0;
		available = 0;
	}
}


int main(void){
	available_Memory am;
	producer pd;
	
	setter(am, pd);
	
	pthread_t producer, consumer;
	
	pthread_create(&producer, NULL, (void*)producer1, available_Memory);
	pthread_create(&consumer, NULL, (void*)consumer1, NULL);
	pthread_join(consumer, NULL); 
	pthread_join(producer, NULL); 
	
	
	
	
	return 0;
}
