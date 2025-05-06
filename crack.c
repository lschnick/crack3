#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

char (*loadFile2D(char *filename, int *size))[HASH_LEN];
char *substringSearch2D(char *target, char (*lines)[HASH_LEN], int size);
int alphabetic(const void *a, const void *b);

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    // TODO: Read the hashes file into an array.
    //   Use either a 2D array or an array of arrays.
    //   Use the loadFile function from fileutil.c
    //   Uncomment the appropriate statement.
    int size, count, length;
    count = 0;
    char (*hashes)[HASH_LEN] = loadFile2D(argv[1], &size); //create 2d array of hashes from hash file
    
    // CHALLENGE1: Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char[HASH_LEN]), alphabetic); //sort list of hashes alphabetically

    // TODO
    // Open the password file for reading.
    // TODO
    char dictln[1000];
    // Open the dictionary file for reading.
    FILE *dictf = fopen(argv[2], "r");
     if (dictf == NULL)
    {
        printf("error with dict file");
        exit(1);
    }

    while ((fgets(dictln, 1000, dictf))!= NULL) //test for eof
    {
        length = strlen(dictln);
        int i = length - 1;
        if ( dictln[i] == '\n') //trim new line char
        {
            dictln[i] = '\0';
        }
        length = strlen(dictln);
        char *hashed = md5(dictln, length); //hash dict word using md5
        char *found = substringSearch2D(hashed, hashes, size); //use strcmp to check for matches
        if (found)
        {
			printf("Found: %s\n", found);
            count++;
        }
		else
        {
			printf("Not found!\n");
        }
    }
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.

    // TODO
    // When done with the file:
    //   Close the file
    fclose(dictf);
    //   Display the number of hashes found.
    printf("Hashes found: %d\n", count);
    //   Free up memory.
    free(hashes);
}

int alphabetic(const void *a, const void *b) //check alphebetic order for qsort
{
    char *aa = (char*)a;
    char *bb = (char*)b;
    return strcmp(aa, bb);
}
