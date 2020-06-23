
#include "polo.h"
// fichier polo.c


char * sget_int(char *s, int *val){
    *val=0;
    for(;*s >= '0' && *s <= '9';s++)
    *val = (*s - '0') + 10 * *val;
    return s;
    }


float sget_float(char *s){
    float val= 0.0;
    int len = strlen(s);
    int dotPosition = 0;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '.')
        {
          dotPosition = len - i  - 1;
        }
        else
        {
          val = val * 10.0 + (s[i]-'0');
        }
    }
        while (dotPosition--)
      {
        val /= 10.0;
      }

    return val;
}
      
    void test (){
        
        char s = '9';
        char string[] = "42.1";
        int val = 0;
        printf("  int = %d    ",*sget_int(&s,&val));

        printf("float = %f",sget_float(string));
                
    }


void raler(const char *msg)
{
	fprintf(stderr, "%s", msg);
	abort();
}

float poloInv(Pile p ,char *s)
{
    float a;
	char *e, *w = "\n";
	for (s = strtok(s, w); s; s = strtok(0, w)) {
		a = strtof(s, &e);
		if (e > s) empiler(p,a);
		else if (*s == '+'){          
            empiler(p,p->tab[p->h-2] + p->tab[p->h-1]) ;
		            }
        else if (*s == '-'){
            empiler(p,p->tab[p->h-2] - p->tab[p->h-1]) ;
        }
		else if (*s == '*')
             empiler(p,p->tab[p->h-2] * p->tab[p->h-1]) ;
        else if (*s == '/')	
            empiler(p,p->tab[p->h-2] / p->tab[p->h-1]) ;
        else if (*s == '^')	
            empiler(p,powf(p->tab[p->h-2], p->tab[p->h-1]));
        else {
			fprintf(stderr, "'%c': ", *s);
			raler("unknown oeprator\n");
		}
	
	}
 
	return p->tab[p->h-1];
     }



int main(void)
{
    Pile p=pileNouv();
    char s[256];
    printf("Introduisez un calcul, par exemple: 32.7  5  +  2.23  42e-1  +  *  \n");
    fgets(s, 255, stdin);
	printf(" Le resultat est: %g \n", poloInv(p,s));
    
	return 0;
}