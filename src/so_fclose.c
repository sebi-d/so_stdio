#include "so_stdio.h"
#include <string.h>

int so_fclose(SO_FILE *stream){

    if(stream == NULL) {
        return SO_EOF;
    }

    if(stream->_io == WRITE) {
        if(so_fflush(stream) < 0) {
            if (stream->_buffer != NULL) {
                free(stream->_buffer);
            }
            free(stream);
            return SO_EOF;
        }
    }

    int close_status = close(stream->_fileno);

    if (stream->_buffer != NULL) {
        free(stream->_buffer);
    }
    free(stream);

    return close_status;
}