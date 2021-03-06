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


void inizialize_structure(struct config * conf)
{

	FILE *to_parse=NULL;
	int err_ex ;
	regex_t orto , optha , radio , cst , prior ;
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
	compile_re(&optha,"^VISITA_OCULISTICA [0-9]*;");
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
			if(!regexec(&optha,stream,1,result,0)){
				conf->optha=parse_value(stream);
				
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


