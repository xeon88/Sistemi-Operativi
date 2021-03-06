#include "Routine_server.h"



int make_msg_queue(int key)
{
	int msgid=msgget(key,IPC_EXCL | PERMESSI);
	if(msgid==-1)
		{
		perror(0);
		exit(0);
		}
	return msgid;
}


int * make_shm_nseq(int key )
{
	int seq_shm=shmget(key,sizeof(int)*NUM_SERVICE,IPC_CREAT|PERMESSI);
	if(seq_shm==-1)
		{
			perror(0);
			exit(0);		
		}
	int *pnt=(int *)shmat(seq_shm,0,0);
	return pnt;

}


struct conf * make_shm_conf(int key )
{
	int conf_shm=shmget(key,sizeof(struct conf),IPC_CREAT|PERMESSI);
	if(seq_shm==-1)
		{
			perror(0);
			exit(0);		
		}
	struct conf *pnt=(struct conf *)shmat(conf_shm,0,0);
	return pnt;

}


int seminit(int semid,int semnum,int startval)
{
	union semun arg;
	arg.val=startval;
	int r=semctl(semid,semnum,SETVAL,arg);
	return r;
}




int make_semaphore(int num,int val)
{
	int i=0;	
	int semid=semget(SEM_KEY,num,IPC_CREAT | PERMESSI);
	if(semid==-1)
		{
			perror(0);
			exit(0);	
		}	

	for(i;i<num;i++)
	{
		int res=seminit(semid,i,val);
		if(res==-1)
			{
				perror(0);
			}
	}			

	return semid;
}


void down(int semid,int semnum)
{

	struct sembuf sops[NUM_SERVICE];
	sops[semnum].sem_num=semnum;
	sops[semnum].sem_op=-1;
	sops[semnum].sem_flg=0;
	semop(semid,&sops[semnum],NUM_SERVICE);

}


void up(int semid,int semnum)
{
	struct sembuf sops[NUM_SERVICE];
	sops[semnum].sem_num=semnum;
	sops[semnum].sem_op=1;
	sops[semnum].sem_flg=0;
	semop(semid,&sops[semnum],NUM_SERVICE);

}

int convert_char(char input[] ,int n)
{
	int i; 
	int value =0;
	for(i=n-1;i>=0 ;i--)
	{
		value+=input[i]*10^i;
	}

	return value ;
}


char * cpy_substr(char str[] ,int start,int end )
{

	int length=end-start+2;
	char *substr=malloc(length*sizeof(char));
	int i=0;
	
	for(i=0;i<length-1;i++)
		{
			substr[i]=str[start+i];
		}
	
	substr[length-1]='/0';

	return substr;
}



void ipc_remove(struct *ipcs_id ipcs) // da RIFARE;
{
	
	int i=0;

	printf("Rimozione strutture IPC in corso ... \n");
	
	msgctl(ipcs->msg_main_bus,IPC_RMID,0);

	printf("main_bus rimossa correttamente \n");

	while(i<NUM_SERVICE)
		{
			msgctl(ipcs->msg_q[i],IPC_RMID,0);

		}			
	
	printf("msg_q reparti rimosse correttamente \n");

	shmctl(ipcs->shmid,IPC_RMID,0);
	
	printf("shared memory rimossa correttamente \n");

	semctl(ipcs->semid,IPC_RMID,0);

	printf("Semaphores rimossi correttamente \n");

	printf("Rimozione strutture IPC completata .. \n");
	
	printf("Terminazione processo server");
	
	exit(0);	

}


/*
	-------------------------------------------------   FILE PARSING --------------------------------------------------------

*/



void compile_re(regex_t *re,char *s)
{
 	int err_comp;
	err_comp=regcomp(re,s,REG_EXTENDED);
	if(err_comp){
			fprintf(stderr, "Could not compile regex\n"); 
			exit(1); 
	}
	
	printf("Compilazione avvenuta..\n");

}





int parse_value(char * stream)
{

	regex_t num ;
	int err_ex , int_len , value ;
	
	compile_re(&num,"[0-9]*;");
	regmatch_t pmatch[1];
	
	err_ex=regexec(&num,stream,1,pmatch,0);
	
	if(!err_ex){
		int_len=(int)pmatch[0].rm_eo-(int)pmatch[0].rm_so;
		char * str_value = malloc(sizeof(char)*int_len);
		int i,j =0;	
		for(i=(int)pmatch[0].rm_so;i<(int)pmatch[0].rm_eo;i++) {
			str_value[j]=stream[i];
			j++; 
			}	 			
		value=atoi(str_value);			
		}
	else if(err_ex == REG_NOMATCH ){
                puts("No match");
        }
    else{
                regerror(err_ex,&num,stream, sizeof(stream));
                fprintf(stderr, "Regex match failed: %s\n", stream);
                exit(1);
        }


	return value;
}



