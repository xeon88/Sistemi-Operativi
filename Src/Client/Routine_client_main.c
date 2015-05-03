#include "Routine_client.h"
#include "header_proj.h"



int main(int argc ,char ** argv){

		int num_client , legal_visite , legal_prior;
		int * client_chld; 		
			
	if(argc==1){
		//esegui un figlio con parametri 1 RADIOLOGY ILLWAIT	

		num_client=1;
        	client = calloc(1,sizeof(int));
		int pid_c=fork();
		if(pid_c==0){
			execlp("./Client_chld","./Clent_chld","RADIOLOGY","NOHURRY",(char*)0);

			//execlp fallisce
			
			printf("Impossibile inviare la richiesta \n");
			perror(1);
			exit(1);			 	
			}		

		}

	else if(argc==4){

		// controllo prima se il primo input è un intero
		
		num_client=parse_value(argv[1]);
		if(num_client==-1){
			  printf("Numero richieste non valido : %s \n  l'operazione sarà terminata \n",argv[1]);
			  exit(1);
			}
		// controlla se il secondo input sia un nome di visita valida		

		legal_visite=check_visite(argv[2]);
		if(legal_visite==-1){
			  printf("Tipo visita non valido : %s \n l'operazione sarà terminata \n",argv[2]);
			  exit(1);			
			}						

		// controlla se il secondo input sia un nome di priorità valida
		
		legal_prior=check_prior(argv[3]);
		if(legal_visite==-1){
			  printf("Tipo visita non valido : %s \n l'operazione sarà terminata \n",argv[3]);
			  exit(1);			
			}					

		client_chld=calloc(num_client,sizeof(int));
		
		int i=0;
		
		for(i;i<num_client;i++){
			client_chld[i]=fork();
			
			if(client_chld[i]==0){
				
				execlp("./Client_chld","./Clent_chld",argv[1].argv[2],argv[3],(char*)0);
				
				printf("Impossibile inviare la richiesta \n");
				perror(1);
				exit(1);
				}			
			
			}		
		
		while(i>0){		
		 	int n=wait(0);
			i--;		
		}

	 
		printf("Terminazione del programma \n");
	
	else{

		printf("Il numero di parametri non è corretto %d : operazione non valida",argc-1);
		exit(1);

	}

	return EXIT_SUCCESS;
}




