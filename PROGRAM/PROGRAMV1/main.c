#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int menu (){

    int opcao = 0;

    do
    {   

        printf("\e[1;1H\e[2J");

        printf("\nBem Vindo ao Menu Principal...\n");
        printf("\n\n--- MENU ---\n\n");
        printf("\n1 - Administrador");
        printf("\n2 - Utilizador");
        printf("\n0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            
            //admin

            break;

        case 2:

            

            break;

        case 0:

        printf("\e[1;1H\e[2J");

        printf("\nBem Vindo ao Menu Principal...\n");
        printf("\n\n--- MENU ---\n\n");
        printf("\n1 - Administrador");
        printf("\n2 - Utilizador");
        printf("\n0 - Sair\n");
        
            printf("\n\nA sair...\n\n\n\n");

            return 0;

            break;
        
        default:
            break;
        }

    } while (opcao != 0);

}

int main (){

    menu();

    return 0;
}