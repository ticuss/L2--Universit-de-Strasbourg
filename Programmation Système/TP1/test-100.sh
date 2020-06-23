#!/bin/bash

# Script de test. Il y a 5 tests différents :
#
# 1. Test du nombre d'arguments
# 2. Test de validité des arguments et accessibilité
# 3. Test de comportement
# 4. Test en charge
# 5. Test mémoire (valgrind)
#
# Usage: test.sh t1 t2...
# (où chaque ti est un numéro entre 1 et 5)
# Par exemple :
#     ./test.sh 1 2 3
#     ./test.sh 1 4
#
# Le script s'arrête à la première erreur
# Hypothèse : le programme renvoie 1 en cas d'erreur, 0 sinon

# Analyse des arguments
declare -a TESTS
TESTS=([1]=0 [2]=0 [3]=0 [4]=0 [5]=0)
for t in "$@"; do
    if test 1 -le "$t" -a "$t" -le 5; then
        TESTS[$t]=1
    else
        echo "Parameter $t invalide"
        exit 1
    fi
done

# Recherche de l'exécutable
PROG=./backup
if ! test -x $PROG; then
    echo "Executable $PROG introuvable"
    exit 1
fi

# Identification
TEST=$(basename $0 .sh)
WDIR=$(realpath $(dirname $0))

# Répertoire temporaire pour les fichiers de test
# (dans le répertoire courant par défaut -- man mktemp)
TMPDIR=$(mktemp -d "tmp.XXX")
LOG=$TEST.log
exec 2> $LOG

OUT=$TMPDIR/$TEST.out
ERR=$TMPDIR/$TEST.err

# Fonctions pour l'affichage
function debut_test () # numero titre
{
    echo -n "[  ] $1. $2... "
}
function fin_test ()
{
    echo -e "\r[ok]"
}
function fail () # erreur
{
    echo -e "\r[ko]"
    echo "==> Échec du test sur '$1'."
    echo "==> Log : '$LOG'."
    echo "==> Exit"
    rm -rf $TMPDIR
    exit 1
}

# pas de variable non définie, et affichage des commandes dans log
set -ux

########
#
# 1. Test du nombre d'arguments
#
if test ${TESTS[1]} -eq 1; then
    debut_test 1 "Test du nombre d'arguments"
    # Le programme doit afficher "Usage: ..." en cas d'arguments incorrects
    # Trop peu d'arguments, il faut échouer
    $PROG a1 a2 >$OUT 2>$ERR
    grep -iq "usage" $ERR || fail "Nombre d'argument invalide (2)"
    # Trop d'arguments, il faut échouer
    $PROG a1 a2 a3 a4 >$OUT 2>$ERR
    grep -iq "usage" $ERR || fail "Nombre d'argument invalide (4)"
    #
    rm -rf $OUT $ERR
    fin_test
fi

########
#
# 2. Test de validité des arguments et accessibilité de la source
#
if test ${TESTS[2]} -eq 1; then
    debut_test 2 "Test de validité et accessibilité"
    # Quand le répertoire source n'existe pas, il faut échouer
    $PROG inexistant inexistant inexistant &>/dev/null
    test $? -eq 1 || fail "Appel avec source inexistant"
    # Le répertoire de référence peut ne pas exister
    mkdir $TMPDIR/source
    $PROG $TMPDIR/source inexistant $TMPDIR/destination &>/dev/null
    test $? -eq 0 || fail "Appel avec reference inexistante"
    rmdir $TMPDIR/destination
    # Quand la destination existe déjà, il faut échouer
    mkdir $TMPDIR/destination
    $PROG $TMPDIR/source inexistant $TMPDIR/destination &>/dev/null
    test $? -eq 1 || fail "Appel avec destination existante"
    rmdir $TMPDIR/destination
    # Si la source ne peut être lue, il faut échouer
    chmod u-r $TMPDIR/source
    $PROG $TMPDIR/source inexistant $TMPDIR/destination &>/dev/null
    test $? -eq 1 || fail "Appel avec source non-lisible"
    rmdir $TMPDIR/destination
    chmod u+r $TMPDIR/source
    # Si le répertoire source n'est pas "parcourable", il faur échouer
    touch $TMPDIR/source/fichier
    chmod u-x $TMPDIR/source
    $PROG $TMPDIR/source inexistant $TMPDIR/destination &>/dev/null
    test $? -eq 1 || fail "Appel avec source non-parcourable"
    #
    chmod u+x $TMPDIR/source
    rm -rf $TMPDIR/{source,destination}
    fin_test
