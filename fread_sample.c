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
        
        if(stream->_index == stream->_size) {
            _bytes = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
            if (_bytes < 0) {
                stream->_errflag = 1;
                return SO_EOF;
            }

            if (_bytes == 0) {
                stream->_eof = 1;
            }  
            stream->_index = 0;
            stream->_size = _bytes;          
        }
        
        int to_copy = min(to_read - _read, stream->_size - stream->_index);
        memcpy((char*)ptr + _read, stream->_buffer + stream->_index, to_copy);
        stream->_index += to_copy;
        _read += to_copy;
    }

    stream->_io = READ;
    stream->_offset += _read;
    return _read / size;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    size_t to_write = size * nmemb;
    size_t _written = 0;
    size_t _remaining = 0;

    if(stream == NULL) {
        return 0;
    }
    
    if (so_ferror(stream)) {
        return 0;
    }

    //if append
    // if((stream->_flags & O_APPEND) == O_APPEND) {
    //     if(so_fseek(stream, 0, SEEK_END) < 0) {
    //         return 0;
    //     }
    // }

    //if +
    // if(stream->_flags && O_RDWR == O_RDWR) {
    //     if(stream->_io == READ) {

    //     }
    // }

    if(stream->_io == READ) {
        if(so_fseek(stream , 0, SEEK_CUR) < 0) {
            stream->_errflag = 1;
            return 0;
        }
    }

    while (_written < to_write) {
        if (stream->_size == BUFFER_SIZE) {
            if(so_fflush(stream) < 0) {
                return 0;
            }
        }
        _remaining = to_write - _written;
        int to_copy = min(_remaining, BUFFER_SIZE - stream->_size);
        memcpy(stream->_buffer + stream->_size, (char*)ptr + _written, to_copy);
        stream->_size += to_copy;
        _written += to_copy;
        stream->_offset += to_copy;
    }

    stream->_io = WRITE;
    return _written / size;
}

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

int so_fflush(SO_FILE *stream) {

    size_t _result = write(stream->_fileno, stream->_buffer, stream->_size);

    if(_result <= 0) {
        stream->_errflag = 1;
        return SO_EOF;
    }
    memset(stream->_buffer, 0, BUFFER_SIZE);
    stream->_size = 0;
    stream->_index = 0;

    return 0;
}

int main() {
    SO_FILE *file_ = so_fopen("huge.txt", "r");
    SO_FILE *file2 = so_fopen("huge.txt", "w");
    
    if (file_ == NULL) {
        //perror("Error opening file");
        return 1;
    }

    char buffer[200000];


    
    int written = so_fwrite(buffer, 1, 200000, file2);
    int result2 = so_fclose(file2);

    return 0;
}
