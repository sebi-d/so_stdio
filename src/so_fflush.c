#include "so_stdio.h"

int so_fflush(SO_FILE *stream) {

    if(stream->_index > 0) {
        size_t result = write(stream->_fileno, stream->_buffer, stream->_index);

        if(result < 0) {
            stream->_errflag = 1;
            const char* errorMessage = "Error writing to file\n";
            write(2, errorMessage, sizeof(errorMessage) - 1);
            return SO_EOF;
        }

        stream->_index = 0;
        stream->_offset = lseek(stream->_fileno, 0, SEEK_CUR);
    }

    return 0;
}