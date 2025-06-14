#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "auth.h"

//função verificar data

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(const char *dateStr) {
    if (strlen(dateStr) != 10)
        return 0;

    // verificar posição dos carateres (dd-mm-yyyy)

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (dateStr[i] != '-') return 0;
        } else {
            if (!isdigit(dateStr[i])) return 0;
        }
    }

    // transformar a string em numeros inteiros

    int day = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
    int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
    int year = 0;
    for (int i = 6; i <= 9; i++) {
        year = year * 10 + (dateStr[i] - '0');
    }

    // 1 < mês < 12
    if (month < 1 || month > 12) return 0;

    // Data de hoje

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;

    // YVerificar se o ano é válido (se estamos em 2025, 2026 não é válido)
    if (year < 1900 || year > currentYear) return 0;

    // Verifica o mês
    if (year == currentYear && month > currentMonth) return 0;

    // Dias no mês (mês bissexto ou não)
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (month == 2 && isLeapYear(year))
        daysInMonth[2] = 29;

    // Verificar dia
    if (day < 1 || day > daysInMonth[month]) return 0;

    // O dia não pode ser no futuro
    if (year == currentYear && month == currentMonth && day > currentDay) return 0;

    return 1;
}



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
    USERINFO temp;  // Temporary variable for reading existing users

    printf("\e[1;1H\e[2J");
    printf("\n\n--- Registo de Novo Utilizador ---\n");

    printf("Nome Completo: ");
    while (getchar() != '\n');  // Clear input buffer
    fgets(user.nome, sizeof(user.nome), stdin);
    user.nome[strcspn(user.nome, "\n")] = '\0';  // Remove trailing newline

    printf("Cartão de cidadão: ");
    scanf("%s", user.cc);

    printf("NIF: ");
    scanf("%s", user.nif);
    user.nif[strcspn(user.nif, "\n")] = '\0';

    do {
        printf("Data de nascimento (dd-mm-aaaa): ");
        scanf("%19s", user.data_nasc);
        while (getchar() != '\n'); // Clear leftover input

        if (!isValidDate(user.data_nasc)) {
            printf("Data inválida. Tente novamente.\n");
        }
    } while (!isValidDate(user.data_nasc));
    
    
    // Clear input buffer

    printf("Curso: ");
    fgets(user.curso, sizeof(user.curso), stdin);
    user.curso[strcspn(user.curso, "\n")] = '\0';

    printf("Média: ");
    scanf("%f", &user.media);

    // Display available courses
    FILE *fc = fopen("cursos.bin", "rb");
    if (fc == NULL) {
        printf("Erro ao abrir o ficheiro cursos.bin\n");
        return -1;
    }

    printf("\e[1;1H\e[2J");
    printf("\n--- Todos os Cursos ---\n\n");

    while (fread(&cursos, sizeof(CURSOS), 1, fc) == 1) {
        printf("Curso: %s | Sigla: %s | Status: %d\n", cursos.curso, cursos.tag, cursos.status);
    }

    fclose(fc);

    printf("\n\nEscolhe um curso com status '1' (sigla do curso): ");
    scanf("%s", user.cursocandidato);
    user.cursocandidato[strcspn(user.cursocandidato, "\n")] = '\0';

    getchar();  // Clear newline after scanf

    printf("Crie um username: ");
    scanf("%s", user.sign_username);

    printf("Crie uma password: ");
    scanf("%s", user.sign_password);

    FILE *f = fopen("users.bin", "a+b");
    if (f == NULL) {
        printf("\nErro ao guardar utilizador.\n");
        return -1;
    }

    int previousid = 0;

    rewind(f);
    while (fread(&temp, sizeof(USERINFO), 1, f) == 1) {
        if (temp.id > previousid) {
            previousid = temp.id;
        }
    }

    user.id = previousid + 1;

    fwrite(&user, sizeof(USERINFO), 1, f);
    fclose(f);

    //adicionar candidato à ncandidatos (+1)

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