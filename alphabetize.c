/* Sean Hellebusch
 * This program allows the user to enter up to 10 words
 * to be alphebetized and returned to the screen.
 */
#include<stdio.h>
#include<string.h>
#define MAX_WORDS 10
#define MAX_WORD_SIZE 21
typedef unsigned int uint;

int main( void )
{

	char arrayOfWords[MAX_WORDS][MAX_WORD_SIZE];
	char temp[MAX_WORD_SIZE];
	uint j = 0;
	uint i = 0;
	uint size = 0;
	
	/* prompt user for input */
	printf("Enter a space separated list of up to 10 strings to be sorted\n");
	printf("Enter a period by itself to terminate the list\n");


	while( i < MAX_WORD_SIZE && arrayOfWords[i][MAX_WORD_SIZE] != '.' )
	{
		i++;
		size++;
		if( i < MAX_WORD_SIZE )
		{
			scanf( "%s", &arrayOfWords[i][MAX_WORD_SIZE]);
		}
	} 
	
	/* alphebetize the words */
	for( i = 1; i < MAX_WORDS; i++ )
	{
		for( j = 2; j < MAX_WORDS; j++)
		{
			if( strcmp(arrayOfWords[j-1], arrayOfWords[j] ) > 0 )
			{
				strcpy( temp, arrayOfWords[j-1] );
				strcpy( arrayOfWords[j-1], arrayOfWords[j] );
				strcpy( arrayOfWords[j], temp) ;
			}
		}
	}


	/* print the words to the screen */

	for( i = 0; i < size; i++ )
		printf("%s\n", arrayOfWords[i]);	

	/* report success */
	return 0;
}
