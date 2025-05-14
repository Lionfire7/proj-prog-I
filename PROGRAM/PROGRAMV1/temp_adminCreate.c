#include <stdio.h>
#include <stdlib.h>
#include "auth.h"

//usei só pra criar o username e password no ficheiro bin do admin

int signup() {
    ADMININFO admin;

    printf("\n\n--- Registo de Novo Utilizador ---\n");

    printf("Crie um username: ");
    scanf("%s", admin.username);

    printf("Crie uma password: ");
    scanf("%s", admin.password);

    FILE *f = fopen("admin.bin", "ab");
    if (f == NULL) {
        printf("\nErro ao guardar utilizador.\n");
        return -1;
    }

    fwrite(&admin, sizeof(admin), 1, f);
    fclose(f);

    printf("\nUtilizador registado com sucesso.\n");
    return 0;
}

int AdminSignup () {

    signup ();
    
}