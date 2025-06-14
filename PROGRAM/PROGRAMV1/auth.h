#define MAX_USERS 100
#define MAX_LEN 100
#define MAX_STACK_SIZE 100
#define MAX_CURSOS 20

#define NIF_LENGHT 9

typedef struct login_user {

    char input_username [MAX_LEN];
    char input_password [MAX_LEN];

    char login_username [MAX_LEN];
    char login_password [MAX_LEN];

} LOGIN_USER;

typedef struct userinfo {

    int id;

    char sign_username [MAX_LEN];
    char sign_password [MAX_LEN];

    char nome [MAX_LEN];
    char cc [50];
    char nif [50];
    char data_nasc [50];
    char curso [100];
    char escola [100];
    float media;
    char cursocandidato [50];

} USERINFO;

typedef struct admininfo {

    char username [100];
    char password [100];

} ADMININFO;

typedef struct cursos  {

    char curso [100];
    char tag [10];
    int status;
    int ncandidatos;
    int nvagas;

} CURSOS;

char *chooseCurso (void);