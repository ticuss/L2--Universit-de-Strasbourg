// TP3 

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "listeg.h"
#include "listeui.h"
#include "dico.h"
#include "graphurbain.h"


/******************************************/
/******************************************/
int main(int argc, char* argv[])
{
	unsigned short i, j;
	grapheurbain g = grapheurbainNouv();

	// on utilise la table dico pour associer un nom (chaine de car) a chaque identifiant
	Dico rues = newDico();
	adj(rues, "Zellenberg", 1); 
	adj(rues, "Chapelle", 2);
	adj(rues, "Altkirch", 3);
	adj(rues, "Haute", 4);
	adj(rues, "Ancienne ecole",5);
	adj(rues, "Saint Hippolyte",6);
	adj(rues, "Ziegelfeld",7);

	Dico carf = newDico();
	adj(carf, "ZW222", 1);
	adj(carf, "ZW221", 2); 
	adj(carf, "ZW231", 3); 
	adj(carf, "ZW232", 4); 
	adj(carf, "ZW233", 5); 
	adj(carf, "ZW234", 6); 
	adj(carf, "ZW241", 7);
	adj(carf, "ZW251", 8); 
	adj(carf, "ZW250", 9); 
	adj(carf, "ZW211", 10); 
	adj(carf, "ZW100", 11); 

	printf("\nCr�er et Tester le graphe urbain\n");
	// on cr�e les 11 carrefours precedents dans le graphe
	for (unsigned int i=1; i<=11; i++) addCarrefour(&g, i);
	// on cr�e les arcs (rues)
	addRueDoubleSens(&g, getIdent(carf,"ZW222"), getIdent(carf, "ZW221"), getIdent(rues, "Ziegelfeld"));
	addRueDoubleSens(&g, getIdent(carf,"ZW221"), getIdent(carf, "ZW231"), getIdent(rues, "Ziegelfeld"));
	addRueDoubleSens(&g, getIdent(carf,"ZW241"), getIdent(carf, "ZW231"), getIdent(rues, "Ziegelfeld"));
	addRueDoubleSens(&g, getIdent(carf,"ZW250"), getIdent(carf, "ZW241"), getIdent(rues, "Ziegelfeld"));
	addRueDoubleSens(&g, getIdent(carf,"ZW250"), getIdent(carf, "ZW251"), getIdent(rues, "Zellenberg"));
	addRueDoubleSens(&g, getIdent(carf,"ZW234"), getIdent(carf, "ZW251"), getIdent(rues, "Altkirch"));
	addRueDoubleSens(&g, getIdent(carf,"ZW233"), getIdent(carf, "ZW234"), getIdent(rues, "Saint Hippolyte"));
	addRueDoubleSens(&g, getIdent(carf,"ZW232"), getIdent(carf, "ZW233"), getIdent(rues, "Saint Hippolyte"));
	addRueDoubleSens(&g, getIdent(carf,"ZW231"), getIdent(carf, "ZW232"), getIdent(rues, "Saint Hippolyte"));
	addRueDoubleSens(&g, getIdent(carf, "ZW100"), getIdent(carf, "ZW233"), getIdent(rues, "Haute"));
	addRue(&g, getIdent(carf, "ZW231"), getIdent(carf, "ZW211"), getIdent(rues, "Ancienne ecole"));
	
	printf("Dans le graphe urbain:\n");
	char *str;

	printf("Le carrefour ZW233 est incident aux rues:\n");
	listeui crois = ruesDeCarrefour(g, getIdent(carf, "ZW233"));
	for (i = 0; i<longlui(crois); i++)
	{
		str = getStr(rues, kiemelui(crois, i));
		printf("%s\n", str);
	}
	destroylui(crois);

	printf("La rue Zellenberg croise:\n");
	crois = ruesCroisement(g, getIdent(rues,"Zellenberg"));
	for (i = 0; i<longlui(crois); i++)
	{
		str = getStr(rues, kiemelui(crois, i));
		printf("rue %s\n", str);
	}
	destroylui(crois);

	grapheurbainFree(g);

	freeDico(rues);
	freeDico(carf);

	return 0;
}
