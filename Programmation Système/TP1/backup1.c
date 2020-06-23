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
int show_files_propreties( char *argv[]);
void regular_set_amtime (const struct stat * st, int fd)
{
    struct timespec ut [2] = { st->st_atim, st->st_mtim };
    if (futimens (fd, ut) == -1)
        raler ("futimens");
}

void listdir( char *argv[], size_t size) {
   
    DIR *dir;
    struct dirent *entry;
    size_t len = strlen(argv[1]);

    if (!(dir = opendir(argv[1]))) {
        fprintf(stderr, "path not found: %s: %s\n",
                argv[1], strerror(errno));
        return;
    }

    puts(argv[1]);
    while ((entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
       
        if (entry->d_type == DT_DIR) {
            if (!strcmp(name, ".") || !strcmp(name, ".."))
                continue;
            if (len + strlen(name) + 2 > size) {
                fprintf(stderr, "path too long: %s/%s\n", argv[1], name);
            } else {    
                argv[1][len] = '/';
                strcpy(argv[1] + len + 1, name);
                listdir(&argv[1], size);
                argv[1][len] = '\0';
            }
        } else {
            printf("%s/%s\n", argv[1], name);
            
        }
    }
    
}



int show_files_propreties(char *argv[]){
    struct stat sb;

   

   if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

   printf("File type:                ");

printf("Permissions: ");

    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");   




   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    
    


    }
    

  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char path[1] = ".";
    listdir(argv, sizeof argv[1]);
   show_files_propreties(argv);
    return 0;
}