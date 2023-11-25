#include "so_stdio.h"
#include <sys/wait.h>
#include <bits/waitflags.h>

int so_pclose(SO_FILE *stream) {

    // if (stream == NULL) {
    //     return SO_EOF;
    // }

    // if (close(stream->pipe_fd[READ_END]) == -1) {
    //     return SO_EOF;
    // }

    // int status;
    // if (waitpid(-1, &status, WNOHANG) == -1) {
    //     return SO_EOF;
    // }

    // return WEXITSTATUS(status);
    return SO_EOF;
}