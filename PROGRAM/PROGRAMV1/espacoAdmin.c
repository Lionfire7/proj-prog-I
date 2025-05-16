#include <stdio.h>
#include "auth.h"

int AdminLog () {

    //admin log

    ADMININFO admin;

    char input_username [100];
    char input_password [100];

    FILE *f = fopen("admin.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir base de dados de utilizadores.\n");
        return -1;
    }

    do {

        printf("\n\nInsira o seu username (0 para voltar): ");
        scanf("%49s", input_username);

        if (strcmp(input_username, "0") == 0) {
            fclose(f);
            return 0;
        }

        int found = 0;
        rewind(f); // Go back to start of file

        while (fread(&admin, sizeof(ADMININFO), 1, f) == 1) {
            if (strcmp(input_username, admin.username) == 0) {
                found = 1;
                int trycounter = 0;

                do {
                    printf("\nInsira a sua password: ");
                    scanf("%49s", input_password);

                    if (strcmp(input_password, admin.password) == 0) {
                        printf("\e[1;1H\e[2J");
                        printf("\nLogin bem-sucedido. \nBem-vindo, Admin\n\n");

                        //espacouser

                        espacoAdmin();

                        fclose(f);
                        return 0;
                    } else {
                        printf("\nPassword incorreta.\n");
                        trycounter++;
                    }

                } while (trycounter < 3);

                printf("\nExcedeu o número de tentativas.\n");
                fclose(f);
                return 0;
            }
        }

        if (!found) {
            printf("\e[1;1H\e[2J");
            printf("\nUsername não encontrado. Tente novamente.\n");
        }

    } while (strcmp(input_username, "0") != 0);

    fclose(f);
    return 0;
}

int espacoAdmin () {

    ADMININFO admin;

    int op = 0;

    do
    {   
        printf("--- | Admin Menu | ---\n");
        printf("\n1 - Acrescentar Curso\n");
        printf("2 - Alterar dados de curso\n");
        printf("3 - Alterar status de curso\n");
        printf("4 - Listar Cursos p/ nome\n");
        printf("5 - Alterar dados p/ escola\n");
        printf("6 - Listar candidatos de curso\n");
        printf("7 - Fechar Candidaturas\n");
        printf("8 - Seriar candidatos\n");
        printf("9 - Imprimir lista de candidatos\n");
        printf("10 - Imprimir lista de colocados p/ curso\n");
        printf("11 - Imprimir lista de colocados p/ escola\n");
        printf("12 - Analise de candidaturas\n");
        printf("\n0 - Voltar ao menu\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &op);
        while (getchar() != '\n'); // limpa o buffer até ao \n (tava a fazer o programa repetir addCurso 2x )

        switch (op)
        {
        case 1 :
            
            addCurso ();
            
            break;

        case 0 :

            return 0;

            break;
        
        default:
            break;
        }

    } while (op != 0);
    

    return 0;

}

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

    printf("\nStatus:\n 1 - Ativo   /   2 - Inativo\n");
    printf("\nEScreva aqui o status do curso: ");
    scanf("%d", &cursos.status);

    fwrite(&cursos, sizeof(cursos), 1, f);
    fclose(f);

    printf("\e[1;1H\e[2J");

    printf("\nCurso registado com sucesso...\n\n");

    return 0;
    
}

int listCursos () {

    //listar cursos por ordem alfabetica
    
}
