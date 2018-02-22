#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fx (void *arg)
{
	int *i = (int*) arg;
	printf("thread: i = %d\n", *i);
	return NULL;
}

int main(int argc, char **argv)
{
	// if(argc != 2)
	// {
		// fprintf(stderr, "usage: ./a.out N_threads\n");
		// exit(1);
	// }
	
	int n = atoi(argv[1]);
	int i;
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*n);
	
	
	for(i = 0; i < n; i++)
	{
		fprintf(stderr, "test%d\n", n);
		pthread_create(&threads[i], NULL, fx, (void *)i);
	}

	for(i = 0; i < n; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	
}