#define _XOPEN_SOURCE 700
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>
#include "table.h"

int lance_prog(struct job *task);
void alarme( struct job *_job);


size_t job=0;
int affiche = 1;

struct itimerval timeval;
struct table *table;

/** Une fonction que vous pouvez utiliser comme printf pour afficher
    une ligne précédée du numéro de processus et des minute/seconde.
*/
#ifdef __GNUC__
__attribute__ ((format (printf, 1, 2)))
#endif

void chronos_log (const char * fmt, ...)
{
    if(affiche == 0 ) return;
    va_list ap;
    va_start (ap, fmt);
    time_t t = time (NULL);
    struct tm * tm = localtime (&t);
    fprintf (stderr, "[%d @ %02d:%02d] ",getpid(), tm->tm_min, tm->tm_sec);
    vfprintf (stderr, fmt, ap);
    fflush (stderr);
    va_end (ap);
}

void sigterme(int sig){
    if ( sig == SIGTERM )
    {
        chronos_log("SHUTDOWN\n");
    for (int i = 0; i < table->njob; i++)
        {
            int status;
        if( table->jobs[i].pid != -1 ) {
            waitpid(table->jobs[i].pid,&status, 0);
        if(WIFEXITED(status)){
        
        if( ! WEXITSTATUS(status) )
                chronos_log("WAIT %s %d ok\n",table->jobs[i].id, table->jobs[i].pid );
        else
                chronos_log("WAIT %s %d ko\n",table->jobs[i].id, table->jobs[i].pid );
                }
            }
        }
        
        if( table ) 
        table_free( table);    

        chronos_log("BYE\n");
        exit(0);
    }
}

void sigusr1(int sig){
    if( sig == SIGUSR1)
    affiche=!affiche;
}


void sigusr2(int sig){
    if( sig == SIGUSR2)
    table_print(table,0);
}

void sigalrme(int sig){
    if( sig == SIGALRM )
    {
        
        int stat = lance_prog( table->jobs + job % table->njob  );
        if( stat == 0 ){ 
            chronos_log("INIT %s %d\n", table->jobs[ job % table->njob ].id, table->jobs[ job % table->njob ].pid );
        }
        
        alarme(table->jobs + job%table->njob);
        ++job;
    }
}

void sigfils(int sig){
    if( sig != SIGCHLD ) return;
    pid_t pid;
    int status;
    pid=waitpid(-1,&status,WNOHANG);
    
    if( WIFEXITED(status) )
        status= WEXITSTATUS(status);
    int find= table_find_pid(table, pid );
    
    if (find >= 0){
        
        if( status == 0 ) chronos_log("FINI %s %d ok\n", table->jobs[find].id, table->jobs[find].pid);
        else chronos_log("FINI %s %d ko\n", table->jobs[find].id, table->jobs[find].pid);
    }
    table->jobs[find].pid=-1;
    
}

void attribuer_signes(){
    struct sigaction sig;
    sig.sa_flags=0;
    sigfillset(&sig.sa_mask);

    sig.sa_handler= sigterme;
    sigaction(SIGTERM, &sig, NULL);

    sigdelset(&sig.sa_mask, SIGTERM);
    sig.sa_handler= sigusr1;
    
    sigaction(SIGUSR1, &sig, NULL);
    sig.sa_handler= sigusr2;
   
    sigaction(SIGUSR2, &sig, NULL);
    sig.sa_handler= sigalrme;
   
    sigaction(SIGALRM, &sig, NULL);
    sig.sa_handler= sigfils;
    
    sigaction(SIGCHLD, &sig, NULL);
    
}

int lance_prog(struct job *task)
{
    if (task->pid != -1){
        chronos_log("OMIS %s\n", task->id);
        return -1;
    }

    pid_t child = fork();
    switch(child){
        case -1:  
            chronos_log("Error Fork\n");
            return -2;
        case 0:    
            execvp(task->cmd[0], task->cmd);
            break;

        default:
            task->pid=child;
            
    }
    return 0;
    
}


void alarme( struct job *_job){
    timeval.it_value.tv_sec=_job->delay;
    setitimer(ITIMER_REAL, &timeval,NULL );
}


int main(int argc, char * argv [])
{
    chronos_log ("HELLO\n");
    if (argc != 2 )
    {
        chronos_log("Exit\n");
        exit(EXIT_FAILURE);
    }
    attribuer_signes();
    FILE* f= fopen(argv[1], "r");
    table= table_parse(f);
    fclose(f);
    
    sigset_t suspend;
    sigfillset(&suspend);
    sigdelset(&suspend, SIGUSR1);
    sigdelset(&suspend, SIGUSR2);
    sigdelset(&suspend, SIGCHLD);
    sigdelset(&suspend, SIGTERM);
    sigdelset(&suspend, SIGALRM);
         alarme(table->jobs);
    while(1){
        sigsuspend(&suspend);
    }
    if(table) 
    table_free(table);

    return EXIT_SUCCESS;
}
