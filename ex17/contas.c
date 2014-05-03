#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Contas {

	int id;
	int set;
	char nome[MAX_DATA];
	char desc[MAX_DATA];
	char tipo;  // 0 = credor 1 = devedor
	int valor;
};


struct Database { 
	struct Contas rows[MAX_ROWS];
};


struct Connection { 
	struct Database *db;
	FILE *file;
};


void die(const char *message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}



void Database_create(struct Connection *conn) { 

	int i=0;

	for (i = 0; i < MAX_ROWS; i++) {

		struct Contas conta = {.id = i, .set = 0, .tipo = 0, .valor = 0};
		conn->db->rows[i] = conta;
	}
}


void Database_write(struct Connection *conn) {

	rewind(conn->file);
	int rc = fwrite(conn->db,sizeof(struct Database),1,conn->file);
	if (rc != 1)
		printf("falhou");

	rc = fflush(conn->file);
	if(rc == -1) 
		printf("Cannot flush database.");


}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if(rc != 1) 
    	printf("Failed to load database.\n");
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db) die("Memory error");

    if(mode == 'c') {
        conn->file = fopen(filename, "w");
    } 
    else {
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }
    }

    if(!conn->file) die("Failed to open the file");

    return conn;
}



void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file);
        if(conn->db) free(conn->db);
        free(conn);
    }
}

void Database_set(struct Connection *conn, int id, const char *nome, const char *desc,char tipo,int valor) {
	
	struct Contas *conta = &conn->db->rows[id];

	if (conta->set) die("Ja existe uma conta nessa posição");

	conta->set = 1;

	char *name = strncpy(conta->nome,nome,MAX_DATA);
	if(!name) die("Falha em colocar Nome");

	char *descri = strncpy(conta->desc,desc,MAX_DATA);
	if(!descri) die("Falha em colocar descricao");

	conta->tipo = tipo;
	conta->valor = valor;
}



void Conta_print(struct Contas *conta) { 

	printf("nome:	 %s\n",conta->nome);
	printf("discri:  %s\n",conta->desc);
	printf("valor:	 %d\n",conta->valor);
	printf("tipo:    %c\n",conta->tipo);
	printf("\n");
}


void Database_list(struct Connection *conn) { 


	int i = 0;
	struct Database *db = conn->db;

	for(i = 0; i < MAX_ROWS; i++) {

		struct Contas *curr = &db->rows[i];
		if (curr->set) { 

			Conta_print(curr);
		}

	}

}


int main(int argc,char **argv) { 

	if (argc < 3) die("Uso: contas <dbfile> <acao> [parametros acao]");

	char *filename = argv[1];
    char action = argv[2][0];

	struct Connection *conn = Database_open(filename,action);

	int id = 0;
	if(argc > 3) id = atoi(argv[3]);
    if(id >= MAX_ROWS) die("There's not that many records.");

	switch(action) { 

		case 'c': 
			Database_create(conn);
			Database_write(conn);	
			break;
		
		case 'l': 			
			Database_list(conn);	
			break;

		case 's': 
             //if(argc != 8) die("Need id, name, descricao, tipo, valor");
             Database_set(conn, id, argv[4], argv[5],*argv[6],*argv[7]);
             Database_write(conn);	
             break;

		
		default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
	}

	Database_close(conn);


	return 0;


}