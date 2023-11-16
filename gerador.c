#include <stdio.h>

int main() {
    FILE *arquivo;

    arquivo = fopen("exemplo.bin", "wb");

    int number = 32;

    fwrite(&number, sizeof(int), 1, arquivo);

    return 0;
}
