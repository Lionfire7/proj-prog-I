#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

int login () { 
    LOGIN_USER user;
    USERINFO temp;

    FILE *f = fopen("users.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir base de dados de utilizadores.\n");
        return -1;
    }

    do {

        printf("\n\nInsira o seu username (0 para voltar): ");
        scanf("%49s", user.input_username);

        if (strcmp(user.input_username, "0") == 0) {
            fclose(f);
            return 0;
        }

        int found = 0;
        rewind(f); // Go back to start of file

        while (fread(&temp, sizeof(USERINFO), 1, f) == 1) {
            if (strcmp(user.input_username, temp.sign_username) == 0) {
                found = 1;
                int trycounter = 0;

                do {
                    printf("\nInsira a sua password: ");
                    scanf("%49s", user.input_password);

                    if (strcmp(user.input_password, temp.sign_password) == 0) {
                        printf("\e[1;1H\e[2J");
                        printf("\nLogin bem-sucedido. \nBem-vindo, %s!\n\n", temp.nome);

                        //espacouser

                        espacoUser();

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

    } while (strcmp(user.input_username, "0") != 0);

    fclose(f);
    return 0;
}

int signup() {
    USERINFO user;
    CURSOS cursos;

    printf("\e[1;1H\e[2J");

    printf("\n\n--- Registo de Novo Utilizador ---\n");

    printf("Nome Completo: ");
    while (getchar() != '\n');
    fgets(user.nome, sizeof(user.nome), stdin);
    user.nome[strcspn(user.nome, "\n")] = '\0';

    printf("Cartão de cidadão: ");
    scanf("%s", user.cc);

    printf("NIF: ");
    scanf("%s", user.nif);

    printf("Data de nascimento (dd-mm-aaaa): ");
    scanf("%s", user.data_nasc);
    while (getchar() != '\n');

    printf("Curso: ");
    fgets(user.curso, sizeof(user.curso), stdin);
    user.curso[strcspn(user.curso, "\n")] = '\0';

    printf("Média: ");
    scanf("%f", &user.media);

    //chooseCurso

    int found = 0;

    static char selected_tag [50];

    printf("\e[1;1H\e[2J");

    FILE *fc = fopen("cursos.bin", "rb");
    if (fc == NULL) {
        printf("Erro ao abrir o ficheiro cursos.bin\n");
        return;
    }

    printf("\e[1;1H\e[2J");

    printf("\n--- Todos os Cursos ---\n\n");

    while (fread(&cursos, sizeof(CURSOS), 1, fc) == 1) {
        printf("Curso: %s | Sigla: %s | Status: %d\n", cursos.curso, cursos.tag, cursos.status);
    }

    printf("\n\nEscolhe um curso com status '1' (sigla do curso): ");
    scanf("%s", user.cursocandidato);
    user.cursocandidato[strcspn(user.cursocandidato, "\n")] = '\0';

    fclose(fc);

    printf("\e[1;1H\e[2J");

    getchar ();

    printf("Crie um username: ");
    scanf("%s", user.sign_username);

    printf("Crie uma password: ");
    scanf("%s", user.sign_password);

    int previousid = 0;

    FILE *f = fopen("users.bin", "a+b");
    if (f == NULL) {
        printf("\nErro ao guardar utilizador.\n");
        return -1;
    }

    //user id

    rewind (f);
    while (fread(&user, sizeof(USERINFO), 1, f) == 1)
    {
        if (user.id > previousid)
        {
            previousid = user.id;
        }
    }

    //new id
    user.id = previousid + 1;

    fwrite(&user, sizeof(user), 1, f);
    fclose(f);

    printf("\nUtilizador registado com sucesso.\n");
    return 0;
}

int userlog() {
    int opcao;

    do {
        printf("\e[1;1H\e[2J");

        printf("\n\n--- MENU ---\n\n");
        printf("1 - Login\n");
        printf("2 - Registar\n");
        printf("0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                login();
                break;
            case 2:
                signup();
                break;
            case 0:
                printf("\e[1;1H\e[2J"); // Clear screen

                printf("\n\nA sair do programa...\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}