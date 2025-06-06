#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "espacoUser.h"
#include "espacoAdmin.h"

void listcandidatura(USERINFO temp) {
    printf("\e[1;1H\e[2J");

    printf("========== CANDIDATURA ==========\n");
    printf("ID: %d\n", temp.id);
    printf("Username: %s\n", temp.username);
    printf("Nome: %s\n", temp.nome);
    printf("Cartão de Cidadão: %s\n", temp.cc);
    printf("NIF: %s\n", temp.nif);
    printf("Data de Nascimento: %s\n", temp.data_nasc);
    printf("Curso: %s\n", temp.curso);
    printf("Escola: %s\n", temp.escola);
    printf("Média: %.2f\n", temp.media);
    printf("Curso Candidato: %s\n", temp.cursocandidato);
    printf("=================================\n");

    return;

}

int imprimircandidatura (USERINFO temp){

    printf("\e[1;1H\e[2J");

    FILE *out = fopen("candidatura.txt", "w");
        if (out == NULL) {
            printf("Erro ao criar o ficheiro candidatura.txt\n");
            fclose(out);
            return -1;
          }

    fprintf(out, "========== CANDIDATURA ==========\n");
    fprintf(out, "ID: %d\n", temp.id);
    fprintf(out, "Username: %s\n", temp.username);
    fprintf(out, "Nome: %s\n", temp.nome);
    fprintf(out, "Cartão de Cidadão: %s\n", temp.cc);
    fprintf(out, "NIF: %s\n", temp.nif);
    fprintf(out, "Data de Nascimento: %s\n", temp.data_nasc);
    fprintf(out, "Curso: %s\n", temp.curso);
    fprintf(out, "Escola: %s\n", temp.escola);
    fprintf(out, "Média: %.2f\n", temp.media);
    fprintf(out, "Curso Candidato: %s\n", temp.cursocandidato);
    fprintf(out, "=================================\n");


    const char *old_name = "candidatura.txt";
    char new_name[100];
    snprintf(new_name, sizeof(new_name), "%s__candidatura.txt", temp.username);

    if (rename(old_name, new_name) == 0) {
        printf("Ficheiro renomeado com sucesso para %s\n", new_name);
    } else {
        perror("Erro ao renomear o ficheiro");
    }

    printf("\e[1;1H\e[2J");

    printf("Candidatura exportada com sucesso para 'user_candidatura.txt'.\n");
    printf("O ficheiro encontra-se guardado na mesma pasta onde se encontra o programa\n");
    fclose(out);

    return 0;
}

int signup() {
    int aberto = 0;

    FILE *f = fopen("aberto.bin", "rb");

    if (fread(&aberto, sizeof(int), 1, f) == 1) {
        if (aberto != 0) {
            printf("\nAs candidaturas fecharam.\n");
            fclose(f);
            return -1;
        }
    }
    fclose(f);

    USERINFO user;
    CURSOS cursos;

    printf("\e[1;1H\e[2J");

    printf("\e[1;1H\e[2J");

    getchar();

    printf("\n\n--- Registo de Novo Utilizador ---\n");

    printf("Crie um username: ");
    scanf("%s", user.username);

    printf("Crie uma password: ");
    scanf("%s", user.password);

    int previousid = 0;

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

    getchar();

    printf("Escola: ");
    fgets(user.escola, sizeof(user.escola), stdin);
    user.escola[strcspn(user.escola, "\n")] = '\0';

    printf("\e[1;1H\e[2J");

    FILE *fc = fopen("cursos.bin", "rb");
    if (fc == NULL) {
        printf("Erro ao abrir o ficheiro cursos.bin\n");
        return -1;
    }

    printf("\e[1;1H\e[2J");
    printf("\n--- Todos os Cursos ---\n\n");

    while (fread(&cursos, sizeof(CURSOS), 1, fc) == 1) {
        printf("%s (%s) - Candidatos: %d, Vagas: %d, Escola: %s, Status: %d\n",
        cursos.curso, cursos.tag, cursos.candidatos, cursos.nvagas, cursos.escola, cursos.status);
    }

    fclose(fc);

    printf("\n\nEscolhe um curso com status '1' (sigla do curso): ");
    scanf("%s", user.cursocandidato);
    user.cursocandidato[strcspn(user.cursocandidato, "\n")] = '\0';

    getchar();  

    FILE *fuserid = fopen("userid.bin", "a+b");
    if (fuserid == NULL) {
        printf("\nErro ao abrir o ficheiro userid.bin.\n");
        return -1;
    }

    while (fread(&previousid, sizeof(USERINFO), 1, fuserid) == 1)
    {
        user.id = previousid + 1;
    }
    fprintf(fuserid, "%d", user.id);
    fclose(fuserid);

    FILE *f = fopen("users.bin", "a+b");
    if (f == NULL) {
        printf("\nErro ao abrir o ficheiro users.bin.\n");
        return -1;
    }


    fwrite(&user, sizeof(user), 1, f);
    fclose(f);


   printf("\nUtilizador registado com sucesso.\n");
    return 0;
}

