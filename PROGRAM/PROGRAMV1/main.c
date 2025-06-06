#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "espacoAdmin.h"
#include "user_func.h"

int main (){

    llist *head = NULL;

    userlog (&head);

    FILE *f = fopen("users.bin", "w+b");
    if (f == NULL) {
        printf("\nErro ao abrir o ficheiro users.bin.\n");
        return -1;
    }

    while (head != NULL) {
        fwrite(&head->userinfo, sizeof(USERINFO), 1, f);
        head = head->next;
    }

    fclose(f);
    return 0;
}