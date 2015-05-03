#include "Pr_queue.h"

/*Funzioni per la gestione della coda con priorità utilizzate dal figlio del server per calcolare correttamente il numero di turno 
  dei client
*/


Pt_invoice* make_queue()
{	
	Pt_invoice* p_queue = calloc(Q_LENGTH,sizeof(struct invoice));
	return p_queue;
}


void add(Pt_invoice p_queue[],Pt_invoice request,int *free_pos)
{
   p_queue[free_pos]=request;
   *free_pos++;
   move_up(*free_pos);
}

Pt_invoice extract_min(Pt_invoice queue[],int *free_pos)
{

	Pt_invoice tmp=p_queue[0];
	p_queue[0]=p_queue[free_pos-1];
	*free_pos--;
	move_down[*free_pos-1];
	
	return tmp;
}


void move_up(Pt_invoice queue[],int lastpos)
{
	int i=last_pos;
	Pt_invoice tmp=queue[i];
	while(i>0 && (queue[i]->priority>queue[(i-1)/2]->priority || queue[i]->turn>queue[(i-1)/2]->turn))
	{
	   queue[i]=queue[(i-1/2)];
	   i=(i-1)/2;
	}
	queue[i]=tmp;
}



void move_down(Pt_invoice queue[],int lastpos)
{
	int i=0;
	Pt_invoice tmp=queue[i];
	int i_child;
	while((i_child=2*i+1)<lastpos)
	{
		int r_child=i_child+1;
		if(r_child<lastpos && queue[r_child]>queue[i_child])i_child++
		if(tmp>=queue[i_child])break;
		queue[i]=queue[i_child];
		i=i_child;
	}
	queue[i]=tmp;
}



