/* Christopher Valencia
 * c tutorial task 5
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_NUM_OF_WORDS 128

int main(void)
{
    int count = 0;
    char *words[MAX_NUM_OF_WORDS];
    char temp[45];

    printf("Enter words (enter \"END\" to stop): \n");
    while (count < MAX_NUM_OF_WORDS)
    {
        scanf("%s", temp);

        if (strcmp(temp, "END") == 0)
            break;

        words[count] = malloc((strlen(temp)+1) * sizeof(char));
        strcpy(words[count], temp);

        count++;
    }
    if (count == MAX_NUM_OF_WORDS)
        printf("You have entered too many words, we are moving on. \n");

    printf("The following %d words have been read:\n", count);
    for(int index = 0; index < count; index++)
    {
        printf("%s \n", words[index]);
        free(words[index]);
    }

    return (0);
}