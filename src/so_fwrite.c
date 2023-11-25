#include "so_stdio.h"
#include <string.h>
#include <fcntl.h>

int min(int a, int b);

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    size_t to_write = size * nmemb;
    size_t _written = 0;
    size_t _remaining = 0;

    if(stream == NULL) {
        return 0;
    }
    
    if (so_ferror(stream)) {
        return 0;
    }

    //if append
    // if((stream->_flags & O_APPEND) == O_APPEND) {
    //     if(so_fseek(stream, 0, SEEK_END) < 0) {
    //         return 0;
    //     }
    // }

    //if +
    // if(stream->_flags && O_RDWR == O_RDWR) {
    //     if(stream->_io == READ) {

    //     }
    // }

    if(stream->_io == READ) {
        if(so_fseek(stream , 0, SEEK_CUR) < 0) {
            stream->_errflag = 1;
            return 0;
        }
    }

    while (_written < to_write) {
        if (stream->_index == BUFFER_SIZE) {
            if(so_fflush(stream) < 0) {
                return 0;
            }
        }
        _remaining = to_write - _written;
        int to_copy = min(_remaining, BUFFER_SIZE - stream->_index);
        memcpy(stream->_buffer, (char*)ptr + _written, to_copy);
        
        stream->_index += to_copy;
        _written += to_copy;
        stream->_offset += to_copy;
    }

    stream->_io = WRITE;
    return _written / size;
}