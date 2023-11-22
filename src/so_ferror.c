#include "so_stdio.h"

int so_ferror(SO_FILE *stream) {
    //If the error indicator associated with the stream was set, 
    //the function returns a non-zero value 
    //else, it returns a zero value.
    return stream->_errflag;
}