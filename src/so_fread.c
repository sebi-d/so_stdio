#include "so_stdio.h"
#include <string.h>

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    
    if(stream == NULL) {
        return SO_EOF;
    }

    size_t totalBytes = size * nmemb;
    size_t bytesRead = 0;

    while (bytesRead < totalBytes) {
        size_t result = read(stream->_fileno, (char *)ptr + bytesRead, totalBytes - bytesRead);

        if(result < 0) {
            stream->_errflag = 1;
        }

        if(stream->_index == BUFFER_SIZE) {
            size_t result = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);
        
            if (result > 0) {
                stream->_index = 0;
            } else if (result == 0) {
                break; 
            } else {
                stream->_errflag = 1;
                const char* errorMessage = "Error reading from file\n";
                write(2, errorMessage, sizeof(errorMessage) - 1);
                return bytesRead / size;  
            }
        }

        size_t bytesToCopy = totalBytes - bytesRead;
        size_t bytesAvailable = BUFFER_SIZE - stream->_index;

        if (bytesToCopy <= bytesAvailable) {
            memcpy((char *)ptr + bytesRead, stream->_buffer + stream->_index, bytesToCopy);
            stream->_index += bytesToCopy;
            bytesRead += bytesToCopy;
        } else {
            memcpy((char *)ptr + bytesRead, stream->_buffer + stream->_index, bytesAvailable);
            stream->_index += bytesAvailable;
            bytesRead += bytesAvailable;
        }
    }

    return bytesRead/size;
}