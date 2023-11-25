#include "so_stdio.h"
#include <string.h>

int min(int a, int b){
    if(a < b){
        return a;
    }
    return b;
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    
    size_t to_read = size * nmemb;
    size_t _bytes = 0;
    size_t _read = 0;

    if(stream == NULL) {
        return SO_EOF;
    }

    if(stream->_io == WRITE) {
        if(so_fflush(stream) < 0) {
            return 0;
        }
    }
    
    if (so_feof(stream) || so_ferror(stream)) {
        return SO_EOF;
    }

    while (_read < to_read) {
        if(so_feof(stream)) {
            break;
        }
        if(stream->_index == 0 || stream->_index == BUFFER_SIZE) {
            _bytes = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
            if (_bytes < 0) {
                stream->_errflag = 1;
                return SO_EOF;
            }

            if (_bytes == 0) {
                stream->_eof = 1;
            }  
            stream->_index = 0;          
        }
        
        int to_copy = min(to_read - _read, BUFFER_SIZE - stream->_index);
        memcpy((char*)ptr + _read, stream->_buffer + stream->_index, to_copy);
        stream->_index += to_copy;
        _read += to_copy;
    }

    stream->_io = READ;
    stream->_offset += _read;
    return _read / size;
}