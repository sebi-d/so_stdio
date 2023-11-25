#include "so_stdio.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

SO_FILE *so_fopen(const char *pathname, const char *mode) {
    
    SO_FILE* new_file = (SO_FILE*) calloc (1, sizeof(SO_FILE));

    if(new_file == NULL) {
        return NULL;
    }
    
    //fileno
    new_file->_fileno = -1;

    //buffer
    new_file->_index = 0;
    new_file->_buffer = (char*) calloc (BUFFER_SIZE, sizeof(char));
    
    if(new_file->_buffer == NULL) {
        free(new_file);
        return NULL;
    }

    //flags
    new_file->_flags = 0;

    //eof
    new_file->_eof = 0;

    if (strcmp(mode, "r") == 0) {
        new_file->_io = READ;
        new_file->_flags = O_RDONLY;
        new_file->_offset = 0;
    } else if (strcmp(mode, "w") == 0) {
        new_file->_io = WRITE;
        new_file->_flags = O_WRONLY | O_CREAT | O_TRUNC;
        new_file->_offset = 0;
    } else if (strcmp(mode, "a") == 0) {
        new_file->_io = WRITE;
        new_file->_flags = O_WRONLY | O_CREAT | O_APPEND;
        new_file->_offset = lseek(new_file->_fileno, 0, SEEK_END);
    } else if (strcmp(mode, "r+") == 0) {
        new_file->_io = READ;
        new_file->_flags = O_RDWR;
        new_file->_offset = 0;
    } else if (strcmp(mode, "w+") == 0) {
        new_file->_io = WRITE;
        new_file->_flags = O_RDWR | O_CREAT | O_TRUNC;
        new_file->_offset = 0;
    } else if (strcmp(mode, "a+") == 0) {
        new_file->_io = WRITE;
        new_file->_flags = O_RDWR | O_CREAT | O_APPEND;
        new_file->_offset = lseek(new_file->_fileno, 0, SEEK_END);
    } else {
        free(new_file->_buffer);
        free(new_file);
        return NULL;
    }

    //permissions
    new_file->_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    //open
    new_file->_fileno = open(pathname, new_file->_flags, new_file->_permissions);

    if(new_file->_fileno < 0) {
        free(new_file->_buffer);
        free(new_file);
        return NULL;
    }

    return new_file;
}