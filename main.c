#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fx (void *arg)
{
	int i = (int) arg;
	printf("thread: i = %d\n", i);
	printf("running\n");
	return NULL;
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "usage: ./a.out num_threads option [arg]\n");
		exit(1);
	}

	//Store file in buffer
	
	FILE *imageToProcess;
	imageToProcess = fopen(argv[2], "r");
	
	int ***pixels;
	char type[70];;
	int width, height, maxPixelValue;
	int red, blue, green;
	
	if(!imageToProcess)
	{
		fprintf(stderr, "This CANNAWT Beeee\n");
		exit(1);
	}
	else
	{
		//Store file header
		fscanf(imageToProcess, "%s", type);
		fscanf(imageToProcess, "%d", &width);
		fscanf(imageToProcess, "%d", &height);
		fscanf(imageToProcess, "%d", &maxPixelValue);
		fclose(imageToProcess);
		fprintf(stderr, "type: %s width: %d height: %d maxPixelValue: %d\n", type, width, height, maxPixelValue);
		
	}
	

	



	














	
	// int n = atoi(argv[1]);
	// int i;
	// pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*n);
	
	// for(i = 0; i < n; i++)
	// {
		// printf("main: spawning thread %d..\n", i);
		// pthread_create(&threads[i], NULL, fx, (void *)(i + 1));
	// }

	// for(i = 0; i < n; i++)
	// {
		// printf("main: joining thread %d..\n", i);
		// pthread_join(threads[i], NULL);
	// }
}