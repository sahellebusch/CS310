#include <stdio.h>
#include <string.h> 
#define MAX_CHARS 21
#define MAX_WORDS 10
typedef unsigned int uint;

void insertionSort( char arrayOfWords[][MAX_CHARS], uint );
int main (void )
{
	char arrayOfWords[MAX_WORDS][MAX_CHARS];
	uint index = 0;
	uint k;
	
	printf("Please enter up to ten words to be sorted.\n");
	printf("Enter a period by itself to terminate the list.\n");
	while( index < MAX_WORDS && arrayOfWords[index][MAX_CHARS] != '.' )
	{	
		index++;
		if( index < MAX_WORDS )
		{
			scanf( "%s", &arrayOfWords[index][MAX_CHARS] );
			printf("%s\n", &arrayOfWords[index][MAX_CHARS] );
		}
	}
	
	for( k = 0; k <= index-1; k++)
	{
		printf("%s\n", &arrayOfWords[k][MAX_CHARS]);
	}
	insertionSort( arrayOfWords, index );
	for( k = 0; k <= index; k++)
	{
		printf("%s \n", &arrayOfWords[k][MAX_CHARS]);
	}
	
	
	return 0;
}

void insertionSort( char array[][MAX_CHARS], uint index )
{
	char temp[1][MAX_CHARS];
	if( (index - 1) >= 2 )
	{
		uint i;
		uint j;
		for( i = 1; i <= index - 1; i++ )
		{
			temp[0][MAX_CHARS] = array[i][MAX_CHARS];
			j = i;
			while( strcmp(&temp[0][MAX_CHARS], &array[j][MAX_CHARS])> 0 
				   && j >= 0 )
			{
				array[j+1][MAX_CHARS] = array[j][MAX_CHARS];
				j = j-1;
			}
			array[j+1][MAX_CHARS] = temp[0][MAX_CHARS];
		}
	}
}		
	

















