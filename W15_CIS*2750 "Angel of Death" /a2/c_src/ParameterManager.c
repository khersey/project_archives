/* filename:   ParameterManager.c
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 1
 *
 * This file contains all the core functions of the library.
 */

#include "ParameterManager.h"


/*

Allocates memory for a ParameterManager, and allocates memory for an amount of parameters equal to size.

Parameters:
int size - initial size of the array containing parameters.  Must be greater than 0.

Returns:
A new ParameterManager struct, or NULL upon failure.

Error Conditions:
Size is less than 0.  
Memory allocation fails.

*/
ParameterManager * PM_create(int size) {

    ParameterManager * newPM;
    int i;
    
    newPM = malloc(sizeof(ParameterManager));
    if (!(newPM) || size <= 0) {
        return NULL;
    }

    newPM->maxSize = size;
    newPM->curSize = 0;
    newPM->param_managed = (parameter*)malloc(sizeof(parameter) * size);
    if (!(newPM->param_managed)) {
        return NULL;
    }

    for (i = 0; i < size; i++) {
        newPM->param_managed[i].name = NULL;
        newPM->param_managed[i].value = NULL;
    }

    return newPM;
}

/*

Frees all memory associated with a ParameterManager p.

Parameters:
ParameterManager p - an initialized ParameterManager.

Returns: 
1 upon success and 0 upon failure.

Error Conditions:
Double free could occur.

*/
int PM_destroy(ParameterManager *p) {
    int i;

    if(p == NULL) {
        return 1;
    }

    for (i = 0; i < p->maxSize; i++) {
        if (p->param_managed[i].name != NULL) {
            free(p->param_managed[i].name);
        }
        if (p->param_managed[i].value != NULL) {
            if (p->param_managed[i].type == STRING_TYPE) {
                free(p->param_managed[i].value->str_val);
            } else if (p->param_managed[i].type == LIST_TYPE) {
                free(p->param_managed[i].value->list_val);
            }

            free(p->param_managed[i].value);
        }
        
    }

    free(p->param_managed);
    free(p);
    return 1;
}



/*

Reads in characters one at a time, first looking for a name, then an =, then looking for the value of the name,
and lastly looking for a ;.  This is repeated until and EOF is read in. After an EOF is read, parseValidate will run,
which checks to see that all non-optional parameters have values. 

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
FILE *fp - a FILE pointer to a valid input stream.
char comment - contains the character which indicates the start of a comment.

Returns:
1 upon success or 0 upon failure.

Error Conditions:
Any violation of the expected format.
p or fp is NULL.
parseValidate fails (one or more non-optional parameters does not have a value).

*/
int PM_parseFrom(ParameterManager *p, FILE *fp, char comment) {
    char *name = NULL;
    char current;
    int key;

    current = fgetc(fp);

    if(p == NULL || fp == NULL) {
        #ifdef _DEBUG_
        printf("PM_parseFrom: ERROR file pointer is NULL\n");
        #endif

        return 0;
    }
    
    while(current != EOF) {

        do {
            current = spaceMode(fp, current);
            if(current == comment) {
                current = commentMode(fp, current);
            }
        } while(isspace(current) || current == comment);
        if(current == EOF) {
            break;
        }

        current = nameMode(fp, current, comment, &name);

        do {
            current = spaceMode(fp, current);
            if(current == comment) {
                current = commentMode(fp, current);
            }
        } while(isspace(current) || current == comment);
        if(current == EOF) {
            break;
        }

        key = PM_getKey(p, name);
        free(name);

        if(current == '=') {
            if(key == -1) {
                while(current != EOF && current != ';' ) {
                    current = fgetc(fp);
                }
                if(current == ';') {
                    current = fgetc(fp);
                }
                continue;
            }
        } else {
            #ifdef _DEBUG_
            printf("PM_parseFrom: ERROR expected =\n");
            #endif

            return 0; /* parse error */
        }

        current = fgetc(fp);

        do {
            current = spaceMode(fp, current);
            if (current == comment) {
                current = commentMode(fp, current);
            }
        } while (isspace(current) || current == comment);
        if(current == EOF) {
            break;
        }

        current = valueMode(fp, current, comment, &p->param_managed[key].value, p->param_managed[key].type);

        do {
            current = spaceMode(fp, current);
            if (current == comment) {
                current = commentMode(fp, current);
            }
        } while (isspace(current) || current == comment);
        if(current == EOF) {
            break;
        }

        if (current != ';') {
            #ifdef _DEBUG_
            printf("PM_parseFrom: ERROR expecting ;\n");
            #endif

            return 0; /* parse error */
        } else {
            current = fgetc(fp);
        }

    }

    if(!(parseValidate(p))) {
        #ifdef _DEBUG_
        printf("PM_parseFrom: ERROR parseValidate failure\n");
        #endif

        return 0;
    }

    return 1;
}



