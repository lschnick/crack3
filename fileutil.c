#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

char (*loadFile2D(char *filename, int *size))[COLS];
char *substringSearch2D(char *target, char (*lines)[COLS], int size);
void free2D(char (*arr)[COLS]);

char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	//Allocate memory for an 2D array, using COLS as the width.
	char (*strs)[COLS]= malloc(10 * sizeof(char[COLS]));
	// Read the file line by line into a buffer.
	*size = 0;
	char ln[1000]; //buffer line, max 1000 characters
	int rows, i, capacity;
	rows = 0; //counts the rows in use
	capacity = 10; //counts the total rows avalible
	while ((fgets(ln, 1000, in))!= NULL) //tests for eof
    {
        int length = strlen(ln);
        int i = length - 1;
        if ( ln[i] == '\n') //trim new ln character
        {
            ln[i] = '\0';
        }
		//   Trim newline.
		//   Expand array if necessary (realloc).
		if (*size >= capacity)  //tests for max capacity
		{
			capacity = capacity * 1.5; //increaases capacity by %150
			strs = realloc(strs, capacity * sizeof(char[COLS]));
		}
		strcpy(strs[rows], ln); //puts buffer into 2D array
		rows++;
		(*size)++; //notes active rows
	}
	//   Copy each line from the buffer into the array (use strcpy).
    // Close the file.
	fclose(in);
	// The size should be the number of entries in the array.
	
	// Return pointer to the array.
	return strs;
}

// Search the array for the target string.
// Return the found string or NULL if not found.

char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
	int i;
    for (i = 0; i < size; i++) //loop through each row of 2D array for target string
	{
		if (strcmp(lines[i], target) == 0) 
		{
			return lines[i]; //return string if it matches
		}
	}
    return NULL; //else return null
}



void free2D(char (*arr)[COLS])
{
	free(arr); //frees 2D array storage
}
