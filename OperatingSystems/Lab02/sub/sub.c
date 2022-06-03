/**
 * Name: Christopher Valencia
 * Lab: Lab02
 * Date: 02/10/21
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void callHelp();

int main(int argc, char *argv[])
{
    if((argc == 1) || (strcmp(argv[1], "-h") == 0))
    {
        callHelp();
        return(0);
    }

    FILE *fin=NULL;
    FILE *fout=NULL;
    char *remove;
    char *insert;

    for(int x = 1; x < argc; x++)
    {
        if(strcmp(argv[x], "-i") == 0)
        {
            //printf("input set\n");
            fin = freopen(argv[x+1], "r", stdin);
            x++;
        }
        else if(strcmp(argv[x], "-o") == 0)
        {
            //printf("output set\n");
            fout = freopen(argv[x+1], "w", stdout);
            x++;
        }
        else if(strncmp(argv[x], "--", 2) == 0)
        {
            //printf("remove set\n");
            remove = malloc(sizeof(char)*strlen(argv[x])+1);
            strcpy(remove, argv[x]);
        }
        else if(strncmp(argv[x], "-+", 2) == 0)
        {
            //printf("insert set\n");
            insert = malloc(sizeof(char)*strlen(argv[x])+1);
            strcpy(insert, argv[x]);
        }
    }
    if(strlen(insert) < strlen(remove))
    {
        if(fout != NULL)
            fclose(fout);
        printf("sub: Error - missing replacement character\n");
        return(0);
    }
    if(strlen(insert) > strlen(remove))
    {
        fprintf(stdout, "sub: WARNING - extraneous replacement character\n");
        strncpy(insert, insert, strlen(remove));
    }

    if(fin == NULL)
    {
        char *temp = malloc(sizeof(char)*128);
        fgets(temp, 128, stdin);

        for(int x=0; x<strlen(temp); x++)
        {
            for(int y=2; y<strlen(remove); y++)
            {
                if(remove[y] == temp[x])
                    temp[x]=insert[y];
            }
            putc(temp[x], stdout);
        }
        free(temp);
    }
    else
    {
        char buffer;
        while (EOF != buffer)
        {
            buffer = getc(stdin);
            for (int x = 2; x < strlen(remove); x++)
            {
                if (remove[x] == buffer)
                    buffer = insert[x];
            }
            putc(buffer, stdout);
        }
    }

    if(fin != NULL)
        fclose(fin);
    if(fout != NULL)
        fclose(fout);
    free(remove);
    free(insert);
    return(0);
}

void callHelp()
{
    FILE *f;
    char buffer;
    f = freopen("help.txt", "r", stdin);
    buffer=getc(stdin);
    while(EOF != buffer)
    {
        putc(buffer, stdout);
        buffer=getc(f);
    }
    fclose(f);
}