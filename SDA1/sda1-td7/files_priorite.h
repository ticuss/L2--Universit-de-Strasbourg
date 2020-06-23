
//author BOGDANAS CONSTANTIN 

typedef struct strfile {
    int priorite;   // priorité 1 ou 2 
    int data;       // donnes de processus
    struct strfile *nextproc, //suivant dans la liste de processus 
                   *prevproc,// recedent dans la liste de processus 
                   *suivant; //suivant dans la file de passage
} Strfile, *file;


// une file est implantée par une liste doublement chaînée avec 2 pointeur priorite et data 
// la valeur de nextproc du dernier élément pointe sur premier processus stoqué dans data
// la valeur de prevproc du premier élément pointe sur le dernier processus dans la 2eme file qui est en priorité 2
// sur le dernier élément (l'adjonction en queue change donc le point d'accès)
// si j'ai bien compris il faux faire 2 files circulaire une a partir de l'autre par rapport au priorité




/* 2 variante je suis pas sur si on peux resoudre le td utilisant cette structure 

typedef struct strFile{
    int data; //donnes de proc
    struct strFile *next ;// suivant dans la liste de passsage
}strFile;

typedef struct sfile{
    strFile *nextproc; // proc suivant
    strFile *prevproc;//proc precedent

}File;

*/





/*spec FILE0(TRIV) étend BASE
 sorte 
   File

opérations

    filevide : -> File File // creation de deux file priorité 1 et 2 
    adjq : S File -> File 
     adjq_1_2 : S Nat File -> File // S = valeur/processus | nat = priorité  | file 
    supt : File -> File
    tete : File -> S
    estvide : File -> Bool
    lgr : File -> Nat //nb des processus total
    file_ins : S Nat file  -> file // insertion dans la position Nat  
    file_dd : Nat File -> file // decalage a droite 
    file_gg : Nat File -> file//    decalage a gauche 
    chg_de_position :Nat Nat1 File -> file // Nat = dans quelle position on veux changer le processus || Nat1 = position initiale de proc 
    sup_ieme : Nat File -> File
vars e x  : S
vars f : File
vars p : priorite
préconditions

   pre supt(f) = not vide(f)
   pre tete(f)= not estvide(f)
    pre file_dd = not_ estvide(f)
    file_gg = not est_vide(f)
    chg_de_position = not esy_vide(f)
    pre supt_ieme(f) = not vide(f)
axiomes

   estvide(filevide) = Vrai
   estvide(adjq(e,f)) = Faux
   lgr(filevide) = 0
   lgr(adjq(e,f)) = 1 + lgr(f)
   tete(adjq(x,f)) = si estvide(f) alors x sinon tete(f) fsi
   supt(adjq(x,f)) = si estvide(f) alors filevide sinon adjq(x, supt(f)) fsi
    file_ ins(x, file_vide) =  adjq(x,f); 
    file_ins (x,adjq(x,f)) = if x => lgr(f) alors adjq(x,f)
    dd(adjq(e, f), n) =     si n =>lgr(f);
                                        alors adjq(e,f)
                                            else dd(adjq(x,f) , n) fsi.
    chg_de_position(x,y,file_vide) = file_vide ;
    chg_ de position(x,y,adjq(f,z)) =  si x== y alors adjq(f,z)
                                        else adjq(chg_de_position(l,z,y),x) 
        fsi
    sup_ieme(n, adjq(y,f)) = si estvide(f) alors file_vide 
                                            sinon adjq(x,sup_ieme(f));

fspec
*/





