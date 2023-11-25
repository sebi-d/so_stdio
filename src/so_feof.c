#include "so_stdio.h"

int so_feof(SO_FILE *stream) {
    
    return stream->_eof;
}