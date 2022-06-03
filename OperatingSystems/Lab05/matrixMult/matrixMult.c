/**
 * Name: Christopher Valencia
 * Lab: Lab05
 * Date: 03/03/21
 **/
#include "matrixMult.h"

int main(int argc, char *argv[])
{
    //printf("START\n");
   if (freopen(argv[1], "r", stdin) == 0)
      oops("Cannot open the input file.\n", -1);

   int **a1, **b1, **c1, **a2, **b2, **c2; // matrices
   int m1, k1, n1, m2, k2, n2; // dimensions of the matices m x k and k x n

   allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
   allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

   // the real magic happens in here
   pthread_t **tids1 = multiply(a1, b1, c1, m1, k1, n1);
   pthread_t **tids2 = multiply(a2, b2, c2, m2, k2, n2);

   join(tids1, m1, n1);
   join(tids2, m2, n2);

   free_tids(tids1, m1);
   free_tids(tids2, m2);

   // dispaly results of matrix multiplication
   printf("\nMATRIX A1\n");
   displayMatrix(a1, m1, k1);
   freeMatrix(a1, m1);
   printf("\nMATRIX B1\n");
   displayMatrix(b1, k1, n1);
   freeMatrix(b1, k1);
   printf("\nMATRIX A1 x B1\n");
   displayMatrix(c1, m1, n1);
   freeMatrix(c1, m1);

   printf("\nMATRIX A2\n");
   displayMatrix(a2, m2, k2);
   freeMatrix(a2, m2);
   printf("\nMATRIX B2\n");
   displayMatrix(b2, k2, n2);
   freeMatrix(b2, k2);
   printf("\nMATRIX A2 x B2\n");
   displayMatrix(c2, m2, n2);
   freeMatrix(c2, m2);

   return 0;
}

void *matrixThread(void *param)//equivalent to runner method for threads
{
   // map the parameter onto the structure
   MATRIX_CELL *cell = (MATRIX_CELL *)param;

   // TODO: implement
   for(int x=0; x<cell->k; x++)
       cell->c[cell->i][cell->j] += cell->a[cell->i][x] * cell->b[x][cell->j];

   free(cell);

   return NULL;
}

void allocateAndLoadMatrices(int ***a, int ***b, int ***c, int *m, int *k, int *n)
// takes pointers to two-dimensional matrices, so they can be allocated in here
// and used by the caller
// should call the function loadMatrix(int ***matrix, int m, int n)
{
   if (scanf("%d %d %d", m, k, n) == 0)
      oops("Cannot read matrix sizes.\n", -2);

   // TODO: implement

   //allocate the space needed for the matrices
    //printf("allocating A\n");
    *a = malloc(sizeof (int**));
    (*a) = malloc(sizeof (int*)*(*m));
    for(int x=0; x<(*m); x++)
    {
        (*a)[x] = malloc((*k)*sizeof (int*));
    }
    //printf("allocating B\n");
    *b = malloc(sizeof (int**));
    (*b) = malloc(sizeof (int*)*(*k));
    for(int x=0; x<(*k); x++)
    {
        (*b)[x] = malloc((*n)*sizeof (int*));
    }

    *c = malloc(sizeof (int**));
    (*c) = malloc(sizeof (int*)*(*m));
    for(int x=0; x<(*m); x++)
    {
        (*c)[x] = malloc((*n)*sizeof (int*));
    }
    //load matrix data into matrix a and b
    loadMatrix(a, *m, *k);
    //printf("DONE LOADING A\n");

    loadMatrix(b, *k, *n);
    //printf("DONE LOADING B\n");

    //loading matrix c with all zeros to prep for multiply
    for(int x=0; x<(*m); x++)
    {
        for(int y=0; y<(*n); y++)
        {
            (*c)[x][y] = 0;
        }
    }
}

void loadMatrix(int ***matrix, int m, int n)
{
    //printf("LOADING\n");
   // TODO: implement
   for(int x=0; x<m; x++)
   {
       for(int y=0; y<n; y++)
       {
           scanf("%d", &(*matrix)[x][y]);
       }
   }
}

void freeMatrix(int **matrix, int m)
{
   // TODO: implement
    for(int x=0; x<m; x++)
    {
        free(matrix[x]);
    }
    free(matrix);
}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n)
{
   pthread_t **tids = alloc_tids(m, n);

   // TODO: implement

    for(int row=0; row<m; row++)
    {
        for(int col=0; col<n; col++)
        {
            MATRIX_CELL *cell = malloc(sizeof (MATRIX_CELL));
            cell->a = a;
            cell->b = b;
            cell->c = c;
            cell->i = row;
            cell->j = col;
            cell->k = k;
            pthread_create(&tids[row][col], NULL, matrixThread, (void *) cell);
        }
    }
   return tids;
}

pthread_t **alloc_tids(int m, int n)
{
   pthread_t **tids;

   // TODO: implement
    tids = malloc(sizeof (pthread_t**));
    (tids) = malloc(sizeof (pthread_t*)*(m));
    for(int x=0; x<m; x++)
    {
        (tids)[x] = malloc(n*sizeof (pthread_t*));
    }

   return tids;
}

void free_tids(pthread_t **tids, int m)
{
   // TODO: implement
    for(int x=0; x<m; x++)
    {
        free(tids[x]);
    }
    free(tids);
}

void join(pthread_t **tids, int m, int n)
{
   // TODO: implement
    for(int row=0; row<m; row++)
    {
        for (int col = 0; col < n; col++)
        {
            pthread_join(tids[row][col], NULL);
        }
    }
}

void displayMatrix(int **matrix, int m, int n)
{
   // TODO: implement
   //printf("PRINTING\n");
   for(int x=0; x<m; x++)
   {
       for(int y=0; y<n; y++)
       {
           printf("%d ", matrix[x][y]);
       }
       printf("\n");
   }
}
