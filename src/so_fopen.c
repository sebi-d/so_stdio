#include "so_stdio.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

SO_FILE *so_fopen(const char *pathname, const char *mode) {
    
    SO_FILE* new_file = (SO_FILE*) malloc (sizeof(SO_FILE));

    if(new_file == NULL) {
        return NULL;
    }

    //buffer
    new_file->_index = 0;
    memset(new_file->_buffer, 0, BUFFER_SIZE);

    //flags
    new_file->_flags = 0;

    if (strcmp(mode, "r") == 0) {
        new_file->_flags = O_RDONLY;
    } else if (strcmp(mode, "w") == 0) {
        new_file->_flags = O_WRONLY | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "a") == 0) {
        new_file->_flags = O_WRONLY | O_CREAT | O_APPEND;
    } else if (strcmp(mode, "r+") == 0) {
        new_file->_flags = O_RDWR;
    } else if (strcmp(mode, "w+") == 0) {
        new_file->_flags = O_RDWR | O_CREAT | O_TRUNC;
    } else if (strcmp(mode, "a+") == 0) {
        new_file->_flags = O_RDWR | O_CREAT | O_APPEND;
    } else {

        new_file->_errflag = 1;
        return NULL;
    }

    //permissions
    new_file->_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    new_file->_fileno = open(pathname, new_file->_flags, new_file->_permissions);

    if(new_file->_fileno < 0) {
        new_file->_errflag = 1;
        const char* errorMessage = "Error openning the file\n";
        write(STDERR_FILENO, errorMessage, sizeof(errorMessage) - 1);
        return NULL;
    }

    return new_file;
}