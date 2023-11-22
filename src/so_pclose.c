#include "so_stdio.h"
#include <sys/wait.h>
#include <bits/waitflags.h>

int so_pclose(SO_FILE *stream) {

    if (stream == NULL) {
        return SO_EOF;
    }

    if (close(stream->pipe_fd[READ_END]) == -1) {
        //perror("Failed to close read end of the pipe");
        return SO_EOF;
    }

    // Wait for the child process to terminate
    int status;
    if (waitpid(-1, &status, WNOHANG) == -1) {
        
        //perror("Failed to wait for child process");
        return SO_EOF;
    }

    // Free the allocated memory

    return WEXITSTATUS(status);
}