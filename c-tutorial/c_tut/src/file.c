#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	/* file handles */
	FILE *outputFile=NULL;
	FILE *inputFile=NULL;
	char* fileName;
	char temp[100];
	int c;

	inputFile = fopen( "data.txt", "r");
	if(inputFile == NULL)
	    return(1);

	printf("Enter the name of the file you want to create: \n");
    scanf("%s", temp);

    fileName = malloc((strlen(temp)+1) * sizeof(char));
    strcpy(fileName, temp);

	/* open files for writing*/
	outputFile = fopen(fileName, "w+");
	if(outputFile == NULL)
		return(2);    /* need to do explicit ERROR CHECKING */

    while(1)
    {
        c = fgetc(inputFile);
        if( feof(inputFile) )
            break;

        fputc(c, outputFile);
    }

	/* write some data into the file */
    //fprintf(outputFile, "Hello there");
	
	/* don’t forget to close file handles */
	fclose(outputFile);
	fclose(inputFile);
	free( fileName );
	
    return 0;
}
