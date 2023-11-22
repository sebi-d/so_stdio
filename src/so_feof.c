#include "so_stdio.h"

int so_feof(SO_FILE *stream) {
    return (stream->_index == 0 && lseek(stream->_fileno, 0, SEEK_CUR) == stream->_offset);
}