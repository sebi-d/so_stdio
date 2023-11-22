#include "so_stdio.h"

long so_ftell(SO_FILE *stream) {

    if(stream == NULL) {
        return SO_EOF;
    }
    
    return (long)(stream->_index + stream->_offset);
}