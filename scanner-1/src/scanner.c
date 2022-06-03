/*
 * Christopher Valencia
 * scanner 1 project
 * 9/30/2020
 */
#include "scanner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 32

//
// clean up the referenced token (if it isn't NULL).
//
void freeToken(TOKEN **token)
{
    (*token)->val.integer = 0;
    (*token)->val.floating_point = 0;
    (*token)->val.op = '\0';
    free((*token)->val.string);
    free(*token);
    /*
     * TODO
     * free the referenced TOKEN*, and any data in
     * the referenced TOKEN which requires freeing
     * (not in that order).
     *
     * Then, set the referenced TOKEN* to NULL.
     */
}

void printToken (TOKEN **token)
{
    switch ((*token)->type)
    {
        case INT:
            printf("<INT, %i>\n", (int)(*token)->val.integer);
            break;
        case FLT:
            printf("<FLT, %f>\n", (*token)->val.floating_point);
            break;
        case ID:
            printf("<IDENT, %s>\n", (*token)->val.string);
            break;
        case ADDOP:
            printf( "<ADD_OP, %c>\n", (*token)->val.op);
            break;
        case MULTOP:
            printf( "<MULT_OP, %c>\n", (*token)->val.op);
            break;
        case ASSIGN:
            printf( "<ASSIGN>\n");
            break;
        case LPAREN:
            printf( "<LPAREN>\n");
            break;
        case RPAREN:
            printf( "<RPAREN>\n");
            break;
        case SCOLON:
            printf("<SEMICOLON>\n");
            break;
        case REPEAT:
            printf("<REPEAT>\n");
            break;
        case PRINT:
            printf("<PRINT>\n");
            break;
        case INVALID_TOKEN:
            printf("<INVALID, %s>\n", (*token)->val.string);
            break;
        case EOF_TOKEN:
            printf("<EOF>\n");
            break;
    }
    /*
     * TODO
     * Print the referenced token in a readable format.
     * Displayed information should include the token's type,
     * and also the token's value if applicable.
     *
     * Check the sample runs for an example format.
     */
}

void setKeywordOrID(TOKEN *token, char *str)
{
    if( strcmp(str, "print") == 0 )
    {
        token->type = PRINT;
    }
    else if( strcmp(str, "repeat") == 0)
    {
        token->type = REPEAT;
    }
    else
    {
        token->type = ID;
        token->val.string = malloc(sizeof(char) * (strlen(str)+1));
        strcpy(token->val.string, str);
    }
    /*
     * TODO
     * For use in the scanner function, to differentiate between keywords
     * and identifiers (which are treated identically by the state machine).
     *
     * Check if the collected token is a keyword by comparing the string
     * value arg to the string values of the keywords (print and repeat).
     * If the string value denotes is a print or repeat token, change its
     * type to the corresponding TOKEN_TYPE.
     *
     * If the token is not a keyword, then it is an identifier. Change its
     * type accordingly, and store its string value. Note that the str
     * argument is the scanner's buffer, so it should not be assigned
     * directly, but copied; the buffer will be freed before the token
     * is returned (see the bottom of the scanner function).
     *
     * Recall, to copy a string:
     * 1. Allocate enough space to store the string (including the null terminator).
     * 2. Copy the characters into this new space from the original.
     */
}

