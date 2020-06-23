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

#ifndef CHEMIN_MAX
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



void copy_file(char *source,char *dest )
{

int fdIn;
int fdOut;
char buff[CHEMIN_MAX];
ssize_t reads, writes;
struct stat stbuf;


fdIn = open (source, O_RDONLY);

if (fdIn==-1)	
	raler("Open 1");

lstat (source, &stbuf);
if (lstat (source, &stbuf) ==-1)
	raler("lstat");

fdOut = open (dest, O_WRONLY | O_CREAT, stbuf.st_mode);

if (fdOut ==-1)
	raler("Open 2");

while ((reads = read (fdIn, buff, CHEMIN_MAX)) != 0)
    {
    writes = write (fdOut, buff, reads);
    }
    if (writes==-1 )
		raler("write 1");
    regular_set_amtime(&stbuf, fdOut);
   
    close(fdIn);
    
    close(fdOut);


}

void create_dir(char folder[CHEMIN_MAX]){

char sbuf[CHEMIN_MAX];
	int i = 0;
	int j;
	DIR *dir;

while (folder[i] != '\0' && i++ < CHEMIN_MAX) {
	if (folder[i] == '/') {
		if ((j = snprintf(sbuf, i+1, "%s", folder)) < 0 || j > CHEMIN_MAX)
				raler("Problème avec snprintf ");
		if ((dir = opendir(sbuf)) == NULL){
				errno = 0;
				mkdir(sbuf, 0777);
                if (mkdir(sbuf, 0777) == -1)
        raler("Problème avec mkdir 1");
        }
		else if (dir == NULL)
				raler("Problème avec  opendir 1:");
		else
				closedir(dir);
                if (closedir(dir) == -1){
        raler("Problème avec closedir 1");
		}}}
		mkdir(folder, 0777);   
	}



void make_link (char *ref, char *destf)
{
	char dest[CHEMIN_MAX];
	ssize_t read;
	read = readlink (ref, dest, CHEMIN_MAX);
	if (read==-1 )
		raler("read link error 1:"); 
    dest[read] = '\0';	
	symlink(dest, destf);
    if (symlink(dest, destf)==-1 )
		raler("symlink error 2:");
}

void hard_link (char *ref, char *dest)
{
	link(ref, dest);
    if (link(ref, dest)==-1 )
	raler("Hard link error 1:");
}


void pick_the_file (char *source, char *ref, char *dest){
struct stat bufsource, bufref;
if (access(ref, F_OK) == -1)
		copy_file(source, dest);
else {
		lstat(source, &bufsource);
if (lstat(source, &bufsource)==-1 )
		raler("lstat 1:");		
        lstat(ref, &bufref);
if (lstat(ref, &bufsource)==-1 )
		raler("lstat 2:");
if (regular_unchanged(&bufsource, &bufref))
			hard_link(ref, dest);
else 
	copy_file(source, dest);
	}
}

void pick_name (char name[CHEMIN_MAX], char *filename,
	char *dirname)
{
	int i;
	if ((i = snprintf(name, CHEMIN_MAX, "%s/%s", dirname, filename))< 0||i >= CHEMIN_MAX)
		raler ("probleme avec snprintf 3:");
	
}

void backup(char *source, char *ref, char *dest)
{
	DIR *dir;
	struct dirent *entry;
	char file_ref[CHEMIN_MAX], file_source[CHEMIN_MAX];
	char file_dest[CHEMIN_MAX];
	struct stat sbuf;
	
    
	if ( (dir = opendir(source)) == NULL)
		raler("opendir backup");

	while ( (entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
		if (strncmp(name, ".", CHEMIN_MAX) != 0 &&
		   strncmp(name, "..", CHEMIN_MAX) != 0)
		{	
			lstat(file_source, &sbuf);
			pick_name(file_source,name, source);
            pick_name(file_dest, name, dest);
            pick_name(file_ref, name, ref);
            
			if (lstat(file_source, &sbuf) == -1)
		            raler("opendir backup");
		switch (sbuf.st_mode & __S_IFMT) {
		case __S_IFDIR:
				printf("%s\n", file_dest);
				mkdir(file_dest, 0777);
                if (mkdir(file_dest, 0777)==-1 )
		    raler("mkdir 1 backup");

			backup(file_source, file_ref, file_dest);
		break;
		case __S_IFREG:
			pick_the_file(file_source, file_ref, 
					file_dest);
		break;
		
		case __S_IFLNK:
				make_link(file_source, file_dest);
		break;

		default:
			printf("type not accepted");
            
			}
		}
	}
	closedir(dir);
}


int main (int argc, char **argv)
{
	if (argc != 4)
	raler("Usage: ... ");
	access(argv[1], F_OK );
	if(access(argv[1], F_OK )== -1)
    raler("acces 2");	
	create_dir(argv[3]);
	backup(argv[1], argv[2], argv[3]);

	return 0;
}















