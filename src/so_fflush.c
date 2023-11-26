#include "so_stdio.h"
#include <string.h>

int so_fflush(SO_FILE *stream) {

    if (stream == NULL || stream->_buffer == NULL) {
        return SO_EOF;
    }

    if(stream->_size > 0) {
        while(stream->_size > 0) {
            size_t _result = write(stream->_fileno, stream->_buffer, stream->_size);
            if(_result <= 0) {
                stream->_errflag = 1;
                return SO_EOF;
            }
            memmove(stream->_buffer, stream->_buffer + _result, stream->_size - _result);
            memset(stream->_buffer + stream->_size -_result, 0, _result);
            stream->_size -= _result;
            
        }

        memset(stream->_buffer, 0, BUFFER_SIZE);
        stream->_size = 0;
        stream->_index = 0;
    }

    return 0;
}