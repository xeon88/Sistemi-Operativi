#include "./header_proj.h"
#include <regex.h>

typedef struct config{
	int radio;
	int optha;
	int orto;
	int cst_prior;
	int prior;
}conf;

// questa è la struttura dati per l'inserimento dei valori con cui si costruiscono le fatture

void compile_re(regex_t* re,char *s);  // metodo per la compilazione delle regex 

void inizialize_structure(struct config *conf); // inizializza la struttura dati con la configurazione dei valori che si utilizzano per 
											    // costruire la fattura

int parse_value(char *stream);  // prende in input una stringa e restituisce il valore dell'intero contenuto all'interno di esso
								// ogni riga ha al massimo un intero da parsificare 
