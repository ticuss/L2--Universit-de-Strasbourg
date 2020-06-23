#!/bin/bash
#
# Ce script exécute "chronos" et lui envoie des signaux selon un
# scénario passé en argument.
#
# Il doit se trouver dans le même répertoire que le programme chronos
#
# Usage : ./run.sh [-z] fichier.table delai1 sig1 delai2 sig2 ...
#
# - si l'option "-z" est présente, le script attend le début de la
#   minute suivante (afin de commencer à la seconde zéro).
# - fichier.table est l'argument passé à chronos
# - les arguments suivants sont une alternance d'entiers et de
#   noms/numéros de signaux en nombre pair (voir exemple ci-dessous)
#
# Ce script lance chronos avec le fichier.table, puis, pour chaque
# couple d'arguments "<delai> <sig>", il fait :
#
# - sleep <delai>
# - kill -<sig> <process-id-de-chronos>
#
# Il n'y a aucune vérification que <delai> est un nombre et que <sig>
# est un argument correct pour kill. Un <délai> sans <sig> à la fin
# est silencieusement ignoré.
#
# Quand tous les arguments ont été traités, ou quand SIGTERM a été
# envoyé, il attend une seconde et si le processus existe toujours il
# lui envoie SIGTERM (si ce n'est pas déjà fait), puis attend sa
# terminaison.
#
# Exemples :
#
# ./run.sh exemples/jack.table 14.5 TERM
# -> envoie SIGTERM après 14.5 secondes
#
# ./run.sh exemples/sequential.table 1.5 USR2 2 USR2 3 USR1 7.5 USR1 9.5 TERM
# -> envoie SIGUSR2 après 1.5 seconde, USR2 après 3.5 secondes, USR1
#    après 6.5 secondes, etc.
#
# Voir les autres exemples dans le fichier exemples/Makefile
#

# Environnement
set -u
WDIR=$(dirname $0)
# Test de l'existence du programme
PROG=$WDIR/chronos
if ! test -x $PROG; then
    echo "Executable $PROG introuvable"
    exit 1
fi
# Analyse des arguments
SECONDZERO=0
if test "$1" = "-z"; then
    SECONDZERO=1
    shift
fi
TABLE=$1
shift
if ! test -r "$TABLE"; then
    echo "Table $TABLE introuvable"
    exit 1
fi
# Alignement sur zéro le cas échéant
if test $SECONDZERO -eq 1; then
    sleep $(date +"%S.%N" | awk '{print (60-$1+0.1);}')
fi
# On lance le programme
$PROG "$TABLE" & PROGPID=$!
# On exécute le scénario
TERMSENT=0
while test $TERMSENT -eq 0 -a $# -gt 1; do
    sleep $1
    kill -$2 $PROGPID
    if test $2 = "TERM" -o $2 = "SIGTERM" -o $2 = "15"; then
        TERMSENT=1
    fi
    shift 2
done
# Fin du scénario, terminaison d'office si nécessaire/possible
sleep 1
if test $TERMSENT -eq 0 && kill -0 $PROGPID &> /dev/null; then
    kill -TERM $PROGPID
fi
wait $PROGPID
# Fin
exit 0
