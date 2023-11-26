#include "so_stdio.h"
#include <bits/unistd.h>

int so_fgetc(SO_FILE *stream) {

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

    size_t _read = 0;
    //if empty buffer | full buffer
    if(stream->_size == 0 || stream->_index == stream->_size) {
        _read = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
        printf("read syscall\n");
        printf("fileno %i\n", stream->_fileno);
        if(_read == 0) {
            stream->_eof = 1;
            return SO_EOF;
        }
        
        if(_read < 0) {
            stream->_errflag = 1;
            return SO_EOF;
        }

        stream->_index = 0;
        stream->_size = _read;
    }
    
    unsigned char c;
    c = stream->_buffer[stream->_index];
    if(c != 0) {
        stream->_io = READ;
        stream->_offset++;
        stream->_index++;
        return c;
    }
    stream->_eof = 1;
    return SO_EOF;
}