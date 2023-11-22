#include "so_stdio.h"
#include <string.h>

int so_fclose(SO_FILE *stream){
    if(stream == NULL) {
        return SO_EOF;
    }

    memset(stream->_buffer, 0, BUFFER_SIZE);
    close(stream->_fileno);
    return 0;
}
