#include "expression.h"

t_symcle tabcle[NBCLE] = {
    { "+", A1 },
	 { "-", A2 },
	  { "*", A3 },
	   { "/", A4 },
	    { "min", A5 },
		 { "max", A6 },
  		  { "sqrt", B1 },
	 		{ "exp", B2 },
	  			{ "ln", B3 }, 
	  			 { "abs", B4 }, 
	  			  { "floor", B5 }, 
	  			{ "ceil", B6 }
};



int keyfromstring(char* cle)
{
    unsigned int i;
    for (i=0; i < NBCLE; i++) 
    {
        t_symcle *sym = &tabcle[i];
        if (strcmp(sym->cle, cle) == 0)
            return sym->val;
    }
    return BADKEY;
}

int convert_type(char* str, double* a)
{
	char r;
	int size=strlen(str);	
	int err=0;
	int point=0;
	int i=0;
	if(str[0]=='-')
		i=1;
	for(;i<size;i++)
	{
		r=str[i];
		if(r=='.')
		{
			if(point==1 || i==0)
			{	
				err=1;
				i=size;
			}
			else
				point=1;
		}
		else if(r<'0' || r>'9') 
		{
			err=1;
			i=size;
		}
	}
	if(err==0)
		*a=atof(str);
	return err;
}

expr initial(char** str,int* pos,int* err)
{
	int i=*pos;
	*pos+=1;
	if(str[i]==NULL)
		return NULL;
	else
	{
		expr e=(expr)malloc(sizeof(struct abin));
		e->fd=NULL;
		e->fg=NULL;
		int isbin=0;
		double a;
		int c = keyfromstring(str[i]);
		switch(c)
		{
			case A1:/* + */
			case A2:/* - */
			case A3:/* * */
			case A4:/* / */
			case A5:/* min */
			case A6:/* max */
				e->descri=c;
				isbin=1;
				break;
			case B1:/* sqrt */
			case B2:/* exp */
			case B3:/* ln */
			case B4:/* abs */
			case B5:/* floor */
			case B6:/* ceil */
				e->descri=c;
				break;				
			case BADKEY:
				if(convert_type(str[i],&a)==0)
				{
					e->descri=c;
					e->val=a;
					break;
				}
				else
				{
					write(2,"Operateur ou operande inconnu :",31);
					write(2,str[i],strlen(str[i]));
					write(2,"\n",2);
					printf("ERROR\n");
					*err=1;
					return e;
				}
		}
		if(e->descri!=13)
		{
			if(isbin==0)
			{
				if(str[*pos]==NULL)
				{
					write(2,str[i],strlen(str[i]));
					write(2," attend un argument\n",21);
					printf("ERROR\n");
					*err=1;
					return e;
				}
				e->fd=NULL;
				e->fg=initial(str,pos,err);
			}
			else
			{
				if(str[*pos]==NULL)
				{
					write(2,str[i],strlen(str[i]));
					write(2," attend deux arguments\n",24);
					printf("ERROR\n");
					*err=1;
					return e;
				}
				e->fd=initial(str,pos,err);
				if(str[*pos]==NULL)
				{
					write(2,str[i],strlen(str[i]));
					write(2," attend deux arguments\n",24);
					printf("ERROR\n");
					*err=1;
					return e;
				}
				e->fg=initial(str,pos,err);
			}
		}
		return e;
	}
}

expr creation(char* str)
{
	int err=0;
	int i,j=2;
	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]==' ')
			j++;
	}
	char** s=(char**)malloc(j*sizeof(char*));
	char* token=strtok(str," ");
	i=0;
	while(token!=NULL)
	{
		s[i]=(char*)malloc(strlen(token)+1);
		strcpy(s[i],token);
		token=strtok(NULL," ");
		i++;
	}
	s[i]=NULL;
	i=0;
	expr res=initial(s,&i,&err);
	if(err==1)
	{
		free_expr(res);
		free_mem(s);
		return NULL;
	}
	free_mem(s);
	return res;
}

double calcul_expr(expr e, int* err)
{
	if(e==NULL)
	{
		*err=1;
		return 0.0;
	}
	double a,b;
	int c;
	switch(e->descri)
	{
	case A1:/* + */
		a=calcul_expr(e->fd,err)+calcul_expr(e->fg,err);
			break;
	case A2:/* - */	
		a=calcul_expr(e->fd,err)-calcul_expr(e->fg,err);
			break;
	case A3:/* * */
			a=calcul_expr(e->fd,err)*calcul_expr(e->fg,err);
			break;
	case A4:/* / */
		b=calcul_expr(e->fg,err);
			if(b==0.0)
			{
				write(2,"Division par 0: impossible\n", 28);
				printf("ERROR\n");
				*err=1;
			}
		a=calcul_expr(e->fd,err)/b;
			break;
		
	case A6:/* max */
		a=calcul_expr(e->fd,err);
		b=calcul_expr(e->fg,err);
			if(a<b)
				a=b;
			break;
			case A5:/* min */
		a=calcul_expr(e->fd,err);
		b=calcul_expr(e->fg,err);
			if(a>b)
				a=b;
			break;
	case B1:/* sqrt */
		b=calcul_expr(e->fg,err);
			if(b<0.0)
			{
				write(2,"Racine carre d'un negatif: impossible\n", 39);
				printf("ERROR\n");
				*err=1;
			}
		a=sqrt(b);
			break;
	case B2:/* exp */
		a=exp(calcul_expr(e->fg,err));
			break;
	case B3:/* ln */
		b=calcul_expr(e->fg,err);
			if(b<=0.0)
			{
				write(2,"ln d'un nombre negatif est impossible\n", 29);
				printf("ERROR\n");
				*err=1;
			}
		a=log(b);
			break;
	case B4:/* abs */
		a=calcul_expr(e->fg,err);
			if(a<0.0)
				a*=(-1.0);
			break;
	case B5:/* floor */
		a=floor(calcul_expr(e->fg,err));
		c = 0 + (int)a;
		a=(double)c;
			break;
	case B6:/* ceil */	
		a=ceil(calcul_expr(e->fg,err));
			break;
	case BADKEY:
			a=e->val;
			break;
	}
	return a;
}


void free_expr(expr e)
{
	if(e!=NULL)
	{
		free_expr(e->fd);
		free_expr(e->fg);

		free(e);
	}
}

void free_mem(char ** str)
{
	int i=0;
	while(str[i]!=NULL)
	{
		free(str[i]);
		i++;
	}
	free(str[i]);
	free(str);
	return;
}