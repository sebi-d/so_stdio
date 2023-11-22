#include "so_stdio.h"
#include <bits/unistd.h>

int so_fgetc(SO_FILE *stream) {

    if(stream == NULL) {
        return SO_EOF;
    }

    if(stream->_index == BUFFER_SIZE) {
        size_t bytesRead = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
        if(bytesRead > 0) {
            stream->_index = 0;
        } 
        else {
            stream->_errflag = 1;
            const char* error_message = "error reading from file\n";
            write(2, error_message, sizeof(error_message) - 1);
            return SO_EOF;
        }
    }

    return (int)(stream->_buffer[stream->_index++]);
}