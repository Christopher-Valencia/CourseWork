/* Christopher Valencia
 * c tutorial
*/
#include <stdio.h>

int main(void) {
    int nStudents = 0, nFaculty = 0; /* Initialization, required */
    float ratio = 0.0;

    printf("How many students does CSUCI have ?:");
    scanf("%d", &nStudents);  /* Read input */

    printf("How many faculty does CSUCI have ?:");
    scanf("%d", &nFaculty);  /* Read input */

    printf("CSUCI has %d students.\n", nStudents);
    printf("CSUCI has %d faculty. \n", nFaculty);

    ratio = (float) nFaculty / nStudents;
    printf( "CSUCI has %0.1f faculty to student ratio. \n", ratio);

    return 0;
}
