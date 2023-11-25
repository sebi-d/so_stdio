#include "so_stdio.h"

int so_fputc(int c, SO_FILE *stream) {
    
    if(stream == NULL) {
        return SO_EOF;
    }

    stream->_buffer[stream->_index++] = (unsigned char)c;

    //full buffer
    if(stream->_index == BUFFER_SIZE) {
        if(so_fflush(stream) < 0) {
            return SO_EOF;
        }
    }
    
    stream->_io = WRITE;
    stream->_offset++;
    return (int)c;
}