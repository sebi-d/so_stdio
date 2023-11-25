#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "src/so_stdio.h"
#include <sys/stat.h>

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    
    size_t to_read = size * nmemb;
    size_t _bytes = 0;
    size_t _read = 0;

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

    while (_read < to_read) {
        if(so_feof(stream)) {
            break;
        }
        if(stream->_index == BUFFER_SIZE) {
            _bytes = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
            if (_bytes < 0) {
                stream->_errflag = 1;
                return SO_EOF;
            }

            if (_bytes == 0) {
                stream->_eof = 1;
            }  
            stream->_index = 0;          
        }
        
        int to_copy = min(to_read - _read, _bytes - stream->_index);
        memcpy((char*)ptr + _read, stream->_buffer + stream->_index, to_copy);
        stream->_index += to_copy;
        _read += to_copy;
    }

    stream->_io = READ;
    stream->_offset += _read;
    return _read / size;
}

int main() {
    SO_FILE *file_ = so_fopen("output.txt", "r");
    
    if (file_ == NULL) {
        //perror("Error opening file");
        return 1;
    }

    char buffer[17000];

    int result = so_fread(buffer, 1, 10, file_);
    result = so_fread(buffer, 1, 5, file_);


    so_fclose(file_);

    return 0;
}
