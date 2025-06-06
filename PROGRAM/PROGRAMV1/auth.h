#define MAX_USERS 100
#define MAX_LEN 100
#define MAX_STACK_SIZE 100
#define MAX_CURSOS 40

typedef struct userinfo {

    int id;

    char username [MAX_LEN];
    char password [MAX_LEN];

    char nome [MAX_LEN];
    char cc [50];
    char nif [50];
    char data_nasc [50];
    char curso [100];
    char escola [100];
    float media;
    char cursocandidato [100];

} USERINFO;

typedef struct llist {
    USERINFO userinfo;
    struct llist* next;
} llist;

typedef struct cursos  {

    char curso [100];
    char escola [10];
    char tag [10];
    int nvagas;
    int status;
    int candidatos;

} CURSOS;

typedef struct coloc{
    int id;
    char username [MAX_LEN];
    char nome [MAX_LEN];
    char curso [MAX_CURSOS];
    char status [10];
}COLOC;