fi
########
#
# 3. Test de comportement
#
function make_file () # name
{
    # Fabrique un fichier de 5000 lignes aléatoirement sélectionnées
    shuf -n 5000 < /usr/share/dict/words > $1
}
if test ${TESTS[3]} -eq 1; then
    debut_test 3 "Test de comportement"
    # ignorer un fichier d'un type non supporté
    mkdir $TMPDIR/source $TMPDIR/source/ignore
    mkfifo $TMPDIR/source/ignore/unefifo
    $PROG $TMPDIR/source inexistant $TMPDIR/lundi >$OUT 2>$ERR
    test $? -eq 0 || fail "Echec avec un fichier exotique"
    grep -q "source/ignore/unefifo" $OUT || fail "Fichier à ignorer non affiché"
    rm -rf $TMPDIR/source/ignore
    # copier correctement un nouveau fichier, et lui donner la bonne date
    make_file $TMPDIR/source/regulier.txt
    $PROG $TMPDIR/source $TMPDIR/lundi $TMPDIR/mardi &>/dev/null
    test $? -eq 0 || fail "Echec avec un nouveau fichier"
    diff -q $TMPDIR/source/regulier.txt $TMPDIR/mardi/regulier.txt
    test $? -eq 0 || fail "Copie erronée d'un nouveau fichier"
    OLD=$(stat -c "%y" $TMPDIR/source/regulier.txt)
    NEW=$(stat -c "%y" $TMPDIR/mardi/regulier.txt)
    test "$OLD" = "$NEW" || fail "Date incorrecte sur fichier copié"
    # faire un lien correct vers un fichier existant
    $PROG $TMPDIR/source $TMPDIR/mardi $TMPDIR/mercredi &>/dev/null
    OLD=$(stat -c "%i" $TMPDIR/mardi/regulier.txt)
    NEW=$(stat -c "%i" $TMPDIR/mercredi/regulier.txt)
    test "$OLD" -eq "$NEW" || fail "Lien fautif vers un fichier inchangé"
    # faire un copie d'un fichier modifié
    make_file $TMPDIR/source/regulier.txt
    $PROG $TMPDIR/source $TMPDIR/mercredi $TMPDIR/jeudi &>/dev/null
    diff -q $TMPDIR/mercredi/regulier.txt $TMPDIR/jeudi/regulier.txt &>/dev/null
    test $? -eq 1 || fail "Echec avec un fichier modifié"
    # copier un lien symbolique
    (cd $TMPDIR/source; ln -s regulier.txt unsymlink)
    $PROG $TMPDIR/source $TMPDIR/jeudi $TMPDIR/vendredi &>/dev/null
    OLD=$(cd $TMPDIR/source; stat -c "%N" unsymlink)
    NEW=$(cd $TMPDIR/vendredi; stat -c "%N" unsymlink)
    test "$OLD" = "$NEW" || fail "Echec de la copie d'un symlink"
    #
    rm -rf $OUT $ERR $TMPDIR/{source,lundi,mardi,mercredi,jeudi,vendredi}
    fin_test
