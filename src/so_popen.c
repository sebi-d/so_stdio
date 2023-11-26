#include "so_stdio.h"
#include <sys/types.h>
#include <string.h>

SO_FILE *so_popen(const char *command, const char *type) {
    
    int _fd = 0;
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        return NULL;
    }

    pid_t pid = fork();

    if (pid == -1) {
        close(pipe_fd[READ_END]);
        close(pipe_fd[WRITE_END]);
        return NULL;
    } else if (pid == 0) {
        if(strcmp(type, "r") == 0) {
            close(pipe_fd[READ_END]);
			dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
			close(pipe_fd[WRITE_END]);
        } else if (strcmp(type, "w") == 0) {
            close(pipe_fd[WRITE_END]);
			dup2(pipe_fd[READ_END], STDIN_FILENO);
			close(pipe_fd[READ_END]);
        }
        execlp("/bin/sh", "sh", "-c", command, (char *)NULL);
        exit(1);
    } else {
        if(strcmp(type, "r") == 0) 
        {
            close(pipe_fd[WRITE_END]);
            _fd = pipe_fd[READ_END];
        }
        else 
        { 
            close(pipe_fd[READ_END]);
            _fd = pipe_fd[WRITE_END];
        }

	}

    SO_FILE *new_file = (SO_FILE *)calloc(1, sizeof(SO_FILE));
    new_file->_fileno = _fd;
    new_file->_pid = pid;
    if (!new_file) {
        return NULL;
    }
    new_file->_buffer = (char*) calloc (BUFFER_SIZE, sizeof(char));
    
    return new_file;
}