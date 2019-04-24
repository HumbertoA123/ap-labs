#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "logger.h"
#define _GNU_SOURCE


int NUM_BUFFERS;
long **buffers;
pthread_mutex_t *mutexes;
long *result;
pthread_t threads[2000];

struct Struct {
	long *matA;
	long *matB;
	size_t rowPos;
	size_t colPos;
	long *result;
};

long *readMatrix(char *filename)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		return NULL;
	}

	long *matrix;
	matrix = (long *)malloc(4000000 * sizeof(long));

	int i = 0;
	while (getline(&line, &len, fp) != -1)
	{
		matrix[i++] = strtol(line, NULL, 10);
	}
	free(line);
	return matrix;
}

long *getCol(int col, long *matrix)
{
	if (col < 0 || col > 2000)
	{
		exit(EXIT_FAILURE);
	}

	long *newcol;
	size_t offset = col - 1;

	newcol = (long *) malloc(2000 * sizeof(long));

	for (int i = 0; i < 2000; i++)
	{
		newcol[i] = matrix[offset];
		offset += 2000;
	}
	return newcol;
}

long *getRow(int row, long *matrix)
{
	if (row < 0 || row > 2000)
	{
		exit(EXIT_FAILURE);
	}

	size_t offset = ((2 * row) - 2) * 1000;
	long *newrow;
	newrow = (long *)malloc(2000 * sizeof(long));

	for (int i = 0; i < 2000; i++)
	{
		newrow[i] = matrix[offset++];
	}
	return newrow;
}

int getLock(void)
{
	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		if (pthread_mutex_trylock(&mutexes[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

int releaseLock(int lock)
{
	if (pthread_mutex_unlock(&mutexes[lock]) == 0)
	{
		return 0;
	}
	return -1;
}

long dotProduct(long *v1, long *v2)
{
	long result = 0;
	for (int i = 0; i < 2000; i++)
	{
		result += v1[i] * v2[i];
	}
	return result;
}

void *threadFunc(void *arg)
{
	struct Struct *data = (struct Struct *)arg;
	long index;
	int lock1, lock2;

	while ((lock1 = getLock()) == -1);
	while ((lock2 = getLock()) == -1);

	buffers[lock1] = getRow(data->rowPos, data->matA);
	buffers[lock2] = getCol(data->colPos, data->matB);
	
	index = ((((data->rowPos - 1) * 2000) + data->colPos) - 1);
	data->result[index] = dotProduct(buffers[lock1], buffers[lock2]);

	free(buffers[lock1]);
	free(buffers[lock2]);
	free(arg);

	while (releaseLock(lock1) != 0);
	while (releaseLock(lock2) != 0);

	return NULL;
}

long *multiply(long *matA, long *matB)
{
	result = (long *)malloc(4000000 * sizeof(long));

	for (size_t i = 0; i < 2000; i++)
	{
		for (size_t j = 0; j < 2000; j++)
		{
			struct Struct *currentStruct;
			currentStruct =
			    (struct Struct *)
			    malloc(sizeof(struct Struct));
			currentStruct->matA = matA;
			currentStruct->matB = matB;
			currentStruct->rowPos = i + 1;
			currentStruct->colPos = j + 1;
			currentStruct->result = result;
			pthread_create(&threads[j], NULL, threadFunc,
				       (void *)currentStruct);
		}

		for (size_t j = 0; j < 2000; j++)
		{
			pthread_join(threads[j], NULL);
		}
	}
	return result;
}

int saveResultMatrix(long *result)
{
	FILE *f = fopen("result.dat", "w");
	if (f == NULL)
	{
		errorf("error: couldn't open/create result.dat\n");
		return -1;
	}

	for (size_t i = 0; i < 4000000; i++)
	{
		fprintf(f, "%ld\n", result[i]);
	}

	fclose(f);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		errorf("Please enter the number of buffers.\n");
		exit(EXIT_FAILURE);
	}
	NUM_BUFFERS = strtol(argv[2], NULL, 10);
	if (NUM_BUFFERS < 10)
	{
		errorf("For the proper functioning of the program please give at least 10 buffers.\n");
		exit(EXIT_FAILURE);
	}

	buffers = (long **)malloc(NUM_BUFFERS * sizeof(long *));
	mutexes = (pthread_mutex_t *) malloc(NUM_BUFFERS * sizeof(pthread_mutex_t));

	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		mutexes[i] = mutex;
		pthread_mutex_init(&mutexes[i], NULL);
	}

	infof("Processing...This will take a while, please wait.\n");

	long *matrixA, *matrixB;
	matrixA = readMatrix("matA.dat");
	matrixB = readMatrix("matB.dat");

	result = multiply(matrixA, matrixB);
	saveResultMatrix(result);
	infof("Matrix multiplication finished succesfully.\n");

	free(matrixA);
	free(matrixB);
	free(buffers);
	free(mutexes);
	free(result);
	return 0;
}