fi
########
#
# 4. Test de correction de la destination, en charge
#
function make_tree () # name depth subdirs(>0) files symlinks
{
    # Fabrique un répertoire "name" de profondeur "depth"
    # contenant une quantité aléatoire de sous-rep/fichiers/liens
    local name=$1 depth=$2 ndirs=$3 nfiles=$4 nsyms=$5
    if test $depth -gt 0; then
        mkdir $name
        for d in $(seq $((1 + (RANDOM % ndirs)))); do
            make_tree $name/dir-$d $((depth-1)) $ndirs $nfiles $nsyms
        done
        for f in $(seq $((RANDOM % (nfiles+1)))); do
            make_file $name/reg-$f
        done
        for l in $(seq $((RANDOM % (nsyms+1)))); do
            ln -s $name-$l-dangling $name/sym-$l
        done
    fi
}
function list_plinks () # dir file
{
    # Une liste triée de fichiers ordinaires, avec inode et mtime
    (cd $1; find . -type f -exec stat -c "%n %i %y" {} \; | sort) > $2
}
function list_slinks () # dir file
{
    # Une liste triée de symlinks avec cible
    (cd $1; find . -type l -exec stat -c "%N" {} \; | sort) > $2
}
if test ${TESTS[4]} -eq 1; then
    debut_test 4 "Test en charge"
    # Fabriquer un répertoire source, et réaliser une sauvegarde
    # qui doit être identique
    make_tree $TMPDIR/source 4 10 15 0
    $PROG $TMPDIR/source inexistant $TMPDIR/premiere &>/dev/null
    diff -rq $TMPDIR/source $TMPDIR/premiere
    test $? -eq 0 || fail "Sauvegarde (initiale) non identique"
    # Seconde sauvegarde avec une source inchangée depuis reference
    # Les trois répertoires doivent être identiques
    $PROG $TMPDIR/source $TMPDIR/premiere $TMPDIR/seconde &>/dev/null
    diff -rq $TMPDIR/source $TMPDIR/seconde
    test $? -eq 0 || fail "Sauvegarde incrementale non identique à la source"
    diff -rq $TMPDIR/premiere $TMPDIR/seconde
    test $? -eq 0 || fail "Sauvegarde incrementale non identique à la reference"
    # Vérifier que la seconde sauvegarde est bien constituée de liens physiques
    list_plinks $TMPDIR/premiere $TMPDIR/version1.links
    list_plinks $TMPDIR/seconde $TMPDIR/version2.links
    diff -q $TMPDIR/version1.links $TMPDIR/version2.links
    test $? -eq 0 || fail "Sauvegarde incrementale avec liens physiques fautifs"
    # On passe à une source contenant uniquement des liens symboliques
    rm -rf $TMPDIR/source $TMPDIR/premiere $TMPDIR/seconde
    make_tree $TMPDIR/source 4 10 0 15
    # Une seule sauvegarde, et vérification de la copie des liens symboliques
    $PROG $TMPDIR/source inexistant $TMPDIR/premiere &>/dev/null
    list_slinks $TMPDIR/source $TMPDIR/version1.links
    list_slinks $TMPDIR/premiere $TMPDIR/version2.links
    diff -q $TMPDIR/version1.links $TMPDIR/version2.links
    test $? -eq 0 || fail "Sauvegarde incrementale avec liens symboliques fautifs"
    #
    rm -rf $TMPDIR/{source,premiere}
    fin_test
fi
########
#
# 5. Test mémoire avec valgrind
#
function touch_tree () # name
{
    # modifie aléatoirement les fichiers réguliers du rep (et sous-rep)
    local rep=$1
    for e in $rep/*; do
        if test -f "$e"; then
            if test $((RANDOM % 2)) -eq 0; then
                touch "$e"
            fi
        elif test -d "$e"; then
            touch_tree "$e"
        fi
    done
}
if test ${TESTS[5]} -eq 1; then
    debut_test 5 "Test mémoire (valgrind)"
    # Fabriquer un répertoire source
    make_tree $TMPDIR/source 4 10 15 15
    # Une première sauvegarde, qui ne doit pas faire de fuites mémoire
    valgrind --leak-check=full --error-exitcode=100 \
             $PROG $TMPDIR/source inexistant $TMPDIR/premiere > /dev/null
    test $? = 100 && fail "test memoire 1/3"
    # Une seconde sauvegarde, incrémentale, testée idem
    valgrind --leak-check=full --error-exitcode=100 \
             $PROG $TMPDIR/source $TMPDIR/premiere $TMPDIR/seconde> /dev/null
    test $? = 100 && fail "test memoire 2/3"
    # Une troisième sauvegarde, après modif aléatoire
    touch_tree $TMPDIR/source
    valgrind --leak-check=full --error-exitcode=100 \
             $PROG $TMPDIR/source $TMPDIR/seconde $TMPDIR/troisieme > /dev/null
    test $? = 100 && fail "test memoire 3/3"
    #
    rm -rf $TMPDIR/{source,premiere,seconde,troisieme}
    fin_test
fi
########
#
# Tout est ok
#
rm -rf $TMPDIR
exit 0
