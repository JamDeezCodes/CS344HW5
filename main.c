#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct image 
{
	int ***pixels;
	int rows;
	int columns;
	int max_pixel_value;
	float contrast_percentage;
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

void *right_rotate_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	int red_temp, blue_temp, green_temp;
	int i, j, ***pixels;
	
	int new_rows = image_object->columns;
	int new_columns = image_object->rows;
	
	// Allocate new array for pixels
	pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
	for(i = 0; i < image_object->columns; i++)
	{
		pixels[i] = (int **) malloc(sizeof(int *) * image_object->rows);
		for(j = 0; j < image_object->rows; j++)
		{
			pixels[i][j] = (int *) malloc(sizeof(int) * 3);
		}
	}
	
	for
	(	
		row_index = 0; 
		row_index < image_object->columns;
		row_index++
	)
	{
		for
		(
			column_index = (image_object->rows-1);
			column_index > 0;
			column_index--
		)
		{
			
			pixels[row_index][column_index][0] = image_object->pixels[image_object->rows - column_index][row_index][0];
			pixels[row_index][column_index][1] = image_object->pixels[image_object->rows - column_index][row_index][1];
			pixels[row_index][column_index][2] = image_object->pixels[image_object->rows - column_index][row_index][2];
			
		}
	}
	
	image_object->pixels = pixels;
	image_object->rows = new_rows;
	image_object->columns = new_columns;
	
	return NULL;
}

void *left_rotate_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	int red_temp, blue_temp, green_temp;
	int i, j, ***pixels;
	
	int new_rows = image_object->columns;
	int new_columns = image_object->rows;
	
	// Allocate new array for pixels
	pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
	for(i = 0; i < image_object->columns; i++)
	{
		pixels[i] = (int **) malloc(sizeof(int *) * image_object->rows);
		for(j = 0; j < image_object->rows; j++)
		{
			pixels[i][j] = (int *) malloc(sizeof(int) * 3);
		}
	}
	
	for
	(	
		row_index = (image_object->columns-1); 
		row_index > 0;
		row_index--
	)
	{
		for
		(
			column_index = 0;
			column_index < image_object->rows;
			column_index++
		)
		{
			
			pixels[row_index][column_index][0] = image_object->pixels[column_index][image_object->columns - row_index][0];
			pixels[row_index][column_index][1] = image_object->pixels[column_index][image_object->columns - row_index][1];
			pixels[row_index][column_index][2] = image_object->pixels[column_index][image_object->columns - row_index][2];
			
		}
	}
	
	image_object->pixels = pixels;
	image_object->rows = new_rows;
	image_object->columns = new_columns;
	
	return NULL;
}

void *contrast_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for(row_index = 0; row_index < image_object->rows; row_index++)
	{
		for(column_index = 0; column_index < image_object->columns; column_index++)
		{
			if(image_object->pixels[row_index][column_index][0] <= image_object->max_pixel_value/2)
			{
				image_object->pixels[row_index][column_index][0] -= image_object->max_pixel_value*image_object->contrast_percentage;
			}
			else
			{
				image_object->pixels[row_index][column_index][0] += image_object->max_pixel_value*image_object->contrast_percentage;
			}
						
			if(image_object->pixels[row_index][column_index][1] <= image_object->max_pixel_value/2)
			{
				image_object->pixels[row_index][column_index][1] -= image_object->max_pixel_value*image_object->contrast_percentage;
			}
			else
			{
				image_object->pixels[row_index][column_index][1] += image_object->max_pixel_value*image_object->contrast_percentage;
			}
			
			if(image_object->pixels[row_index][column_index][2] <= image_object->max_pixel_value/2)
			{
				image_object->pixels[row_index][column_index][2] -= image_object->max_pixel_value*image_object->contrast_percentage;
			}
			else
			{
				image_object->pixels[row_index][column_index][2] += image_object->max_pixel_value*image_object->contrast_percentage;
			}
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
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, left_rotate_image, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-R") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, right_rotate_image, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
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
		
		image_object->contrast_percentage = contrast_percentage;
		
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, contrast_image, (void *)(image_object));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	
	//Print image to stdout
	
	printf("%s\n", type);
	printf("%d ", width);
	printf("%d\n", height);
	printf("%d\n", max_pixel_value);
	
	
	for(i = 0; i < image_object->rows; i++)
	{
		for(j = 0; j < image_object->columns; j++)
		{
			printf("%d %d %d\n", image_object->pixels[i][j][0], image_object->pixels[i][j][1], image_object->pixels[i][j][2]);
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