#include "../includes/sha256.h"
#include "../includes/readFile.h"
#include "../includes/writeFile.h"

#include <stdlib.h>
#define CACHE_SIZE 1000
const char *FILENAME = "possible.txt";


int readFile(BYTE *orginal_hash)
{
    char **cache = NULL;
    cache = calloc(CACHE_SIZE, sizeof(char *));
    if (cache == NULL)
        exit(0);
    for (int i = 0; i < CACHE_SIZE; i++)
        cache[i] = calloc(STR_MAX_SIZE + 2, sizeof(BYTE));

    FILE *fp = fopen(FILENAME, "r");
    int i = 0;
    do
    {
        if (i == CACHE_SIZE)
        {
            for (int j = 0; j < CACHE_SIZE; j++)
            {
                int len = strlen(cache[j]);
                BYTE *text = calloc(sizeof(BYTE), len);
                memset(text, 0, len);
                memcpy(text, cache[j], len * sizeof(BYTE));
                BYTE hash[SHA256_BLOCK_SIZE];
                SHA256_CTX ctx;

                sha256_init(&ctx);
                sha256_update(&ctx, text, len);
                sha256_final(&ctx, hash);
                if (!memcmp(hash, orginal_hash, SHA256_BLOCK_SIZE))
                {
                    printf("%s\n", cache[j]);
                    exit(0);
                };
                SAFE_FREE(text);
            }
            i = i % CACHE_SIZE;
        }
        memset(cache[i], 0, STR_MAX_SIZE + 2);
        fgets(cache[i], STR_MAX_SIZE + 1, fp);
    } while (cache[i++] != NULL);
}

int main()
{
    FILE *fp = fopen(FILENAME, "w+");
    BYTE* text1 = PASSWORD;
    
    if (fp == NULL)
        return 1;
    writeFile(fp);
    fflush(fp);
    BYTE buf[SHA256_BLOCK_SIZE];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx, text1, strlen(text1));
    sha256_final(&ctx, buf);
    BYTE *original_hash = buf;

    readFile(original_hash);
    return 0;
}