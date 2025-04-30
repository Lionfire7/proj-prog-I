#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"

int login () {

    LOGIN_USER log_users [MAX_USERS];
    int count = 0;
    int found = 0;  
    int trycounter = 0;

    FILE *f = fopen ("users.txt", "r"); 
    if (f == NULL)
    {
        printf("\nError loading user database...\n");
        return -1;
    }

    do
    {
    
        printf("\n\nEnter your username (0 to close program) and password below: \n");
    
        printf("\nUsername: ");
        scanf("%s", &log_users->input_username);

        printf("\e[1;1H\e[2J");
    
        //close program
    
        if (strcmp (log_users->input_username, "0") == 0)
        {
            printf("\n\nClosing program now...");
            return 0;
        }
    
        //check if username is registered
    
        while (fscanf(f, "%s %s", log_users->login_username, log_users->login_password) != EOF)
        {
            if (strcmp (log_users->input_username, log_users->login_username) == 0)
            {   
                //the username was found, ask for password
                do
                {
                    printf("\n\nEnter password: ");
                    scanf("%s", &log_users->input_password);

                    printf("\e[1;1H\e[2J");
    
                if (strcmp (log_users->login_password, log_users->input_password) == 0)
                {
                    printf("\nWelcome, loggin in now...");
                    found = 1; // sucess
                    
                    //go to user page
                    fclose (f);

                    return 0;

                    break;

                } else {
    
                    printf("\n\nWrong password...");
                    found = 0;
                    trycounter ++;
    
                }
    
                } while (trycounter < 3);
    
                if (trycounter == 3)
                {
                    printf("\n\nYou are out of attemps...");
                }
                
               
            } else {
    
                printf("\nUsername not found...");
            }
    
        }

    } while (strcmp (log_users->input_username, "0") != 0);
    
    fclose (f);

    return 0;

}

int main () {

    login ();
    
    return 0;
}