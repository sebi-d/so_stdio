#include "./src/so_stdio.h"

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream){
    
    if(stream == NULL) {
        return 0;
    }
    
    if (so_feof(stream) || so_ferror(stream)) {
        return 0;
    }

    size_t to_read = size * nmemb;
    size_t _read = 0;

    while (bytesRead < totalBytes) {
        size_t result = read(stream->_fileno, stream->_buffer[stream->_index + bytesRead], BUFFER_SIZE);

        if(result < 0) {
            stream->_errflag = 1;
        }

        if(stream->_index == BUFFER_SIZE) {
            so_fflush(stream);
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

int main() {

    SO_FILE *f = so_fopen("sample.txt", "r");

    char buffer2[1024];
    
    int bytesRead = so_fread(buffer2, 1024, 1, f);


    so_fclose(f);

    return 0;
}