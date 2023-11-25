#include "so_stdio.h"
#include <string.h>

int so_fflush(SO_FILE *stream) {

    if(stream->_index > 0) {
        size_t _result = write(stream->_fileno, stream->_buffer, stream->_index);

        if(_result <= 0) {
            stream->_errflag = 1;
            return SO_EOF;
        }
        memset(stream->_buffer, 0, BUFFER_SIZE);
        stream->_index = 0;
    }
    return 0;
}