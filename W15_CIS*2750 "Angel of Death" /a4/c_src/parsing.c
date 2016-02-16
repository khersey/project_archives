/* filename:   parsing.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 3
 * 
 * This file contains functions that are used to perform parsing by the library.
 */

#include "ParameterManager.h"


/*

Reads in a value, a character at a time.  This function can parse and process
INT_TYPE, REAL_TYPE, OR BOOLEAN_TYPE type values locally. for STRING_TYPE and LIST_TYPE,
other functions are called.

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
char current - the current character which has been read in.
char comment - the character with indicates the start of a comment.
union param_value **val - pointer to the value of a parameter.
param_t type - indicates the type of value being read.

Returns:
The next character after the value of the parameter.

Error Conditions:
Memory allocation fails.
Violation of the expected format.

*/
char valueMode(FILE *fp, char current, char comment, union param_value **val, param_t type) {
    int pos = 0;
    int size = 0;
    char *buffer = NULL;

    *val = malloc(sizeof(union param_value));
    if(*val == NULL) {
        return '0';
    }


    if (type == INT_TYPE) {
        while (isdigit(current)) {
            if (buffer == NULL || strlen(buffer) == size) {
                size += 20;
                buffer = realloc(buffer, size + 1);
                if(buffer == NULL) {
                    return '0';
                }
            }
            buffer[pos] = current;
            pos ++;
            current = fgetc(fp);
        }

        if(buffer != NULL) {
            sscanf(buffer, "%d", &(*val)->int_val);
        } else {
            return '0';
        }
        

    } else if (type == REAL_TYPE) {
        while (isdigit(current) || current == '.') {
            if (buffer == NULL || strlen(buffer) == size) {
                size += 20;
                buffer = realloc(buffer, size + 1);
                if(buffer == NULL) {
                    return '0';
                }
            }
            buffer[pos] = current;
            pos ++;
            current = fgetc(fp);
        }

        if(buffer != NULL) {
            sscanf(buffer, "%f", &(*val)->real_val);
        } else {
            return '0';
        }
        

    } else if (type == BOOLEAN_TYPE) {
        while (isalpha(current) && current != EOF && current != ';') {
            if (buffer == NULL || strlen(buffer) == size) {
                size += 20;
                buffer = realloc(buffer, size + 1);
                if(buffer == NULL) {
                    return '0';
                }
            }
            buffer[pos] = current;
            pos ++;
            current = fgetc(fp);
            if (strlen(buffer) == 4) {
                if (strcmp("true",buffer) == 0) {
                    (*val)->bool_val = true;
                    break;
                }
            } else if (strlen(buffer) == 5) {
                if (strcmp("false",buffer) == 0) {
                    (*val)->bool_val = false;
                    break;
                } else {         /* In this case, neither "true" or "false" has been read in */
                    return '0';  /* This will cause a parsing error */
                }
            }
        }

    } else if (type == STRING_TYPE) {
        current = stringMode(fp, current, &(*val)->str_val);

    } else if (type == LIST_TYPE) {
        current = listMode(fp, current, comment, &(*val)->list_val);
    }

    if (buffer != NULL) {
        free(buffer);
    }

    return current;
}


/*

Reads in characters until a " is read in, stringMode is then called,
where the string variable being passed in is a ParameterList param member,
where the string will be stored.  Upon reading in a }, this function exits.

Parameters:
FILE *fp - a valid pointer to an input stream.
char current - the current character which has been read in.
char comment - the character with indicates the start of a comment.
ParameterList **p - pointer to a pointer to a ParameterList
param_t type - indicates the type of value being read.

Returns:
The next character after a } is read

Error Conditions:
Memory allocation fails.
Violation of the expected format.

*/
char listMode(FILE *fp, char current, char comment, ParameterList **p) {

    ParameterList *temp = NULL;
    *p = malloc(sizeof(ParameterList));
    if(*p == NULL) {
        return '0';
    }

    (*p)->param = NULL;
    (*p)->next = NULL;


    while (current != '}' && current != EOF && current != '=' && current != ';') {
        if (current == '\"') {
            
            temp = malloc(sizeof(ParameterList));
            if(temp == NULL) {
                return '0';     /* This will cause a parse error if we are out of memory */
            }

            current = stringMode(fp, current, &temp->param);

            if((*p)->next == NULL) {
                (*p)->next = temp;
                temp->next = NULL;
            } else {
                temp->next = (*p)->next;
                (*p)->next = temp;
            }
            

        } else if (isspace(current)) {
            current = spaceMode(fp, current);
        } else if (current == comment) {
            current = commentMode(fp, current);
        } else {
            current = fgetc(fp);
        }
    }

    if (current == '}') {  
        current = fgetc(fp);    /* We want the next character after the list to be returned */
    }

    return current;
}


