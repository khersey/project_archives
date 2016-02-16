/* filename:   ParameterManager.h
 * student:    Kyle Hersey
 * student#:   0851973
 * course:     CIS*2750
 * assignment: 1
 *
 */


#ifndef PM_INCLUDED
#define PM_INCLUDED


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Define ADTs */

typedef enum Boolean {
    false = 0,
    true = 1
} Boolean;

typedef enum param_t {
    INT_TYPE,
    REAL_TYPE,
    BOOLEAN_TYPE,
    STRING_TYPE,
    LIST_TYPE
} param_t;

typedef struct ParameterList ParameterList;
struct ParameterList {
    char * param;
    ParameterList * next;
};

union param_value {
    int int_val;
    float real_val;
    Boolean bool_val;
    char *str_val;
    ParameterList *list_val;
};

typedef struct parameter parameter;
struct parameter {
    char *name;
    param_t type;
    union param_value *value;
    Boolean required;
};

typedef struct ParameterManager ParameterManager;
struct ParameterManager {
    parameter *param_managed;
    int maxSize;
    int curSize;
};



/* Define Interface Functions */

ParameterManager * PM_create(int size);

int PM_destroy(ParameterManager *p);

int PM_parseFrom(ParameterManager *p, FILE *fp, char comment);

int PM_manage(ParameterManager *p, char *pname, param_t ptype, int required);

int PM_hasValue(ParameterManager *p, char *pname);

union param_value PM_getValue(ParameterManager *p, char *pname);

char * PL_next(ParameterList *top);



/* Define Utility Functions */

int PM_getKey(ParameterManager *p, char *pname);

int PL_count(ParameterList *top);



/* Define Parsing Functions (parsing.c) */
char nameMode(FILE *fp, char current, char comment, char **name);

char listMode(FILE *fp, char current, char comment, ParameterList **p);

char valueMode(FILE *fp, char current, char comment, union param_value **value, param_t type);

char stringMode(FILE *fp, char current, char **str);

char commentMode(FILE *fp, char current);

char spaceMode(FILE *fp, char current);

Boolean parseValidate(ParameterManager *p);


#endif
