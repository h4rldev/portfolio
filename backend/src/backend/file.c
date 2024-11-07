#include "../../include/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *read_file(char *path) {
  FILE *file = fopen(path, "rb+");
  size_t file_len = 0;

  if (!file) {
    perror("Failed to open file");
    printf("File path: %s\n", path);
    return 0;
  }

  fseek(file, 0L, SEEK_END);
  file_len = ftell(file);
  rewind(file);

  if (file_len <= 0) {
    fprintf(stderr, "Failed to read file length, can't read file. exiting..\n");
    fclose(file);
    return 0;
  }

  char *buffer = (char *)malloc(file_len);
  if (!buffer) {
    perror("malloc");
    fclose(file);
    return 0;
  }

  size_t bytes_read = 0;
  bytes_read = fread(buffer, 1, file_len, file);
  if (bytes_read != file_len) {
    fprintf(stderr, "Did not read the whole file.. Something definitely went "
                    "very wrong.\n");
    free(buffer);
    fclose(file);
    return 0;
  }

  fclose(file);
  return buffer;
}

char *get_cwd(void) {
  char *cwd = malloc(1024);
  if (!cwd)
    return 0;

  if (getcwd(cwd, 1024) == NULL) {
    perror("getcwd");
    return 0;
  }

  return cwd;
}
