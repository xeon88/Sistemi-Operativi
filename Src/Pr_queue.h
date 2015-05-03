#define Q_LENGTH 10

Pt_invoice* make_queue();
void add(Pt_invoice queue[],Pt_invoice request,int *free_pos); // aggiunge una richiesta all'interno della coda con priorità 
// free_pos indica la prima posizione libera all'interno della coda
Pt_invoice extract_min(Pt_invoice queue[],int *free_pos); //estrae il primo elemento dalla coda con priorità

// funzioni per la gestione della coda con priorità
void move_up(Pt_invoice queue[],int i);
void move_down(Pt_invoice queue[],int i);



