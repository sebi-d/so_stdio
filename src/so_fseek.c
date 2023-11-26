#include "so_stdio.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int so_fseek(SO_FILE *stream, long offset, int whence) {
    
    if(stream->_io == WRITE) {
        if(so_fflush(stream) < 0) {
            return SO_EOF;
        }
    }

    if(whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END) {
        stream->_errflag = 1;
        return SO_EOF;
    }

    stream->_offset = lseek(stream->_fileno, offset, whence);
    if (stream->_offset == -1) {
        stream->_errflag = 1;
        return SO_EOF;
    }

    stream->_size = 0;
    stream->_index = 0;

    return 0;
}