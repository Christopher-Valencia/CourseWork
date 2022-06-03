/* Christopher Valencia
 * c tutorial
*/
#include <stdio.h>
#include <ctype.h>

#define DANGER_LEVEL 5    /* C Preprocessor -
			- substitution on appearance */

/* like Java ‘final’ */
int main(void) {
    char level;

    while (1) {
        printf("Enter gas level: ");
        level = getchar();
        level = tolower(level);

        switch (level) {
            case 'e':
                printf("empty \n");
                return 0;
            case 'f':
                printf("full \n");
                return 0;
            case 'h':
                printf("half full \n");
                return 0;
            default:
                printf("invalid entry! \n enter only 'e' 'h' 'f' \n");
                break;
        }
    }

    /* if-then-else as in Java */
    /*if (level <= DANGER_LEVEL) /*replaced by 5
        printf("Low on gas!\n");
    else
        printf("Good driver !\n");*/

    return 0;
}
