#include "so_stdio.h"

int so_fputc(int c, SO_FILE *stream) {
    
    if(stream == NULL) {
        return SO_EOF;
    }

    if (stream->_index == BUFFER_SIZE) {
        ssize_t bytesWritten = write(stream->_fileno, stream->_buffer, BUFFER_SIZE);

        if(bytesWritten < 0) {
            stream->_errflag = 1;
            const char* error_message = "error writing to file\n";
            write(2, error_message, sizeof(error_message) - 1);
            return SO_EOF;
        }

        stream->_index = 0;
    }

    stream->_buffer[stream->_index++] = (char)c;

    return c;

}
