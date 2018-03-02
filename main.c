#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct image 
{
	int ***pixels;
	int rows;
	int columns;
	int max_pixel_value;
	int row_to_stop;
	int row_to_begin;
	float contrast_percentage;
} image;

int ***pixels;

void *change_image_to_red (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for
	(	
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
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
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
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
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
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
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
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
	int i, j;
	
	for
	(	
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
		row_index++
	)
	{
		for
		(
			column_index =  image_object->rows-1;	
			column_index > 0;
			column_index -- 
		)
		{
			pixels[row_index][column_index][0] = image_object->pixels[image_object->rows - column_index][row_index][0];
			pixels[row_index][column_index][1] = image_object->pixels[image_object->rows - column_index][row_index][1];
			pixels[row_index][column_index][2] = image_object->pixels[image_object->rows - column_index][row_index][2];
		}
	}
	
	return NULL;
}

void *left_rotate_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	int i, j;
		
	for
	(	
		row_index = image_object->row_to_stop; 
		row_index > image_object->row_to_begin;
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
			pixels[row_index][column_index][0] = image_object->pixels[column_index][row_index][0];
			pixels[row_index][column_index][1] = image_object->pixels[column_index][row_index][1];
			pixels[row_index][column_index][2] = image_object->pixels[column_index][row_index][2];
		}
	}
	
	return NULL;
}

void *contrast_image (void *arg)
{
	struct image *image_object = (struct image*) arg;
	
	int row_index, column_index;
	
	for(row_index = image_object->row_to_begin; row_index < image_object->row_to_stop; row_index++)
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

	// int ***pixels;
	char type[70];;
	int columns, rows, max_pixel_value;
	int red, blue, green;
	int i, j;
	struct image *image_object = (struct image*) malloc(sizeof(struct image*));
	
	// Read file header from stdin
	fscanf(stdin, "%s", type);
	fscanf(stdin, "%d", &columns);
	fscanf(stdin, "%d", &rows);
	fscanf(stdin, "%d", &max_pixel_value);
	
	// Allocate array for pixels
	image_object->pixels = (int ***) malloc(sizeof(int **) * rows);
	for(i = 0; i < rows; i++)
	{
		image_object->pixels[i] = (int **) malloc(sizeof(int *) * columns);
		for(j = 0; j < columns; j++)
		{
			image_object->pixels[i][j] = (int *) malloc(sizeof(int) * 3);
		}
	}
	
	// Store pixel RGB values inside 3D array
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			fscanf(stdin, "%d", &red);
			fscanf(stdin, "%d", &blue);
			fscanf(stdin, "%d", &green);
			image_object->pixels[i][j][0] = red;
			image_object->pixels[i][j][1] = blue;
			image_object->pixels[i][j][2] = green;
		}
	}
	
	// Perform image processing
	image_object->rows = rows;
	image_object->columns = columns;
	image_object->max_pixel_value = max_pixel_value;	
	
	int number_of_threads = atoi(argv[1]);
	
	//TODO: split rows up according to number_of_threads count, last thread gets most responsibility
	int rows_per_thread = (int)image_object->rows/number_of_threads;
	int row_to_begin = 0;
	int row_to_stop = rows_per_thread;
	
	// Handle different kinds of image transformations
	if(strcmp(argv[2], "-red") == 0)
	{
		
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->rows;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			//depending on i, set the row for the thread to start and stop processing the image at
			pthread_create(&threads[i], NULL, change_image_to_red, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-blue") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->rows;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, change_image_to_blue, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-green") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->rows;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, change_image_to_green, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-L") == 0)
	{
		int new_rows = image_object->columns;
		int new_columns = image_object->rows;
		
		rows_per_thread = new_rows/number_of_threads;
		row_to_stop = rows_per_thread;
		
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
				
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->columns-1;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
			
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, left_rotate_image, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}

		//Free old 3D pixel array
		for(i = 0; i < image_object->rows; i++)
		{
			for(j = 0; j < image_object->columns; j++)
			{
				free(image_object->pixels[i][j]);
			}
			free(image_object->pixels[i]);
		}
		
		image_object->pixels = pixels;
		image_object->rows = new_rows;
		image_object->columns = new_columns;
	}
	else if(strcmp(argv[2], "-R") == 0)
	{
		int new_rows = image_object->columns;
		int new_columns = image_object->rows;
		
		rows_per_thread = new_rows/number_of_threads;
		row_to_stop = rows_per_thread;
		
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
				
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->columns-1;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
			
		}
					
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, right_rotate_image, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}

		//Free old 3D pixel array
		for(i = 0; i < image_object->rows; i++)
		{
			for(j = 0; j < image_object->columns; j++)
			{
				free(image_object->pixels[i][j]);
			}
			free(image_object->pixels[i]);
		}
		
		image_object->pixels = pixels;
		image_object->rows = new_rows;
		image_object->columns = new_columns;
	}
	else if(strcmp(argv[2], "-I") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->max_pixel_value = max_pixel_value;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->rows;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, invert_image, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}
	}
	else if(strcmp(argv[2], "-C") == 0)
	{
		float contrast_percentage = atof(argv[3]);
		
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->columns);
			image_objects[i]->contrast_percentage = contrast_percentage;
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->max_pixel_value = max_pixel_value;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			if(i == number_of_threads - 2)
			{
				row_to_stop = image_object->rows;
			}
			else
			{
				row_to_stop += rows_per_thread;
			}

			row_to_begin += rows_per_thread;
		}
		
		for(i = 0; i < number_of_threads; i++)
		{

			pthread_create(&threads[i], NULL, contrast_image, (void *)(image_objects[i]));
		}

		for(i = 0; i < number_of_threads; i++)
		{

			pthread_join(threads[i], NULL);
		}
	}
	
	//Print image to stdout
	printf("%s\n", type);
	printf("%d ", image_object->columns);
	printf("%d\n", image_object->rows);
	printf("%d\n", max_pixel_value);
	
	for(i = 0; i < image_object->rows; i++)
	{
		for(j = 0; j < image_object->columns; j++)
		{
			printf("%d %d %d\n", image_object->pixels[i][j][0], image_object->pixels[i][j][1], image_object->pixels[i][j][2]);
		}
	}
	
	return(0);		
}