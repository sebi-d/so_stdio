#include "so_stdio.h"
#include <string.h>
#include <fcntl.h>

int min(int a, int b);

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    size_t to_write = size * nmemb;
    size_t _written = 0;

    if (stream == NULL || stream->_buffer == NULL) {
        return 0;
    }
    
    if (so_ferror(stream)) {
        return 0;
    }

    while (_written < to_write) {
        if (stream->_size == BUFFER_SIZE) {
            if(so_fflush(stream) < 0) {
                stream->_errflag = 1;
                return 0;
            }
        }
        size_t _remaining = to_write - _written;
        int to_copy = min(_remaining, BUFFER_SIZE - stream->_size);
        memcpy(stream->_buffer + stream->_size, (char*)ptr + _written, to_copy);
        stream->_size += to_copy;
        _written += to_copy;
        stream->_offset += to_copy;
        stream->_io = WRITE;
    }

    return _written / size;
}