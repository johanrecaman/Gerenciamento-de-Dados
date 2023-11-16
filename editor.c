#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *bin;
    int *buffer;
    size_t size;

    bin = fopen("exemplo.bin", "rb");

    fseek(bin, 0, SEEK_END);
    size = ftell(bin);
    rewind(bin);

    size_t bytesRead = fread(buffer, 1, size, bin);

    
    printf("%d", buffer[0]);

    free(buffer);
    fclose(bin);

    return 0;
}