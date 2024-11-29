#ifndef COMPRESS_H_IMPLEMENTATION
#define COMPRESS_H_IMPLEMENTATION

#include <stddef.h>

char *compress_gzip(const char *in, size_t in_len, size_t *res_len);
char *compress_brotli(const unsigned char *in, size_t in_len, size_t *res_len);

#endif // !COMPRESS_H_IMPLEMENTATION
