#include "Routine_client.h"

int parse_value(char * stream)
{

	regex_t num ;
	int err_ex , int_len , value ;
	
	compile_re(&num,"^[0-9]*$");
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
               	value=-1;
        }
    else{
                regerror(err_ex,&num,stream, sizeof(stream));
                fprintf(stderr, "Regex match failed: %s\n", stream);
                exit(1);
        }


	return value;
}




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



int check_visite(char * par){

	regex_t visite;
	int err_comp;	
	regmatch_t pmatch[1];	

	compile_re(&visite,"^(ORTHOPEDICS|RADIOLOGY|OPHTHALMOLOGY)$");
		
	return !regexec(&visite,par,1,pmatch,0) ? 1 : 0 ;

}


int check_prior(char * par){

	regex_t priority;
	int err_comp;	
	regmatch_t pmatch[1];	

	compile_re(&priority,"^(ILLWAIT|NOHURRY|IMONHOLODAY||NEEDTOGO|CANTWAIT)$");
		
	return !regexec(&priority,par,1,pmatch,0) ? 1 : -1 ;

}


int make_msg_queue(int key)
{
	int msgid=msgget(key,IPC_CREAT | PERMESSI);
	if(msgid==-1)
		{
		perror(0);
		exit(0);
		}
	return msgid;

}


int create_socket(int pid_client )
{

	int fd , len ;
	int dsockaddr_un un ;
	fd = socket(AF_UNIX,SOCK_STREAM,0);
	un.sun_family=AF_UNIX;
	strcpy(un.sun_path,"%d.sock",pid_client);
	len=offsetof(struct sockaddr_un , sun_path) + strlen("%d.sock",pid_client);
	bind(fd,(struct sockaddr *)&un,len);
	
	return fd;
}


int connection (int fd)
{

	int fdsrvcli , lencli;
	struct sockaddr_un uncli;
	listen(fd,10);
	lencli=sizeof(struct sockaddr_un);
	fdsrvcli=accept(fd,(struct sockaddr *)&uncli,&lencli);

	return fdsrvcli;

}


void print_reponse(struct invoice * reponse)
{

	printf ("=======s STAMPA RISPOSTA ======== \n");
	printf("Codice cliente : %d  \n",clientId);
	printf("Numero di prenotazione : %d \n",turn);
	printf("Costo della visita : %d \n",price);
	printf ("=======s STAMPA RISPOSTA ======== \n");	


}




