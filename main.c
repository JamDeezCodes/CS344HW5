#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Define image struct
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
	
	//Iterate through entire array and set blue/green pixel values to zero
	//Start and stop at the assigned row indexes for threading
	for(row_index = image_object->row_to_begin; row_index < image_object->row_to_stop; row_index++)
	{
		for(column_index = 0; column_index < image_object->columns; column_index++)
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
	
	//Iterate through array and set blue/red pixel values to zero
	for(row_index = image_object->row_to_begin; row_index < image_object->row_to_stop; row_index++)
	{
		for(column_index = 0; column_index < image_object->columns; column_index++)
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
	
	//Iterate through entire array and set green/red pixel values to zero
	for(row_index = image_object->row_to_begin; row_index < image_object->row_to_stop; row_index++)
	{
		for(column_index = 0; column_index < image_object->columns; column_index++)
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
	
	//To invert image, subtract existing pixel values for RGB from max_pixel_value
	for(row_index = image_object->row_to_begin; row_index < image_object->row_to_stop; row_index++)
	{
		for(column_index = 0; column_index < image_object->columns; column_index++)
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
	
	//Old bottom row, zeroth column is now zeroth row, zeroth column; manipulate indexes appropriately
	for
	(	
		row_index = image_object->row_to_begin; 
		row_index < image_object->row_to_stop;
		row_index++
	)
	{
		for
		(
			column_index = image_object->rows-1;	
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
		
	//Old zeroth row, final column is new zeroth row, zeroth column; simply read in array to new dimensions by swapping indexes
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
	
	//Manipulate RGB pixel values according to change contrast
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
	
	if(!image_object->pixels)
	{
		fprintf(stderr, "Cannot allocate pixel array\n");
		exit(1);
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
		//Allocate list of threads for splitting up workload according number of threads passed in
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		//Allocate list of image objects for storing which rows a thread must begin and end its work 
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			//Assign necessary attributes to each object 
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
						
			//Every object shares same pixel array
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			image_objects[i]->columns = columns;
			image_objects[i]->row_to_begin = row_to_begin;
			image_objects[i]->row_to_stop = row_to_stop;
			
			//Delegate the workload for each thread
			//If on the last loop iteration, simply have the last thread work on every remaining row in the array
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
		
		//Create threads and assign each image object to be worked on by each thread
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_create(&threads[i], NULL, change_image_to_red, (void *)(image_objects[i]));
		}

		//Join threads after their work is completed
		for(i = 0; i < number_of_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}
		
		free(threads);
	}
	//Rinse and repeat for each processing type
	else if(strcmp(argv[2], "-blue") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
						
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
		
		free(threads);
	}
	else if(strcmp(argv[2], "-green") == 0)
	{
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
			
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
		//Row and column sizes must swap for rotation
		int new_rows = image_object->columns;
		int new_columns = image_object->rows;
		
		//Recalculate rows per thread according to columns size instead
		rows_per_thread = new_rows/number_of_threads;
		row_to_stop = rows_per_thread;
		
		// Allocate new array for pixels with new dimensions
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
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
			
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
		
		//Assign image_object's pixel array to global array with newly rotated image
		image_object->pixels = pixels;
		image_object->rows = new_rows;
		image_object->columns = new_columns;
	}
	else if(strcmp(argv[2], "-R") == 0)
	{
		
		//Perform same operations for right rotation, just use pointer to right rotation method
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
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
			
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
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
			
			image_objects[i]->pixels = image_object->pixels;
			image_objects[i]->rows = rows;
			//Assign max_pixel_value for use in Invert method
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
		
		free(threads);
	}
	else if(strcmp(argv[2], "-C") == 0)
	{
		//Use contrast_percentage and assign while creating each image objects for use during contrast method
		float contrast_percentage = atof(argv[3]);
		
		pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)*number_of_threads);
		
		if(!threads)
		{
			fprintf(stderr, "ERROR: Cannot create threads\n");
		}
		
		struct image **image_objects = (struct image**) malloc(sizeof(struct image*) * number_of_threads);
		
		if(!image_objects)
		{
			fprintf(stderr, "ERROR: Cannot allocate image objects\n");
		}
		
		for(i = 0; i < number_of_threads; i++)
		{
			image_objects[i] = (struct image*) malloc(sizeof(struct image*));
			image_objects[i]->pixels = (int ***) malloc(sizeof(int **) * image_object->rows);
			
			if(!image_objects[i])
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel image object\n");
			}
			
			
			if(!image_objects[i]->pixels)
			{
				fprintf(stderr, "ERROR: Cannot allocate pixel array for image object\n");
			}
			
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
				
		free(threads);
	}
	else
	{
		fprintf(stderr, "FLAGS: -red -green -blue -I -R -L -C P\n");
		exit(1);
	}
	
	//Print image header and pixels to stdout
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
	
	for(i = 0; i < image_object->rows; i++)
	{
		for(j = 0; j < image_object->columns; j++)
		{
			free(image_object->pixels[i][j]);
		}
		free(image_object->pixels[i]);
	}
	
	free(image_object->pixels);
	
	free(image_object);
	
	return(0);		
}