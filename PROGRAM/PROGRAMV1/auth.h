#define MAX_USERS 100
#define MAX_LEN 100
#define MAX_STACK_SIZE 100

typedef struct login_user {

    char input_username [MAX_LEN];
    char input_password [MAX_LEN];

    char login_username [MAX_LEN];
    char login_password [MAX_LEN];

} LOGIN_USER;

typedef struct signup_user {

    char nome [MAX_LEN];
    char cc [50];
    char nif [50];
    char data_nasc [50];
    char curso [100];
    char escola [100];
    float media;

    char sign_username [MAX_LEN];
    char sign_password [MAX_LEN];

} SIGNUP_USER;