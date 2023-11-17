#include <stdio.h>
#include <stdint.h>

typedef struct {
    char cpf[12];
    char nome[100];
} Registro;

int main() {
    FILE *arquivoBinario = fopen("output.bin", "rb");
    FILE *arquivoTexto = fopen("results.txt", "w");

    if (arquivoBinario == NULL || arquivoTexto == NULL) {
        perror("Erro ao abrir os arquivos");
        return 1;
    }

    Registro registro;

    while (fread(&registro, sizeof(Registro), 1, arquivoBinario) == 1) {
        fprintf(arquivoTexto, "%s %s\n", registro.cpf, registro.nome);
    }

    fclose(arquivoBinario);
    fclose(arquivoTexto);

    return 0;
}
