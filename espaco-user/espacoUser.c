#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "main.c"

int listcandidatura() {

    LOGIN_USER user;
    
    FILE *f = fopen("users.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    

}
int espacoUser() {

    int opcao = 0;

    do {
        
        printf("\n1 - Listar Informação de candidatura\n");
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