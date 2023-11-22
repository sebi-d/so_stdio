#include "src/so_stdio.h"
#include <stdio.h>

int main() {

    SO_FILE *f = so_fopen("sample.txt", "r");
    
    char buffer[1024];
    
    int bytesRead = so_fread(f, 1, 1024, f);

    printf("%s", buffer);

    so_fclose(f);

    

    
    
    return 0;
}