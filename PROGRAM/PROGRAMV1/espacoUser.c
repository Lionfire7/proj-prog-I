#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "user_func.h"

int espacoCandidato(USERINFO temp) {

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

                listcandidatura(temp);

                break;

            case 2:

                alterarDadosCandidatura();

                break;

            case 3:

                statusColocacao(temp);

                break;

            case 4:

                imprimircandidatura (temp);
                
                break;

            case 0:

                printf("\e[1;1H\e[2J");
                printf("\nA voltar ao menu principal...\n\n");
                
                return 0;

                break;

            default:

                printf("\nOpção inválida. Tente novamente.\n");

                break;

        }

    } while (opcao != 0);

    return 0;
}