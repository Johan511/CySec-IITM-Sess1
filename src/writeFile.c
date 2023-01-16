#include "../includes/writeFile.h"


int writeToFile(char *top, FILE *fp)
{
    fprintf(fp, "%s\n", top);
    return 1;
}

int writeFile(FILE *fp)
{
    stack *st = NULL;
    char *s = NULL;
    char *top = NULL;
    st = malloc(sizeof(stack));

    if (initialise_stack(st) == 0)
        return 0;
    push(st, "");
    while (st->begin != st->end)
    {
        top = pop(st);
        int s_len = strlen(top);
        if (s_len >= STR_MAX_SIZE)
        {
            writeToFile(top, fp);
        }
        else
        {
            for (char c = 'a'; c != 'z' + 1; c++)
            {
                s = calloc(s_len + 2, sizeof(char));
                if (s == NULL)
                    goto error;
                strcpy(s, top);
                s[s_len] = c;
                s[s_len + 1] = '\0';
                push(st, s);
            }
        }
        SAFE_FREE(top);
    }
    SAFE_FREE(st->arr);
    SAFE_FREE(st);
    return 0;
error:
    SAFE_FREE(top);
    SAFE_FREE(st->arr);
    SAFE_FREE(st);
    return 0;
}
