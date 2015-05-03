#include <sys/un.h>
#include <sys/socket.h>
#include "header_proj.h"

#define ABS_PATH_LENGTH 108
#define MAX_PRIOR 4


int connect_socket(int pid_client);
int try_to_connect(int fdsrv);
void compile_invoice(struct invoice * in , struct config * conf , int n_seq);


