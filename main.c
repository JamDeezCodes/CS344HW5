#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct image 
{
	int ***pixels;
	int rows;
	int columns;
	int max_pixel_value;
} image;

void *change_image_to_red (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for
	(	
		row_index = 0; 
		row_index < image_object->rows;
		row_index++
	)
	{
		for
		(
			column_index = 0; 
			column_index < image_object->columns; 
			column_index++
		)
		{
			image_object->pixels[row_index][column_index][1] = 0;
			image_object->pixels[row_index][column_index][2] = 0;
		}
	}
	
	return NULL;
}

void *change_image_to_green (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for
	(	
		row_index = 0; 
		row_index < image_object->rows;
		row_index++
	)
	{
		for
		(
			column_index = 0; 
			column_index < image_object->columns; 
			column_index++
		)
		{
			image_object->pixels[row_index][column_index][0] = 0;
			image_object->pixels[row_index][column_index][2] = 0;
		}
	}
	
	return NULL;
}

void *change_image_to_blue (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for
	(	
		row_index = 0; 
		row_index < image_object->rows;
		row_index++
	)
	{
		for
		(
			column_index = 0; 
			column_index < image_object->columns; 
			column_index++
		)
		{
			image_object->pixels[row_index][column_index][0] = 0;
			image_object->pixels[row_index][column_index][1] = 0;
		}
	}
	
	return NULL;
}

void *invert_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for
	(	
		row_index = 0; 
		row_index < image_object->rows;
		row_index++
	)
	{
		for
		(
			column_index = 0; 
			column_index < image_object->columns; 
			column_index++
		)
		{
			image_object->pixels[row_index][column_index][0] = 
				image_object->max_pixel_value - image_object->pixels[row_index][column_index][0];
			image_object->pixels[row_index][column_index][1] = 
				image_object->max_pixel_value - image_object->pixels[row_index][column_index][1];
			image_object->pixels[row_index][column_index][2] = 
				image_object->max_pixel_value - image_object->pixels[row_index][column_index][2];
		}
	}
	
	return NULL;
}

int main(int argc, char **argv)
{
	if(argc < 3)
	{
		fprintf(stderr, "usage: ./a.out num_threads option [arg]\n");
		exit(1);
	}

	int ***pixels;
	char type[70];;
	int width, height, max_pixel_value;
	int red, blue, green;
	int i, j;
	struct image *image_object = (struct image*) malloc(sizeof(struct image*));
	
	// Read file header from stdin
	fscanf(stdin, "%s", type);
	fscanf(stdin, "%d", &width);
	fscanf(stdin, "%d", &height);
	fscanf(stdin, "%d", &max_pixel_value);
	
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
			fscanf(stdin, "%d", &red);
			fscanf(stdin, "%d", &blue);
			fscanf(stdin, "%d", &green);
			pixels[i][j][0] = red;
			pixels[i][j][1] = blue;
			pixels[i][j][2] = green;
		}
	}
	
	// Perform image processing
	
	image_object->rows = height;
	image_object->columns = width;
	image_object->max_pixel_value = max_pixel_value;	
	image_object->pixels = pixels;	
	
	int number_of_threads = atoi(argv[1]);
	
	//TODO: split rows up according to number_of_threads count
	
	// Handle different kinds of image transformations here
	
	if(strcmp(argv[2], "-red") == 0)
	{
		
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, change_image_to_red, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-blue") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, change_image_to_blue, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-green") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, change_image_to_green, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-L") == 0)
	{
		
	}
	else if(strcmp(argv[2], "-R") == 0)
	{
		
	}
	else if(strcmp(argv[2], "-I") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, invert_image, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-C") == 0)
	{
		float contrast_percentage = atof(argv[3]);
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
	
	free(image_object);
	
	return(0);		
}