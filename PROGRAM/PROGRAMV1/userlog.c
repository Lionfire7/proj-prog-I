#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

void printAllCursos() {

    CURSOS curso;
    char curso_dump[50];
    FILE *f = fopen("cursos.bin", "rb");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro cursos.bin\n");
        return;
    }

    printf("\n--- Todos os Cursos ---\n");

    while (fread(&curso_dump, sizeof(CURSOS), 1, f) == 1) {
        printf("%s", curso_dump);

    fclose(f);
    }

}

/*int load_cursos () {
    
    CURSOS cursos;
    fpos_t pos;
    int found = 0;
    char cursos_temp = NULL;

    static char selected_tag [50];

    FILE *f = fopen ("cursos.bin", "rb");
    if (f == NULL)
    {
        printf("\nNao foi possivel abrir cursos.bin\n");
        return -1;
    }
    do
    {
        fsetpos (f, pos);
        cursos_temp = fread (&cursos, sizeof(CURSOS), 1, f);
        fgetpos(f,&pos);
        
    } while (fread (&cursos, sizeof(CURSOS), 1, f) != NULL);
    

}*/

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

    printf("Crie um username: ");
    scanf("%s", user.sign_username);

    printf("Crie uma password: ");
    scanf("%s", user.sign_password);

    char *selected_tag = chooseCurso ();
    if (selected_tag == NULL)
    {
        printf("\mErro ao colocar sigla escolhida\n");
        return -1;
    }

    //substituir
    strcpy(user.cursocandidato, selected_tag);

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

char *chooseCurso (void) {

    CURSOS cursos;
    USERINFO info;

    int found = 0;

    static char selected_tag [50];

    FILE *f = fopen ("cursos.bin", "rb");
    if (f == NULL)
    {
        printf("\nNao foi possivel abrir cursos.bin\n");
        return -1;
    }

    printf("\e[1;1H\e[2J");
    printf("\n--- | Cursos Disponíveis | ---\n");

    while (fread(&cursos, sizeof(CURSOS), 1, f) == 1)
    {
        if (cursos.status == 1)
        {
            printf("\n-> Curso: %s    |   Sigla: %s     \n", cursos.curso, cursos.tag);
        }
    }
    
    rewind (f);

    printf("Insira a Sigla do curso ao qual se pretende candidatar: ");
    scanf("%s", selected_tag);

    while (fread (&cursos, sizeof(CURSOS), 1, f) == 1) {

        if (cursos.status == 1 && strcmp (selected_tag, cursos.tag) == 0)
        {
            found = 1;
            break;
        }

    }

    if (!found)
    {
        printf("\nSigla Invalida, tente outra vez\n");
    }

    fclose (f);
    return selected_tag;
}