#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu (){

    int opcao;

    do
    {
        printf("Bem Vindo ao Menu Principal\n");
        printf("\n1 - Administrador");
        printf("\n2 - Utilizador");
        printf("\n3 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            
            //admin

            break;

        case 2:

            //utilizador

            break;

        case 0:

            printf("A sair...\n");

            return 0;

            break;
        
        default:
            break;
        }

    } while (opcao != 0);
    


}
