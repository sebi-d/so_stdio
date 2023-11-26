/*
 * Operating System Executable Loader header
 *
 * 2023, Operating Systems
 */

#ifndef SO_STDIO_H
#define SO_STDIO_H

#include <stdlib.h>
#include <unistd.h>
#include <error.h>

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

#define SO_EOF (-1)
#define BUFFER_SIZE 4096

#define READ_END 0
#define WRITE_END 1

#define READ 0
#define WRITE 1

struct _so_file {
    int _fileno;
    int _flags;
    char *_buffer;
    int _index;
    int _size;
    int _permissions;
    int _offset;
    int _errflag;
    int _io;
    int _eof;
    int _pid;
};

typedef struct _so_file SO_FILE;

SO_FILE *so_fopen(const char *pathname, const char *mode);

int so_fclose(SO_FILE *stream);

int so_fileno(SO_FILE *stream);

int so_fflush(SO_FILE *stream);

int so_fseek(SO_FILE *stream, long offset, int whence);

long so_ftell(SO_FILE *stream);

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);

int so_fgetc(SO_FILE *stream);

int so_fputc(int c, SO_FILE *stream);

int so_feof(SO_FILE *stream);

int so_ferror(SO_FILE *stream);

SO_FILE *so_popen(const char *command, const char *type);

int so_pclose(SO_FILE *stream);

#endif /* SO_STDIO_H */