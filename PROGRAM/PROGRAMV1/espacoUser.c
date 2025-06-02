#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

int listcandidatura() {

    //listar

}

int listarusers () {

    CURSOS cursos;
    USERINFO users;

    FILE *f = fopen ("cursos.bin", "rb");
    if ("f == NULL")
    {
        printf("\nErro ao abrir cursos.bin\n");
    }

    //listar

    fclose(f);

    return;
}

int espacoUser() {

    int opcao = 0;

    do {
        
        printf("\n1 - Listar Informação de candidatura");
        printf("\n2 - Alterar dados de candidatura");
        printf("\n3 - Status de colocação");
        printf("\n4 - Imprimir dados de candidatura");
        printf("\n0 - Voltar ao menu principal\n");

        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:

                // listarInformacaoCandidatura();
                listcandidatura();

                break;

            case 2:

                // alterarDadosCandidatura();

                break;

            case 3:

                // statusColocacao();

                break;

            case 4:

                // imprimirDadosCandidatura();
                imprimircandidatura ();

                break;

            case 0:

                printf("\e[1;1H\e[2J");

                return 0;

                break;

            default:

                printf("\nOpção inválida. Tente novamente.\n");

                break;

        }

    } while (opcao != 0);

    return 0;
}

int imprimircandidatura (){

    printf("\e[1;1H\e[2J");

    USERINFO temp;
    CURSOS cursos;
    LOGIN_USER user;

    FILE *f = fopen("users.bin", "rb");
    if (f == NULL) {
        printf("\nErro ao abrir base de dados de utilizadores.\n");
        return -1;
    }

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

            FILE *out = fopen("candidatura.txt", "w");
            if (out == NULL) {
                printf("Erro ao criar o ficheiro candidatura.txt\n");
                fclose(f);
                return -1;
            }

            fprintf(out, "========== CANDIDATURA ==========\n");
            fprintf(out, "ID: %d\n", temp.id);
            fprintf(out, "Username: %s\n", temp.sign_username);
            fprintf(out, "Nome: %s\n", temp.nome);
            fprintf(out, "Cartão de Cidadão: %s\n", temp.cc);
            fprintf(out, "NIF: %s\n", temp.nif);
            fprintf(out, "Data de Nascimento: %s\n", temp.data_nasc);
            fprintf(out, "Curso: %s\n", temp.curso);
            fprintf(out, "Escola: %s\n", temp.escola);
            fprintf(out, "Média: %.2f\n", temp.media);
            fprintf(out, "Curso Candidato: %s\n", temp.cursocandidato);
            fprintf(out, "=================================\n");

            fclose(out);

            //rename file to user__candidatura.txt

            const char *old_name = "candidatura.txt";
            char new_name[100];
            snprintf(new_name, sizeof(new_name), "%s__candidatura.txt", temp.sign_username);

            if (rename(old_name, new_name) == 0) {
                printf("Ficheiro renomeado com sucesso para %s\n", new_name);
            } else {
                perror("Erro ao renomear o ficheiro");
            }

            printf("\e[1;1H\e[2J");

            printf("Candidatura exportada com sucesso para 'candidatura.txt'.\n");
            printf("O ficheiro encontra-se guardado na mesma pasta do programa\n");
            // eu aqui queria mudar o path do ficheiro, mas como temos OS's diferentes, seria complicado de mais fazer
            break;
        }
    }

        if (!found) {
            printf("\e[1;1H\e[2J");
            printf("\nUsername não encontrado. Tente novamente.\n");
        }

    fclose(f);
    return 0;
}