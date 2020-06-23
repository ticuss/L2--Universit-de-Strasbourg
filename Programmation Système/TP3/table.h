
#include <sys/types.h>
#include <stdio.h>

/** Gestion d'une table de jobs.

    Le code qui vous est fourni permet de gérer une table dejobs. Une
    telle table est chargée à partir d'un fichier, et doit être
    libérée en fin de traitement.

        struct table * table = table_parse (fd);
        ...
        table_free (table);

    Votre programme est responsable de l'ouverture du fichier avec
    fopen(), et de sa fermeture avec fclose() (dès après table_parse()).

    Une table est simplement un tableau, que l'on peut parcourir avec :

        for (int i=0 ; i<table->njob ; i++)
            ... table->jobs [i] ...

    Chaque entrée de la table (de type struct job) contient la
    description statique du job (délai, nom et commande). Elle
    contient aussi un champ "pid" qui peut être modifié dynamiquement
    par le programme, de la façon suivante :

    - Lorsque le job est lancé, l'identificateur de processus doit
      être placé dans le champ "pid" du job.

    - Lorsqu'un processus se termine, il faut rechercher dans la table
      à quel job son identificateur correspond : c'est ce que fait la
      fonction table_find_pid(), qui renvoie l'indice du job.

    - Lorsque le processus se termine, le champ "pid" du job doit être
      réinitialisé à -1.

    Note : Cette description fait apparaître un problème potentiel :
    lorsqu'on veut lancer un job, il se peut qu'il ait déjà été lancé
    une fois et qu'il n'ait pas encore terminé. Dans ce cas, le plus
    simple est de ne pas lancer la nouvelle instance du job, et
    d'afficher un message d'avertissement.
*/



/** Description d'un job. */
struct job {
    /* Partie statique */
    int     delay;              /**< délai avant exécution */
    char    id [16];            /**< identificateur, pour affichage */
    char ** cmd;                /**< commande, prête pour exec??() */
    /* Partie dynamique */
    pid_t   pid; /**< identificateur du processus pendant exécution */
};

/** Une table est un simple tableau de jobs. */
struct table {
    int          njob;          /**< Nombre de jobs. */
    struct job * jobs;          /**< Tableau des jobs. */
};


/** Charger une table à partir d'un fichier ouvert.

    Si cette fonction retourne, elle a pu lire un ensemble de jobs et
    construire une table.

    \param fd Le fichier ouvert en lecture.
    \returns Une table.
*/
struct table * table_parse (FILE * fd);

/** Libère toute la mémoire allouée pour une table.

    \param table La table dont il faut libérer la mémoire.
*/
void table_free (struct table * table);

/** Affiche la table des jobs.

    Pour chaque job de la table, affiche au minimum le nom du job
    ainsi que la valeur courant du processus en train de l'exécuter
    (ou -1 si ce n'est pas cas). Si l'argument verbose est différent
    de 0, affiche également la commande associée (où chaque mot est
    entouré d'accolades).

    Si l'argument verbose est faux (égal à 0), la table ne contient
    que les jobs en cours d'exécution (c'est-à-dire éventuellement
    aucun).

    \param table La table des jobs
    \param verbose Requiert les détails si différent de zéro

*/
void table_print (struct table * table, int verbose);

/** Retrouve un identificateur dans la table, et renvoie l'indice.

    \param table La table dans laquelle il faut chercher.
    \param pid L'identificateur de processus à recherche.
    \returns L'indice du job, ou -1 si l'identificateur n'est pas présent.
*/
int table_find_pid (struct table * table, pid_t pid);
