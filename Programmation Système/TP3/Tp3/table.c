
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "table.h"

void syserr (const char * msg)
{
    perror (msg);
    exit (EXIT_FAILURE);
}
void usrerr (const char * fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
    vfprintf (stderr, fmt, ap);
    exit (EXIT_FAILURE);
    va_end (ap);
}
void usrwarn (const char * fmt, ...)
{
    va_list ap;
    va_start (ap, fmt);
    vfprintf (stderr, fmt, ap);
    va_end (ap);
}

/* ---------------------------------------------------------------- */

#define CHUNK_SIZE 8

char ** argvify (char * text, int depth)
{
    char * tok = strtok (text, " \t\n");
    if (tok == NULL)
    {
        char ** a = calloc (depth+1, sizeof (char *));
        if (a == NULL)
            syserr ("argvify/calloc");
        a[depth] = NULL;
        return a;
    }
    else
    {
        char * s = strdup (tok);
        if (s == NULL)
            syserr ("argvify/strdup");
        char ** a = argvify (NULL, depth+1);
        a[depth] = s;
        return a;
    }
}

struct table * table_parse (FILE * fd)
{
    struct table * table = malloc (sizeof(struct table));
    if (table == NULL)
        syserr ("malloc");
    table->njob = 0;
    table->jobs = NULL;
    char line [256];
    int lineno = 0;
    while (fgets (line, 256, fd) != NULL)
    {
        ++ lineno;
        size_t last = strlen(line)-1;
        if (line [last] != '\n')
            usrerr ("%d: ligne sans \\n ou trop longue\n", lineno);
        line [last] = '\0';
        if (table->njob % CHUNK_SIZE == 0)
        {
            size_t ns = table->njob + CHUNK_SIZE;
            table->jobs = realloc (table->jobs, ns*sizeof(struct job));
            if (table->jobs == NULL)
                syserr ("realloc");
        }
        char colon[2];
        int len;
        struct job job = { .delay=0, .cmd=NULL, .pid=-1 };
        if (sscanf (line, " %d%1[:]%15[a-z0-9]%1[:]%n",
                    &job.delay, colon, job.id, colon, &len) != 4)
            usrerr ("%d: ligne '%s' incorrecte\n", lineno, line);
        if (job.delay <= 0)
            usrerr ("%d: délai %d invalide\n", lineno, job.delay);
        job.cmd = argvify (line+len, 0);
        table->jobs[table->njob ++] = job;
    }
    return table;
}

void table_free (struct table * table)
{
    for (int i=0 ; i<table->njob ; i++)
    {
        for (int j=0 ; table->jobs [i].cmd [j]!=NULL ; j++)
            free (table->jobs [i].cmd [j]);
        free (table->jobs [i].cmd);
    }
    free (table->jobs);
    free (table);
}

void table_print (struct table * table, int verbose)
{
    fprintf (stderr, "+--- Jobs\n");
    for (int i=0 ; i<table->njob ; i++)
    {
        pid_t pid = table->jobs [i].pid;
        if (pid != -1 || verbose)
        {
            fprintf (stderr, "| %3d | %-16s: %5d",
                     table->jobs [i].delay, table->jobs [i].id, pid);
            if (verbose)
            {
                char ** cmd = table->jobs[i].cmd;
                fprintf (stderr, " |");
                for (int j=0 ; cmd [j]!=NULL ; j++)
                    fprintf (stderr, " {%s}", cmd [j]);
            }
            fprintf (stderr, "\n");
        }
    }
    fprintf (stderr, "+--------\n");
}

int table_find_pid (struct table * table, pid_t pid)
{
    for (int i=0 ; i<table->njob ; i++)
        if (table->jobs[i].pid == pid)
            return i;
    return -1;
}
