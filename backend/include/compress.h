#ifndef COMPRESS_H_IMPLEMENTATION
#define COMPRESS_H_IMPLEMENTATION

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

char *compress_gzip(const char *in, size_t in_len, size_t *res_len);
bool test_compress_file(FILE *file);

#endif // !COMPRESS_H_IMPLEMENTATION