/*
	La funzione inizialize_structure prende in input una struttura per la configurazione già inizializzata e attraverso l'utilizzo 
	dell' espressioni regolari parsifica il file config.conf - Ogni riga viene parsificata e se una delle strutture dati riconosce una
	stringa e recupera il valore contenuta in essa

*/


void inizialize_structure(struct config * conf)
{

	FILE *to_parse=NULL;
	int err_ex ;
	regex_t orto , ophtha , radio , cst , prior ;
	char * stream ;


	printf ("Apertura file.. \n");
	
	to_parse = fopen("./config.conf","r");
	if(to_parse==NULL){ 
		exit(1);
	}

	printf("Apertura file riuscita \n \n");
	
	
	//	Compilazione delle strutture dati per il parsing del file di configurazione
		
	compile_re(&orto,"^VISITA_ORTOPEDICA [0-9]*;");
	compile_re(&radio,"^VISITA_RADIOLOGICA [0-9]*;");
	compile_re(&ophtha,"^VISITA_OCULISTICA [0-9]*;");
	compile_re(&cst,"^COSTO_PRIORITA [0-9]*;");
	compile_re(&prior,"^PRIORITY [0-9]*;");

	stream = calloc(100,sizeof(char));
	
	
	while(fgets(stream,100,to_parse)!=NULL)
	{
		if(stream[0]!='#'){
			regmatch_t result[1];
			if(!regexec(&orto,stream,1,result,0)){
				conf->orto=parse_value(stream);
				
				
				continue;
				}
			if(!regexec(&radio,stream,1,result,0)){
				conf->radio=parse_value(stream);
				
				continue;
				}
			if(!regexec(&ophtha,stream,1,result,0)){
				conf->ophtha=parse_value(stream);
				
				continue;
				}	
			if(!regexec(&cst,stream,1,result,0)){
				conf->cst_prior=parse_value(stream);
				
				continue;
				}
			if(!regexec(&prior,stream,1,result,0)){
				conf->prior=parse_value(stream);
				continue;
				}
		}		
	
	}
		
}






/*
	Crea un descrittore per il socket 
*/

int create_socket(int pid_client )
{

	int fdsrv;
	fdsrv=socket(AF_UNIX,SOCK_STREAM,0);

	return fdsrv;
}


/*
Questa funzione serve per tentare una connessione al socket creato dal client 
Se ci riesce restituisce l'id corrispondente al socket , altrimenti restituirà un valore 
che notifica l'impossibilità di connettersi al socket (per esempio se il client non l'ha ancora creato)
*/



int configure_connect(int fdsrv){ 

	int lensrv;
	char abs_sock_path[ABS_PATH_LENGTH];  // 108 max_strlenght per la stringa un.sun_path
	struct  sockaddr_un unsrv;


	unsrv.sun_family=AF_UNIX;
	strcat(abs_sock_path,SOCKS_PATH);
	strcat(abs_sock_path,"%d.sock",pid_client);
	strcpy(un.sun_path,abs_sock_path);
	lensrv=offsetof(struct sockaddr_un ,sunpath) + strlen(abs_sock_path);
	connect(fdsrv,(struct sockaddr *)&unsrv , lensrv);

	return fdsrv;

}

/* 

 la funzione serve per compilare i campi rimanenti all'interno della fattura che deve essere spedita al client
 Queste sono le due equazioni che calcolano una il numero di turo l'altra il costo della visita
 turn = n_Seq - prior + MAX_PRIOR dove MAX_PRIOR=4 
 price = visit + (prior * cst_prior);
*/	

void compile_invoice(struct invoice * in , struct config * conf , int n_seq)
{

	int visit_price ,n_turn;x

	n_turn = n_seq - (in->priority)	+ MAX_PRIOR ;
	
	if(kindof_service==OPHTHALMOLOGY){
	
		visite_price = conf->ophtha + (in->priority*cst_prior);
	}
	else if (kindof_service==ORTHOPEDICS){
	
		visite_price = conf->orto + (in->priority*cst_prior);
	}
	else{

		visite_price = conf->ophtha + (in->priority*cst_prior);	
	}

	in->turn=n_turn;
	in->price=visite_price;

}




