#include <stdlib.h>             /* EXIT_FAILURE */
#include <stdio.h>              /* perror */
#include <sys/stat.h>           /* struct stat, futimens */
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#ifndef CHEMIN_MAX //chemin ex (../../moi/tp3)
#define CHEMIN_MAX 4096 // par exemple
#endif


/** Version minimale de la fonction sauve qui peut.

    Appeler cette fonction n'a de sens qu'après un appel système qui a
    échoué (puisqu'elle appelle perror()).

    \param[in] msg Une chaîne de caractère passée à perror()
*/
void raler (const char * msg)
{
    perror (msg);
    exit (EXIT_FAILURE);
}

/** Teste si deux fichiers ont même date de dernière modification et
    mêmes permissions.

    Les deux fichiers sont décrits par leurs "struct stat". Le rôle
    des deux fichiers est symétrique, mais a priori le premier est un
    fichier du répertoire "source", et le second est un fichier du
    répertoire de référence.

    \param[in] src Description du premier fichier
    \param[in] ref Description du second fichier
    \return un booléen indiquant si les fichiers sont présumés identiques

*/
int regular_unchanged (const struct stat * src, const struct stat * ref)
{
    return (src->st_mode == ref->st_mode &&
            src->st_mtim.tv_sec == ref->st_mtim.tv_sec &&
            src->st_mtim.tv_nsec == ref->st_mtim.tv_nsec);
}

/** Modifie les dates de dernier accès et dernière modification d'un
    fichier ouvert.

    Les dates à affecter au fichier "fd" proviennent d'une "struct
    stat". Le fichier doit être ouvert, et donné par son descripteur.

    L'appel de cette fonction doit être la dernière opération
    effectuée sur le fichier avant close().

    Cette fonction de renvoie rien. En cas d'erreur de changement des
    dates, elle appelle la fonction raler().

    \param[in] st Description d'un fichier dont il faut reproduire les dates.
    \param[in] df Descripteur de fichier correctement ouvert

*/

void regular_set_amtime (const struct stat * st, int fd)
{
    struct timespec ut [2] = { st->st_atim, st->st_mtim };
    if (futimens (fd, ut) == -1)
        raler ("futimens");
}




void open_folder ( char* argv[]){

DIR *dp;

struct dirent *dir_element;
struct stat file_info;

dp = opendir(argv[1]);

if (dp == NULL)
    raler("Open DIR");

while  ((dir_element = readdir(dp)) != NULL) {
   
    
   
    
    lstat(dir_element->d_name, &file_info);          //getting a file stats


        printf("[%s]\n",dir_element->d_name);                       // show current filename
        //printf("file mode: %d\n", file_info.st_mode);
        //printf("file permission %d \n",file_info.st_mode & 0777 );
        //printf("path %ld\n",dir_element->d_off);
        // print what kind of file we are dealing with
        //fprintf(stderr, "Usage: %s \n", argv[1]);
       char buf[CHEMIN_MAX]; 
        realpath(dir_element->d_name, buf);
    printf ("[%s]\n", buf);
        
        printf("File type:                ");
        
        switch (file_info.st_mode & S_IFMT) {
         
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }}


    if(closedir(dp)==-1)
        raler("closedir");


}
int main(int argc, char* argv[]){

if (argc < 2){

    fprintf(stderr,"1. Not enough args.");
    exit(EXIT_FAILURE);
}
open_folder(argv);

}
