#ifndef FILE_H_IMPLEMENTATION
#define FILE_H_IMPLEMENTATION

#include <stdbool.h>
#include <stdio.h>

char *get_mime(const char *path);
char *get_cwd(void);

int make_dir(const char *path);
bool path_exist(const char *path);
bool is_file(const char *path);
char *read_file_from_fd(FILE *file);
char *read_file(const char *path);

#endif // !FILE_H_IMPLEMENTATION