/*

Navigate to the bottom of the ParameterList, freeing the last element in the list,
and returning it's param member.

Parameters:
ParameterList *top - a valid, initialized ParameterList.

Returns:
The last element of the ParameterList or NULL if the list is empty.

Error Conditions:
The ParameterList is NULL.
Hanging pointer error.

*/
char * PL_next(ParameterList *top) {
    char *outval;
    ParameterList *destroyMe;
    ParameterList *last;

    destroyMe = top;
    if(destroyMe == NULL) {
        return NULL;
    }

    if(top->next == NULL && top->param == NULL) {
        return NULL;
    }

    while(destroyMe->next != NULL) {
        last = destroyMe;
        destroyMe = destroyMe->next;
    }


    outval = destroyMe->param;

    last->next = NULL;

    free(destroyMe);

    destroyMe = NULL;

    return outval;

}

int PL_count(ParameterList *top) {
    ParameterList *current;
    int count;

    if(top == NULL || top->next == NULL) {
        return 0;
    }

    count = 0;
    current = top;

    while(current->next != NULL) {
        current = current->next;
        count++;
    }

    return count;
}


/*

Dynamically allocates a string, reads in all characters until a " is read,
placing theses characters into str.
Returns the first character after the ".

Parameters:
FILE *fp - a valid input stream.
char current - the current character which has been read in.
char **str - pointer to a string which will be written to.

Returns:
The next character after a " is read in.

Error Conditions:
Memory allocation fails.
Expected format is not followed.

*/
char stringMode(FILE *fp, char current, char **str) {
    int pos = 0;
    int size = 0;
    char *temp = NULL;

    current = fgetc(fp); /* current will be ", and we dont want this in the string, so get next character */

    while(current != '\"' && current != EOF) {
        if (temp == NULL || strlen(temp) == size) {
            size += 20;
            temp = realloc(temp, size + 1);
            if(temp == NULL) {
                return '0';
            }
        }

        temp[pos] = current;
        pos++;
        current = fgetc(fp);
    }
    temp[pos] = '\0';

    if(current != EOF) {
        current = fgetc(fp); /* dont want to return ", so return next character */
    }

    *str = temp;

    return current;
}


/*

Reads in all characters, until a newline, null terminator, or EOF is read in.

Parameters:
FILE *fp - a valid input stream.
char current - the current character which has been read in.

Returns:
First character of the next line.

Error Conditions:

*/
char commentMode(FILE *fp, char current) {
    while(current != '\n' && current != '\0' && current != EOF) {
        current = fgetc(fp);
    }

    if (current != EOF) {
        current = fgetc(fp);
    }

    return current;
}

/*

Reads in characters, adding them to name, until a character is read that is not a letter, number or underscore.

Parameters:
FILE *fp - a valid input stream.
char current - the current character which has been read in.
char comment - the character which signals the start of a comment.
char **name - pointer to a char pointer, for storing the name value.

Returns:
the first character that is not a letter, number or underscore

Error Conditions:
Memory allocation fails.
Name starts with a character that is not a letter.

*/
char nameMode(FILE *fp, char current, char comment, char **name) {
    int pos = 0;
    int size = 20;
    char * temp;

    temp = malloc(size + 1);
    if(temp == NULL) {
        return '0';
    }

    while((isalpha(current) || isdigit(current) || current == '_') && current != comment && current != '=') {
        if (pos == 0 && !(isalpha(current))) {
            free(temp);
            return current;
        }
        if (temp == NULL || strlen(temp) == size) {
            size += 20;
            temp = realloc(temp, size + 1);
        }
        temp[pos] = current;
        pos++;
        current = fgetc(fp);
    }
    temp[pos] = '\0';

    *name = temp;

    return current;
}


/*

Reads in and discards all characters, until a character that is 
NOT a white space is read in.

Parameters:
FILE *fp - pointer to a valid input stream.
char current - the current character which has been read in.

Returns:
The next character that is not whitespace.

*/
char spaceMode(FILE *fp, char current) {
    while(isspace(current) && current != EOF) {
        current = fgetc(fp);
    }
    return current;
}


/*

Checks that all non-optional parameters have values.

Parameters:
ParameterManager *p - a valid, initialized ParameterManager.

Returns:
true upon success and false upon failure.

*/
Boolean parseValidate(ParameterManager *p) {
    int i;

    for(i = 0; i < p->curSize; i++) {
        if(p->param_managed[i].required && !(PM_hasValue(p, p->param_managed[i].name))) {
            #ifdef _DEBUG_
            printf("parseValidate: ERROR parameter \"%s\" is missing a value\n",p->param_managed[i].name);
            #endif

            return false;
        }
    }

    return true;
}
