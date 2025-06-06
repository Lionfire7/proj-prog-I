#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"

int addCurso () {

    CURSOS cursos;

    FILE *f = fopen("cursos.bin", "ab");
    if (f == NULL) {
        printf("\nErro ao abrir cursos.bin\n");
        return -1;
    }

    printf("\e[1;1H\e[2J");
    printf("\n--- | Adicionar Curso | ---\n");
    printf("\nEscreva aqui o nome completo do curso: ");
    fgets(cursos.curso, sizeof(cursos.curso), stdin);
    cursos.curso[strcspn(cursos.curso, "\n")] = '\0';


    printf("\nEscreva a sigla do Curso: ");
    fgets(cursos.tag, sizeof(cursos.tag), stdin);
    cursos.tag[strcspn(cursos.tag, "\n")] = '\0';

    printf("\nNumero de vagas do curso: ");
    scanf("%d", &cursos.nvagas);

    printf("\nEscola: ");
    fgets(cursos.escola, sizeof(cursos.escola), stdin);
    cursos.escola[strcspn(cursos.escola, "\n")] = '\0';

    printf("\nStatus:\n 1 - Aberto   /   2 - Não Aberto\n");
    printf("\nEscreva aqui o status do curso: ");
    scanf("%d", &cursos.status);

    fwrite(&cursos, sizeof(cursos), 1, f);
    fclose(f);

    printf("\e[1;1H\e[2J");

    printf("\nCurso registado com sucesso...\n\n");

    return 0;
    
}

void alterarDadosCurso() {
    CURSOS cursos[MAX_CURSOS];
    char tag[10] = 0;
    int i = 0, found = 0;

    printf("\n Escreva a TAG no curso a alterar: ");
    scanf("%s", tag);
    getchar(); 

    FILE *f = fopen("cursos.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir cursos.bin\n");
        return -1;
    }

    while (fread(&cursos[i], sizeof(CURSOS), 1, f) == 1) {
        if (strcmp(cursos[i].tag, tag) == 0) {
            printf("\e[1;1H\e[2J");
            found = 1;
            printf("\n--- | Alterar Dados de Curso | ---\n");
            printf("\nEscreva aqui o nome completo do curso: ");
            fgets(cursos[i].curso, sizeof(cursos[i].curso), stdin);
            cursos[i].curso[strcspn(cursos[i].curso, "\n")] = '\0';

            printf("\nEscola: ");
            fgets(cursos[i].escola, sizeof(cursos[i].escola), stdin);
            cursos[i].escola[strcspn(cursos[i].escola, "\n")] = '\0';


            printf("\nEscreva a sigla do Curso: ");
            fgets(cursos[i].tag, sizeof(cursos[i].tag), stdin);
            cursos[i].tag[strcspn(cursos[i].tag, "\n")] = '\0';

            printf("\nNumero de vagas do curso: ");
            scanf("%d", &cursos[i].nvagas);
            break;
        }
        i = i+1;

    }

    if (found == 0) {
        printf("\nCurso não encontrado.\n");
        return;
    }

    fclose(f);

    FILE *f = fopen("cursos.bin", "w+b");
    if (f == NULL) {
        printf("\nErro ao abrir o ficheiro cursos.bin.\n");
        return;
    }

    while (i < MAX_CURSOS && cursos[i].tag[0] != '\0') {
        fwrite(&cursos[i], sizeof(CURSOS), 1, f);
        i = i + 1;
    }

    fclose(f);
    printf("\e[1;1H\e[2J");
    return;
}

int compareCursos(const void *a, const void *b) {
    const CURSOS *cursoA = (const CURSOS *)a;
    const CURSOS *cursoB = (const CURSOS *)b;
    return strcmp(cursoA->curso, cursoB->curso);
}

void listarCursosA () {
    FILE *fp = fopen("cursos.bin", "rb");
    if (fp == NULL) {
        printf("Erro ao abrir cursos.bin");
        return;
    }

    CURSOS cursos[MAX_CURSOS];
    int total = fread(cursos, sizeof(CURSOS), MAX_CURSOS, fp);
    fclose(fp);

    if (total == 0) {
        printf("Nenhum curso encontrado.\n");
        return;
    }

    qsort(cursos, total, sizeof(CURSOS), compareCursos);

    printf("\e[1;1H\e[2J");
    printf("Cursos ordenados alfabeticamente:\n\n");
    for (int i = 0; i < total; i++) {
        printf("%s (%s) - Candidatos: %d, Vagas: %d, Escola: %s, Status: %d\n",
               cursos[i].curso, cursos[i].tag, cursos[i].candidatos, cursos[i].nvagas, cursos[i].escola, cursos[i].status);
    }

    printf("\n");
}

void alterarStatusCurso() {
    CURSOS cursos[MAX_CURSOS];
    char tag[10] = 0;
    int i = 0, found = 0;

    printf("\n Escreva a TAG no curso a alterar: ");
    scanf("%s", tag);
    getchar(); 

    FILE *f = fopen("cursos.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir cursos.bin\n");
        return -1;
    }

    while (fread(&cursos[i], sizeof(CURSOS), 1, f) == 1) {
        if (strcmp(cursos[i].tag, tag) == 0) {
            printf("\e[1;1H\e[2J");
            found = 1;
            printf("\n--- | Alterar Estado do Curso | ---\n");
            printf("\nStatus:\n 1 - Aberto   /   2 - Não Aberto\n");
            printf("\nEscreva aqui o status do curso: ");
            scanf("%d", &cursos[i].status);
            break;
        }
        i = i+1;

    }

    if (found == 0) {
        printf("\nCurso não encontrado.\n");
        return;
    }

    fclose(f);

    FILE *f = fopen("cursos.bin", "w+b");
    if (f == NULL) {
        printf("\nErro ao abrir o ficheiro cursos.bin.\n");
        return;
    }

    while (i < MAX_CURSOS && cursos[i].tag[0] != '\0') {
        fwrite(&cursos[i], sizeof(CURSOS), 1, f);
        i = i + 1;
    }

    fclose(f);
    printf("\e[1;1H\e[2J");
    return;
}

void listarCursosEscola() {
    CURSOS cursos;
    char escola[10];
    int found = 0;

    printf("\n Escreva a Escola do curso a listar: ");
    scanf("%s", escola);
    getchar();

    FILE *f = fopen("cursos.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir cursos.bin\n");
        return -1;
    }

    while (fread(&cursos, sizeof(CURSOS), 1, f) == 1) {
        if (strcmp(cursos.escola, escola) == 0) {
            found = 1;
            printf("%s (%s) - Candidatos: %d, Vagas: %d, Escola: %s, Status: %d\n",
            cursos.curso, cursos.tag, cursos.candidatos, cursos.nvagas, cursos.escola, cursos.status);
            break;
        }
    }

    if (found == 0) {
        printf("\n Escola não encontrada.\n");
        return;
    }
    fclose(f);   
    return;
}

void listarCandidatosCurso (llist **head){
    
}

void fecharcandidaturas(){
    FILE *f = fopen("aberto.bin", "wb");

    if (f == NULL) {
        printf("\nErro ao abrir o ficheiro aberto.bin.\n");
        return;
    }

    int status = 0; 

    fwrite(&status, sizeof(int), 1, f);
    
    fclose(f);

    return;
}