#include "so_stdio.h"
#include <sys/types.h>

SO_FILE *so_popen(const char *command, const char *type) {
    SO_FILE *new_file = (SO_FILE *)malloc(sizeof(SO_FILE));
    if (!new_file) {
        
        return NULL;
    }

    if (pipe(new_file->pipe_fd) == -1) {
        //failed to create pipe
        free(new_file);
        return NULL;
    }

    pid_t pid = fork();

    if (pid == -1) {
        //perror("Failed to fork process");
        close(new_file->pipe_fd[READ_END]);
        close(new_file->pipe_fd[WRITE_END]);
        free(new_file);
        return NULL;
    }

    if (pid == 0) { 
        
        close(new_file->pipe_fd[READ_END]);

        dup2(new_file->pipe_fd[1], STDOUT_FILENO);

        close(new_file->pipe_fd[WRITE_END]);

        execl("/bin/sh", "sh", "-c", command, (char *)NULL);

        // If execl fails, exit the child process
        //perror("Failed to execute command");
        exit(EXIT_FAILURE);
    } else { 
        
        close(new_file->pipe_fd[WRITE_END]);

        new_file->_errflag = 0;
        new_file->_offset = 0;
        new_file->_index = 0;

        return new_file;
    }
}