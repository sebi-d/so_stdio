#include "so_stdio.h"
#include <unistd.h>
#include <fcntl.h>

int so_fseek(SO_FILE *stream, long offset, int whence) {
    
    if(stream->_index > 0) {
        size_t result = write(stream->_fileno, stream->_buffer, stream->_index);

        if(result < 0) {
            stream->_errflag = 1;
            const char* error_message = "error writing to file";
            write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
            return SO_EOF;
        }

        stream->_index = 0;
    }

    off_t new_offset;

    if(whence == SEEK_SET) {
        new_offset = stream->_offset;
    }
    else if (whence == SEEK_CUR) {
        new_offset = stream->_offset + offset;
    } else if (whence == SEEK_END) {
        off_t fileSize = lseek(stream->_fileno, 0, SEEK_END);
        new_offset = fileSize + offset;
    } else {
        stream->_errflag = 1;
        return SO_EOF;  
    }

    stream->_offset = new_offset;

    stream->_index = 0;

    off_t result = lseek(stream->_fileno, new_offset, SEEK_SET);

    if (result == -1) {
        stream->_errflag = 1;
        const char* errorMessage = "Error seeking file\n";
        write(STDERR_FILENO, errorMessage, sizeof(errorMessage) - 1);
        return SO_EOF;
    }

    return 0;
}