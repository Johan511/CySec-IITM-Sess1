#include <inttypes.h>
#include <stdint.h>

#pragma once
#define SHA256_HASH_SIZE 32

/* Hash size in 32-bit words */
#define SHA256_HASH_WORDS 8


typedef unsigned char BYTE;             // 8-bit byte
typedef unsigned int  WORD;             // 32-bit word, change to "long" for 16-bit machines
struct _SHA256Context {
  uint64_t totalLength;
  uint32_t hash[SHA256_HASH_WORDS];
  uint32_t bufferLength;
  union {
    uint32_t words[16];
    uint8_t bytes[64];
  } buffer;
};

typedef struct _SHA256Context SHA256_CTX;


extern void sha256_init (SHA256_CTX *sc);
extern void sha256_update (SHA256_CTX *sc, const void *data, uint32_t len);
extern void sha256_final (SHA256_CTX *sc, uint8_t hash[SHA256_HASH_SIZE]);


