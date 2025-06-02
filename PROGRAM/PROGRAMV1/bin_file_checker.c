#include <stdio.h>
#include <stdlib.h>

//checkar se o print dos cursos está a ser feito corretamente

typedef struct cursos {
    char curso[100];
    char tag[10];
    int status;
    int ncandidatos;
    int nvagas;
} CURSOS;

int main() {
    FILE *file = fopen("cursos.bin", "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    CURSOS curso;
    int count = 0;

    printf("Reading contents of cursos.bin:\n\n");

    while (fread(&curso, sizeof(CURSOS), 1, file) == 1) {
        printf("Curso #%d:\n", ++count);
        printf("  Nome:         %s\n", curso.curso);
        printf("  Tag:          %s\n", curso.tag);
        printf("  Status:       %d\n", curso.status);
        printf("  Candidatos:   %d\n", curso.ncandidatos);
        printf("  Vagas:        %d\n\n", curso.nvagas);
    }

    if (feof(file)) {
        printf("End of file reached.\n");
    } else {
        perror("Error reading file");
    }

    fclose(file);
    return 0;
}