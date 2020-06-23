#include "expression.h"

// void prompt est la fonction d'affichage de >>> avant chaque calcul 
//en apliquant cette fonction, l'affichage est bon mais l'exection du fichier check.sh donne
//des erreurs du coup j'ai décidé de le metre en commentaire car je n'ai pas reussi a le resoudre.

static inline void prompt(FILE* const input, FILE* const output)
{
  if (isatty(fileno(input)) && isatty(fileno(output)))
    fprintf(output, "\033[1m>>>\033[0m ");
}

int main(void)
{
    expr e;
    double result;
    int valid=0;
	char buffer[1024];

	//for (prompt(stdin, stdout); (fgets(buf,1024,stdin))!= NULL; prompt(stdin, stdout))
	while((fgets(buffer,1024,stdin))!= NULL)
	{
		buffer[strlen(buffer)-1]='\0';
		if(buffer[0]!='\n' && buffer[0]!='#')
		{
			e=creation(buffer);
			if(e!=NULL)
			{
				result=calcul_expr(e,&valid);
				if(valid!=1)
					printf("%.4f\n",result);
			}
			free_expr(e);
		}
	}
	return 0;
}




