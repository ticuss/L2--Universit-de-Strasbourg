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
void show_files_propreties(char *path);
void copy_files(char *path , char *ref);
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

void listdir(char *path, size_t size , char * ref, char *dest)  {
    DIR *dir;
    struct dirent *entry;
    size_t len = strlen(path);
    struct stat sbuf;
   
    if (!(dir = opendir(path))) {
        fprintf(stderr, "path not found: %s: %s\n",
                path, strerror(errno));
        return;
    }

    puts(path);
    while ((entry = readdir(dir)) != NULL) {
        
        char *name = entry->d_name;
       show_files_propreties(name);
       copy_files(name,ref);
        if (entry->d_type == DT_DIR) {
            if (!strcmp(name, ".") || !strcmp(name, ".."))
            
                continue;
            if (len + strlen(name) > size) {
                fprintf(stderr, "path too long: %s/%s\n", path, name);
               
            } else {
                path[len] = '/';
                strcpy(path + len + 1, name);
              
                listdir(path, size , ref,dest);
                
                
            }

        } else {
            printf("%s/%s\n", path, name);
            
        }
        char * chemin= strcat(strcat(path, "/"), entry->d_name);
        if (stat(chemin, &sbuf) == -1)
                                raler("stat");
        switch (sbuf.st_mode & S_IFMT){
                                case S_IFREG: {
                                        printf("regular file \n");
                                        break;
                                }
                                case S_IFDIR: {
                                    char *ref_temp= strcat(strcat(ref, "/"), entry->d_name);
                                    char *dest_temp= strcat(strcat(dest, "/"), entry->d_name);
                                    if(mkdir(dest_temp, sbuf.st_mode & 0666) == -1)
                                                raler("mkdir");
                                        if(closedir(path) == -1)
                                                raler("closedir");
                                        listdir(chemin, dest_temp, ref_temp);
                                        break ;
                                }
                                case S_IFLNK: {
                                        printf( "lien symbolique \n");
                                        break;
    }
    }
   
    closedir(dir);
}
void show_files_propreties(char *path){
    struct stat sb;

   

  /* if (lstat(path, &sb) == -1) {
        perror("stat::::");
        exit(EXIT_FAILURE);
    }*/
lstat(path, &sb);
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

  
   printf("File type: ");

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
  
}

/*void copy_files(char *path , char *ref){
int fdIn;
int fdOut;
int nbCount;
char buffer;
struct stat sb;
DIR *dir;
struct dirent *entry;

      
      if (fdIn==-1)
{	
	raler("Open 1");
} 

    lstat(path, &sb);

if (S_ISDIR(sb.st_mode))
mkdir(ref,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

fdOut = open(entry->d_name, O_RDWR | O_CREAT | O_APPEND, 0666);

if (fdOut==-1)
{
	
	raler("Open 2");

}


if( sb.st_mode & __S_IFREG || sb.st_mode & __S_IFLNK){

nbCount = read (fdIn ,&buffer, sizeof(buffer));

while (nbCount != 0) 
{
       write(fdOut, &buffer, nbCount);
       nbCount = read(fdIn, &buffer, sizeof(buffer));
}}
 close(fdIn);  
	 close(fdOut);
	 
	 
}


*/




int main(int arcg, char *argv[]){
    
    
    
     if (argc < 2)
    {
      fprintf (stderr, "usage: %s fichier \n", argv[0]);
      exit (1);
    }
    char source [CHEMIN_MAX],ref[CHEMIN_MAX],dest[CHEMIN_MAX];
    listdir(source, sizeof source , ref , dest);
    
    return 0;
}