int userlog (llist *head) { 

    char input_username[MAX_LEN];
    char input_password[MAX_LEN];

    USERINFO temp;

    head = (llist *)malloc(sizeof(llist));
    if (head == NULL) {
        printf("Erro ao alocar memória para a lista de utilizadores.\n");
        return -1;
    }
    
    FILE *f = fopen("users.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir base de dados de utilizadores.\n");
        return -1;
    }

    do {

        printf("\n\nInsira o seu username (0 para sair): ");
        scanf("%99s", input_username);

        if (strcmp(input_username, "0") == 0) {
            fclose(f);
            return 0;
        }

        int found = 0;
        
        rewind(f);

        while (fread(&temp, sizeof(USERINFO), 1, f) == 1) {
            head->userinfo = temp;
            if (strcmp(head->userinfo.username, input_username) == 0) {
                found = 1;
                int trycounter = 0;

                do {
                    printf("\nInsira a sua password: ");
                    scanf("%49s", input_password);

                    if (strcmp(input_password, head->userinfo.password) == 0) {
                        printf("\e[1;1H\e[2J");
                        printf("\nLogin bem-sucedido. \nBem-vindo, %s!\n\n", head->userinfo.nome);
                        if (strcmp(input_username, "admin") == 0) {
                            printf("\e[1;1H\e[2J");
                            printf("\nA entrar no espaço do Admin...\n");
                            fclose(f);
                            return espacoAdmin(&head);
                        }
                        fclose(f);
                        return espacoCandidato(head->userinfo);
                    } else {
                        printf("\nPassword incorreta.\n");
                        trycounter++;
                    }

                } while (trycounter < 3);

                printf("\nExcedeu o número de tentativas.\n");
                fclose(f);
                return 0;
            }
            head->next = (llist *)malloc(sizeof(llist));
            if (head->next == NULL) {
                printf("Erro ao alocar memória para o próximo utilizador.\n");
                fclose(f);
                return -1;
            }
            head = head->next;

        }

        if (!found) {
            int opcao;
            printf("\e[1;1H\e[2J");
            printf("\nUsername não encontrado. Deseja registrar-se?.\n");
            printf("1 - Sim\n");
            printf("0 - Não\n");
            scanf("%d", &opcao);
            switch (opcao)
            {
            case 1:
                signup();
                break;
            case 0:
                printf("\e[1;1H\e[2J");
                printf("\nA voltar a trás...\n");
                break;
                return 0;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
            }
        }

    } while (strcmp(input_username, "0") != 0);

    fclose(f);
    return 0;
}

void statusColocacao(USERINFO temp) {
    printf("\e[1;1H\e[2J");

    COLOC colocado;

    FILE *f = fopen("colocacao.bin", "rb");

    if (f == NULL) {
        printf("\nErro ao abrir base de dados de colocados.\n");
        return -1;
    }

    while (fread(&colocado, sizeof(COLOC),1, f) == 1) {
        if (strcmp(colocado.username, temp.username) == 0) {
        
        printf("ID: %d | Username: %s | Curso Candidato: %s | Status: %d\n", colocado.id, colocado.username, colocado.curso, colocado.status);
        }
        else {
            printf("Nenhum resultado encontrado para o utilizador %s.\n", temp.username);
        }
        
    }

    return;
}

void alterarDadosCandidatura(USERINFO temp){
    printf("\e[1;1H\e[2J");
    printf("\n--- Alterar Dados de Candidatura ---\n");

    printf("Nome Completo: ");
    while (getchar() != '\n');
    fgets(temp.nome, sizeof(temp.nome), stdin);
    temp.nome[strcspn(temp.nome, "\n")] = '\0';

    printf("Cartão de cidadão: ");
    scanf("%s", temp.cc);

    printf("NIF: ");
    scanf("%s", temp.nif);

    printf("Data de nascimento (dd-mm-aaaa): ");
    scanf("%s", temp.data_nasc);
    while (getchar() != '\n');

    printf("Curso: ");
    fgets(temp.curso, sizeof(temp.curso), stdin);
    temp.curso[strcspn(temp.curso, "\n")] = '\0';

    printf("Média: ");
    scanf("%f", &temp.media);

    getchar();

    printf("Escola: ");
    fgets(temp.escola, sizeof(temp.escola), stdin);
    temp.escola[strcspn(temp.escola, "\n")] = '\0';

    printf("\e[1;1H\e[2J");
    printf("\nDados de candidatura alterados com sucesso.\n");
        
    return;
}

