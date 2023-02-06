#include "../includes/sha256.h"
#include "../includes/readFile.h"
#include "../includes/writeFile.h"

#include <stdlib.h>
#include "../includes/sha256.h"
#define CACHE_SIZE 10000

#define READ

#ifdef READ
const char *FILE_OPEN_MODE = "r+";
const char *FILENAME = "rockyou.txt";

#else
const char *FILE_OPEN_MODE = "w+";
const char *FILENAME = "possible.txt";
#endif

void readFile(BYTE *orginal_hash)
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
#ifdef READ
                if (cache[j][len - 1] == '\n')
                    len--;
#endif
                BYTE *text = calloc(sizeof(BYTE), len);
                memset(text, 0, len);
                memcpy(text, cache[j], len * sizeof(BYTE));
                BYTE hash[SHA256_HASH_SIZE];
                SHA256_CTX ctx;

                sha256_init(&ctx);
                sha256_update(&ctx, text, len);
                sha256_final(&ctx, hash);
                if (!memcmp(hash, orginal_hash, SHA256_HASH_SIZE))
                {
                    printf("%s\n", cache[j]);
                    exit(0);
                };
                SAFE_FREE(text);
            }
            i = i % CACHE_SIZE;
        }
        memset(cache[i], 0, STR_MAX_SIZE + 2);
        (void)!fgets(cache[i], STR_MAX_SIZE + 1, fp);
    } while (cache[i++] != NULL);
}

int main()
{
    FILE *fp = fopen(FILENAME, FILE_OPEN_MODE);
    BYTE *text1 = (BYTE *)PASSWORD;

    if (fp == NULL)
        return 1;
    #ifndef READ
    writeFile(fp);
    fflush(fp);
    #endif
    BYTE buf[SHA256_HASH_SIZE];
    SHA256_CTX ctx;

    sha256_init(&ctx);
    sha256_update(&ctx, text1, strlen((char *)text1));
    sha256_final(&ctx, buf);
    BYTE *original_hash = buf;

    printf("Bits : \n");
    for (int j = 0; j < 32; j++)
    {
        char a = original_hash[j];
        int i;
        for (i = 0; i < 8; i++)
        {
            printf("%d", !!((a << i) & 0x80));
        }
        printf(" ");
    }
    printf("\n");
    int wait;
    while (scanf("%d\n", &wait))
    {
    }
    readFile(original_hash);
    return 0;
}