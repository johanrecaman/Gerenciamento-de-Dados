#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char cpf[12];  
    char nome[100]; 
} Record;

int main() {
    FILE *txt, *bin;
    Record records[20];

    txt = fopen("input.txt", "r");
    if (!txt) {
        perror("Error opening input file");
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        if (fscanf(txt, "%11s %99[^\n]", records[i].cpf, records[i].nome) != 2) {
            perror("Error reading from input file");
            fclose(txt);
            return 1;
        }
    }

    fclose(txt);

    bin = fopen("output.bin", "wb");
    if (!bin) {
        perror("Error opening output file");
        return 1;
    }

    fwrite(records, sizeof(Record), 20, bin);

    fclose(bin);

    printf("Records written to output.bin successfully.\n");

    return 0;
}
