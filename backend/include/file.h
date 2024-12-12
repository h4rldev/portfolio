#ifndef FILE_H_IMPLEMENTATION
#define FILE_H_IMPLEMENTATION

#include <stdbool.h>

char *get_mime(char *path);
char *get_cwd(void);

int make_dir(char *path);
bool path_exist(char *path);
char *read_file(char *path);

#endif // !FILE_H_IMPLEMENTATION
