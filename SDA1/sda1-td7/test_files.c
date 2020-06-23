// test_files.c
#include<stdio.h>
#include "files_dbl.h"



void file_print(file f)
{
    if (!f) puts("file vide");
    else
    {   
        file parc = f-> next;
        for(; parc != f; parc = parc->next)
        {
            printf("%7d::", parc->val);
        } 
        printf("%7d::", parc->val);
    }
    putchar('\n');     
}

int main()
{
    file f = file_vide();
    S tab[] = {10,1,2,3,10,11,12,40,41,42,50, 51};
    for(int i=0; i<12; i++) f = file_adjq(tab[i],f);
    printf("longueur %d  : ", file_lgr(f));
    printf("tete %d\n",file_tete(f));
    file_print(f);
 
    f= file_ins(f,2,2323);
    f = file_dd(f, 1);
    f= file_gg(f,1);
    printf("longueur %d  : \n", file_lgr(f));
    file_print(f);


    for(int i=0; i<12; i++)
    {
       
        f = file_supt(f); // c'est mieux de mettre f = ... en cas de file_vide
        
        file_print(f);
    }
    file_supt(f);
    file_print(f);

    return 0; 
}