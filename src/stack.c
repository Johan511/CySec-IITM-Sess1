#include "../includes/stack.h"

int initialise_stack(stack *st)
{
    if (st == NULL)
        goto error;
    st->arr = calloc(ST_MAX_SIZE, sizeof(char *));
    if (st->arr == NULL)
        goto error;
    st->len = 0;
    st->max_len = ST_MAX_SIZE;
    st->begin = 0;
    st->end = 0;
    return 1;

error:
    SAFE_FREE(st);
    SAFE_FREE(st->arr);
    return 0;
}

int extend_stack(stack *st)
{
    char **new_arr = calloc(st->max_len * ST_EXTEND_MULTIPLIER, sizeof(char *));
    if (new_arr == NULL)
        goto error;
    char **old_arr = st->arr;
    int begin = st->begin;
    int end = st->end;
    for (int i = st->begin; i < st->max_len; i++)
        new_arr[i-begin] = old_arr[i];
    st->arr = new_arr;
    st->end = (end - begin);
    st->begin = 0;
    st->max_len = st->max_len * ST_EXTEND_MULTIPLIER;
    return 1;

error:
    SAFE_FREE(new_arr);
    return 0;
}

int push(stack *st, char *e)
{
    if (st->end == st->max_len)
    {
        int extend = extend_stack(st);
        if (extend == 0)
            return 0;
    }

    st->arr[st->end] = e;
    st->end++;
    return 1;
}

char *pop(stack *st)
{
    char *top = calloc(strlen(st->arr[st->begin]) + 1, sizeof(char));
    if (top == NULL)
        goto error;

    strcpy(top, st->arr[st->begin]);
    if (strlen(st->arr[st->begin]) != 0)
        SAFE_FREE(st->arr[st->begin]);
    st->begin++;

    return top;
error:
    SAFE_FREE(top);
    SAFE_FREE(st->arr[st->begin]);

    return 0;
}
