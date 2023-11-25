#include "so_stdio.h"
#include <sys/types.h>

SO_FILE *so_popen(const char *command, const char *type) {
    // SO_FILE *new_file = (SO_FILE *)calloc(1, sizeof(SO_FILE));
    // new_file->_fileno = -1;
    // if (!new_file) {
    //     return NULL;
    // }

    // if (pipe(new_file->pipe_fd) == -1) {
    //     //failed to create pipe
    //     free(new_file);
    //     return NULL;
    // }

    // pid_t pid = fork();

    // if (pid == -1) {
    //     //perror("Failed to fork process");
    //     close(new_file->pipe_fd[READ_END]);
    //     close(new_file->pipe_fd[WRITE_END]);
    //     so_pclose(new_file);
    //     free(new_file);
    //     return NULL;
    // }

    // if (pid == 0) { 
        
    //     close(new_file->pipe_fd[READ_END]);

    //     dup2(new_file->pipe_fd[WRITE_END], STDOUT_FILENO);

    //     close(new_file->pipe_fd[WRITE_END]);

    //     execl("/bin/sh", "sh", "-c", command, (char *)NULL);

    //     return SO_EOF;

    // } else { 
        
    //     close(new_file->pipe_fd[WRITE_END]);

    //     new_file->_errflag = 0;
    //     new_file->_offset = 0;
    //     new_file->_index = 0;

    //     return new_file;
    // }
    return NULL;
}