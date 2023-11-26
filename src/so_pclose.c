#include "so_stdio.h"
#include <sys/wait.h>
#include <bits/waitflags.h>

int so_pclose(SO_FILE *stream) {

    if (stream == NULL) {
        return SO_EOF;
    }
    
    pid_t pid = stream->_pid;
	if(pid == -1) 
    {
        free(stream);
		return SO_EOF;
    }

    else {
        int check = so_fclose(stream);
        if(check < 0) 
        {
            free(stream->_buffer);
            free(stream);
            return SO_EOF;
        }

        int status;
        check = waitpid(pid, &status, 0);
        if(check < 0) 
        {
            free(stream->_buffer);
            free(stream);
            return check;
        }

        return status;
    }
}