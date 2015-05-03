#include "header_proj.h"
#include <regex.h>
#include <time.h>

#define ABS_PATH_LENGTH 108
#define MAX_PRIOR 4


typedef struct ipcs_id{
	
	int nseq_shmid;
	int nseq_semid;
	int msg_main_bus;
	int msg_q[NUMSERVICE];
}ipcs;



typedef struct config{
	int radio;
	int ophtha;
	int orto;
	int cst_prior;
	int prior;
}conf;

// questa è la struttura dati per l'inserimento dei valori con cui si costruiscono le fatture
 


int make_msg_queue(int key);

struct conf * make_shm_conf(int key )
int * make_shm_nseq(int key );

int seminit(int semid,int semnum,int startval);
int make_semaphore();
void down(int semid,int semnum);
void up(int semid,int semnum);
void ipc_remove(struct *ipcs_id ipcs);
int convert_char(char input[] ,int n);
char * cpy_substr(char str[] ,int start,int end );




void compile_re(regex_t* re,char *s);  // metodo per la compilazione delle regex 

void inizialize_structure(struct config *conf); // inizializza la struttura dati con la configurazione dei valori che si utilizzano per 
											    // costruire la fattura

int parse_value(char *stream);  // prende in input una stringa e restituisce il valore dell'intero contenuto all'interno di esso
								// ogni riga ha al massimo un intero da parsificare





int connect_socket(int pid_client);
int try_to_connect(int fdsrv);
void compile_invoice(struct invoice * in , struct config * conf , int n_seq);
