#include "so_stdio.h"

int so_fileno(SO_FILE *stream) {
    if(stream == NULL) {
        return SO_EOF;
    }
    
    return stream->_fileno;
}