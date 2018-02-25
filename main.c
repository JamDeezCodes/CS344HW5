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
	if(argc != 4)
	{
		fprintf(stderr, "usage: ./a.out num_threads option [arg]\n");
		exit(1);
	}

	int ***pixels;
	char type[70];;
	int width, height, max_pixel_value;
	int red, blue, green;
	int i, j;
	
	//Store file in buffer
	
	FILE *image_to_process;
	image_to_process = fopen(argv[3], "r");
	
	if(!image_to_process)
	{
		fprintf(stderr, "This CANNAWT Beeee\n");
		exit(1);
	}
	else
	{
		// Store file header
		fscanf(image_to_process, "%s", type);
		fscanf(image_to_process, "%d", &width);
		fscanf(image_to_process, "%d", &height);
		fscanf(image_to_process, "%d", &max_pixel_value);
		
		// Allocate array for pixels
		pixels = (int ***) malloc(sizeof(int **) * height);
		for(i = 0; i < height; i++)
		{
			pixels[i] = (int **) malloc(sizeof(int *) * width);
			for(j = 0; j < width; j++)
			{
				pixels[i][j] = (int *) malloc(sizeof(int) * 3);
			}
		}
		
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				fscanf(image_to_process, "%d", &red);
				fscanf(image_to_process, "%d", &blue);
				fscanf(image_to_process, "%d", &green);
				pixels[i][j][0] = red;
				pixels[i][j][1] = blue;
				pixels[i][j][2] = green;
			}
		}
		
		// Perform image processing
		
		int number_of_threads = atoi(argv[1]);
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			printf("main: spawning thread %d..\n", i);
			pthread_create(&threads[i], NULL, fx, (void *)(i + 1));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			printf("main: joining thread %d..\n", i);
			pthread_join(threads[i], NULL);
		}
		
		//Print image to stdout
		
		printf("%s\n", type);
		printf("%d ", width);
		printf("%d\n", height);
		printf("%d\n", max_pixel_value);
		
		
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				printf("%d %d %d\n", pixels[i][j][0], pixels[i][j][1], pixels[i][j][2]);
			}
		}
		
		for(i = 0; i < height; i++)
		{
			for(j = 0; j < width; j++)
			{
				free(pixels[i][j]);
			}
			free(pixels[i]);
		}
		
		free(pixels);
		
		fclose(image_to_process);
		
	}
	
}