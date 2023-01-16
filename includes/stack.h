#include <string.h>
#include <stdlib.h>

#define SAFE_FREE(x)     \
    do                   \
    {                    \
        if ((x) != NULL) \
        {                \
            free(x);     \
            x = NULL;    \
        }                \
    } while (0)
#define ST_MAX_SIZE 1000
#define ST_EXTEND_MULTIPLIER 2
#define STR_MAX_SIZE 4

typedef struct __stack
{
    int len;
    char **arr;
    int max_len;
    int begin;
    int end;
} stack;

int initialise_stack(stack *st);
int extend_stack(stack *st);
int push(stack *st, char *e);
char *pop(stack *st);
void free_stack(stack *st);