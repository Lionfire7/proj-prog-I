#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"
#include "admin_func.h"

int espacoAdmin (llist *head) {

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
        case 2 :
            alterarDadosCurso ();
            break;
        case 3 :
            alterarStatusCurso ();
            break;

        case 4 :
            listarCursosA ();
            break;

        case 5 :
            listarCursosEscola();
            break;
        case 6 :
            listarCandidatosCurso();
            break;
        case 7 :
            fecharCandidaturas();
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