/*

Registers a new parameter in the next available position in ParameterManager p.

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
char *pname - a string containing a parameter name.
param_t ptype - parameter type (see ParameterManager.h for valid types).
int required - 1 if parameter is required, 0 if it is optional.

Returns:
1 upon success or 0 upon failure.

Error Conditions:
p or pname are NULL.
A parameter with the same name has already been registered on this ParameterManager.
Memory allocation fails.

*/
int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required) {
    int key, i, length;
    parameter * temp = NULL;

    if(p == NULL || pname == NULL) {
        return 0;
    }

    key = PM_getKey(p, pname);

    if (key == -1) {
        if (p->curSize == p->maxSize) {
            p->maxSize *= 2;
            temp = (parameter*)realloc(p->param_managed, p->maxSize * sizeof(parameter));
            if(temp == NULL) {
                return 0;
            }
            p->param_managed = temp;
            for(i = p->curSize; i < p->maxSize; i++) {
                p->param_managed[i].name = NULL;
                p->param_managed[i].value = NULL;
            }
            
        }

        p->param_managed[p->curSize].name = malloc(strlen(pname) + 1);
        if(!(p->param_managed[p->curSize].name)) {
            return 0;
        }
        strcpy(p->param_managed[p->curSize].name, pname);
        length = strlen(p->param_managed[p->curSize].name);
        p->param_managed[p->curSize].name[length] = '\0';
        p->param_managed[p->curSize].type = ptype;
        p->param_managed[p->curSize].required = required;
        p->curSize++;

        return 1;
    }

    return 0;
}

/*

Checks to see if a parameter has a value.

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
char *pname - a string containing a parameter name.

Returns:
1 if parameter has value, 0 if it does not.

Error Conditions:
p or pname is NULL.

*/
int PM_hasValue(ParameterManager *p, char *pname) {
    int key;

    if(p == NULL || pname == NULL) {
        return 0;
    }

    key = PM_getKey(p, pname);

    if (key != -1 && p->param_managed[key].value != NULL) {
        return 1;
    }

    return 0;
}

/*

Gets the index of a parameter in a ParameterManager

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
char *pname - a string containing a parameter name.

Returns:
The index of the parameter, or -1 upon failure.

Error Conditions:
p or pname is NULL.
There is no parameter registered with the provided name.

*/
int PM_getKey(ParameterManager *p, char *pname) {
    int i;

    if(pname != NULL && p != NULL) {
        for (i = 0; i < p->curSize; i++) {
            if (strcmp(p->param_managed[i].name, pname) == 0) {
                return i;
            }
        }
    }

    return -1;
}

/*

Gives the value of a parameter in a ParameterManager.

Parameters:
ParameterManager *p - a valid initialized ParameterManager.
char *pname - a string containing a parameter name.

Returns:
The value of the parameter with name pname.

Error Conditions:
If p or pname is NULL, or pname is not a valid name this function will cause a segfault.

*/
union param_value PM_getValue(ParameterManager *p, char *pname) {
    int key;

    key = PM_getKey(p, pname);
    
    return *p->param_managed[key].value;
}



