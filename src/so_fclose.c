#include "so_stdio.h"
#include <string.h>

int so_fclose(SO_FILE *stream){

    if(stream == NULL) {
        return SO_EOF;
    }

    if(stream->_io == WRITE) {
        if(so_fflush(stream) < 0) {
            return SO_EOF;
        }
    }

    free(stream->_buffer);
    
    if(close(stream->_fileno) < 0) {
        stream->_errflag = 1;
        return SO_EOF;
    }

    free(stream);
    
    return 0;
}