TOKEN *scanner()
{
    // buffer to store a token's contained characters while it is being tokenized
    size_t bufferSize = BUFFER_SIZE;
    char *stringValue = calloc(sizeof(char), bufferSize);
    int stringValueIndex = 0;

    // allocate space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));

    // initialize the token type to denote that the token is in progress
    token->type = UNASSIGNED;

    // set state machine to starting state
    FSM_STATE state = START_STATE;

    char currentChar = '\0';

    while (currentChar != EOF && token->type == UNASSIGNED)
    {
        currentChar = (char) getchar();
        /*
         * TODO
         * Given the current state of the state machine
         * and the next character, update the state machine
         * (and the string value of the token being built,
         * if applicable).
         *
         * DO NOT return anything here. The only return is the
         * one at the end of this function. Note that the while
         * loop stops iterating once token->type is updated, so
         * token->type should only be updated once the token is
         * ready to be returned.
         */
        if(state == START_STATE)
        {
            switch (currentChar)
            {
                case '(':
                    state = LPAREN_STATE;
                    token->type = LPAREN;
                    break;
                case ')':
                    state = RPAREN_STATE;
                    token->type = RPAREN;
                    break;
                case '=':
                    state = ASSIGN_STATE;
                    token->type = ASSIGN;
                    break;
                case ';':
                    state = SCOLON_STATE;
                    token->type = SCOLON;
                    break;
                case '+':
                case '-':
                    state = ADDOP_STATE;
                    token->val.op = currentChar;
                    token->type = ADDOP;
                    break;
                case '*':
                case '/':
                case '%':
                    state = MULTOP_STATE;
                    token->val.op = currentChar;
                    token->type = MULTOP;
                    break;
                case EOF:
                    state = EOF_STATE;
                    token->type = EOF_TOKEN;
                    break;
                default:
                    break;
            }
        }
        switch (currentChar) {
            case '(':
            case ')':
            case '=':
            case ';':
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                switch (state)
                {
                    case INT_STATE:
                        token->type = INT;
                        token->val.integer = atol(stringValue);
                        stringValueIndex = 0;
                        ungetc(currentChar, stdin);
                        break;
                    case FLT_STATE:
                        token->type = FLT;
                        token->val.floating_point = atof(stringValue);
                        stringValueIndex = 0;
                        ungetc(currentChar, stdin);
                        break;
                    case ID_STATE:
                        setKeywordOrID(token, stringValue);
                        stringValueIndex = 0;
                        ungetc(currentChar, stdin);
                        break;
                    case INVALID_STATE:
                        token->type = INVALID_TOKEN;
                        token->val.string = malloc(sizeof(char) * (strlen(stringValue)+1));
                        strcpy(token->val.string, stringValue);
                        stringValueIndex = 0;
                        ungetc(currentChar, stdin);
                        break;
                    default:
                        break;
                }
                break;
            case '0'...'9':
                if (state == START_STATE)
                {
                    state = INT_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }
                else
                {
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }
                break;
            case '.':
                if(state == INT_STATE)
                {
                    state = FLT_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }
                else
                {
                    state = INVALID_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                }
                break;
            case 'a'...'z':
            case 'A'...'Z':
            case '_':
            case '$':
                if (state == START_STATE || state == ID_STATE)
                {
                    state = ID_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                    break;
                }
                else
                {
                    state = INVALID_STATE;
                    stringValue[stringValueIndex] = currentChar;
                    stringValueIndex++;
                    break;
                }
            case ' ':
            case '\n':
            case '\r':
            case EOF:
                switch (state)
                {
                    case INT_STATE:
                        token->type = INT;
                        token->val.integer = atol(stringValue);
                        stringValueIndex = 0;
                        break;
                    case FLT_STATE:
                        token->type = FLT;
                        token->val.floating_point = atof(stringValue);
                        stringValueIndex = 0;
                        break;
                    case ID_STATE:
                        setKeywordOrID(token, stringValue);
                        stringValueIndex = 0;
                        break;
                    case INVALID_STATE:
                        token->type = INVALID_TOKEN;
                        token->val.string = malloc(sizeof(char) * (strlen(stringValue)+1));
                        strcpy(token->val.string, stringValue);
                        stringValueIndex = 0;
                        break;
                    default:
                        break;
                }
                if(currentChar == EOF)
                    ungetc(currentChar, stdin);
                break;
            default:
                state = INVALID_STATE;
                stringValue[stringValueIndex] = currentChar;
                stringValueIndex++;
                break;
        }

        // if the buffer is full, quadruple its size (do not edit)
        if (stringValueIndex >= bufferSize-1)
        {
            bufferSize *= 4;
            char *temp = calloc(sizeof(char), bufferSize);
            strcpy(temp, stringValue);
            free(stringValue);
            stringValue = temp;
        }
    }

    free(stringValue);
    return token;
}

