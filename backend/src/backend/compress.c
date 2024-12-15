#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib-ng.h>

#include "../../include/compress.h"

static void *handle_zng_compression_error(zng_stream *stream, char *topic,
                                          int err) {
  fprintf(stderr, "%s failed code: %d msg: %s\n", topic, err, stream->msg);
  return NULL;
}

// NOTE: Be sure to add Content-Encoding header for the file you decide to
// NOTE: route!
char *compress_gzip(const char *in, size_t in_len, size_t *res_len) {
  // Initialize compression stream
  int stat;

  char *buf = malloc(in_len);
  char *ret_buf = malloc(1);
  if (!buf && !ret_buf)
    return NULL;

  zng_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;

  // Compress into gzip
  stat = zng_deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 | 16,
                          8, Z_DEFAULT_STRATEGY);
  if (stat != Z_OK)
    return handle_zng_compression_error(&stream, "deflate initialization",
                                        stat);

  stream.avail_in = in_len;
  stream.next_in = (unsigned char *)in;
  stream.avail_out = in_len;
  stream.next_out = (unsigned char *)buf;

  stat = zng_deflate(&stream, Z_FINISH);
  if (stat != Z_STREAM_END) {
    return handle_zng_compression_error(&stream, "deflating", stat);
  }

  *res_len = stream.total_out;

  // printf("Compressed data (hex): ");
  // for (int i = 0; i < *res_len; i++) {
  //   printf("%02x", (unsigned char)buf[i]);
  // }
  // printf("\n");

  ret_buf = realloc(ret_buf, *res_len);
  memcpy(ret_buf, buf, *res_len);

  stat = zng_deflateEnd(&stream);
  if (stat != Z_OK)
    return handle_zng_compression_error(&stream, "end deflation", stat);

  // printf("Deflated: %lu bytes\n", stream.total_out);

  free(buf);

  return ret_buf;
}

bool test_compress_file(FILE *file) {
  size_t file_size = 0;
  size_t compressed_size = 0;

  if (!file)
    return NULL;

  (void)fseek(file, 0L, SEEK_END);
  file_size = ftell(file);
  (void)fseek(file, 0L, SEEK_SET);

  if (file_size <= 128)
    return false;

  return true;
}
