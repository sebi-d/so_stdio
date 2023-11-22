#include "so_stdio.h"
#include <string.h>

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream) {
    if(stream == NULL) {
        return SO_EOF;
    }
    size_t totalBytes = size * nmemb;
    size_t bytesWritten = 0;

    while(bytesWritten < totalBytes) {
        size_t result = write(stream->_fileno, (char*)ptr + bytesWritten, totalBytes - bytesWritten);

        if(stream->_index == BUFFER_SIZE) {
            size_t result = read(stream->_fileno, stream->_buffer, BUFFER_SIZE);

            if(result > 0) {
                stream->_index = 0;
            } else if (result == 0) {
                break;
            } else {
                stream->_errflag = 1;
                const char* errorMessage = "Error writing to file\n";
                write(2, errorMessage, sizeof(errorMessage) - 1);
                return bytesWritten / size; 
            }
        }

        size_t bytesToCopy = totalBytes - bytesWritten;
        size_t bytesAvailable = BUFFER_SIZE - stream->_index;

        if(bytesToCopy <= bytesAvailable) {
            memcpy(stream->_buffer + stream->_index, (const char *)ptr + bytesWritten, bytesToCopy);
            stream->_index += bytesToCopy;
            bytesWritten += bytesToCopy;
        } else {
            
            memcpy(stream->_buffer + stream->_index, (const char *)ptr + bytesWritten, bytesAvailable);
            stream->_index += bytesAvailable;
            bytesWritten += bytesAvailable;
        }
    }

    return bytesWritten / size;
}   