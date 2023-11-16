#include <stdio.h>

int main() {
    FILE *arquivo;
    char linha[50]; //maximo 50c

    // abre o arquivo 
    arquivo = fopen("dados.txt", "r");

    // ve se abriu
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1; // se der erro, acaba
    }

    // le e printa
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    // fecha 
    fclose(arquivo);

    return 0; 
}
