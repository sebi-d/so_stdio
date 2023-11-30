This contains a function suite for the Operating System stdio library for Linux (`libso_stdio.so`).
_______________________________________________________________________________________________________

Project Structure

 so_stdio/
 |	
 |____src/____so_fclose.c
 |	 |_____so_feof.c
 |	 |_____so_ferror.c
 |	 |_____so_fflush.c
 |	 |_____so_fgetc.c
 |	 |_____so_fileno.c
 |	 |_____so_fopen.c
 |	 |_____so_fputc.c
 |	 |_____so_fread.c
 |	 |_____so_fseek.c
 |	 |_____so_ftell.c
 |	 |_____so_fwrite.c
 |	 |_____so_pclose.c
 |	 |_____so_popen.c
 |	 |_____so_stdio.h
 |
 |_____Makefile
 |_____readme.md

_______________________________________________________________________________________________________
Header

struct _so_file {
    int _fileno; 	      //file descriptor
    int _flags; 	      //file creation flags
    char *_buffer; 	    //IO buffering
    int _index; 	      //buffer iteration
    int _size; 		      //keeks buffer size
    int _permissions; 	//file permissions
    int _offset; 	      //file offset
    int _errflag; 	    // error-checking flag
    int _io; 		        //keeps the last file operation (0 -> READ, 1 -> WRITE)
    int _eof; 		      //reach the end of the file 
    int _pid; 		      //associated pid
};

_______________________________________________________________________________________________________
Build

make

_______________________________________________________________________________________________________
Cleanup

make clean