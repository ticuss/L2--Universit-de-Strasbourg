
#
# Ce makefile permet de générer les sorties de chronos pour les
# exemples de ce répertoire, avec un scénario qui consiste à envoyer
# SIGTERM au bout d'un certain délai.
#
# Utilisation : make <cible>
# <cible> peut être "all", "clean", ou un nom de fichier .stderr
# pris dans la liste ci-dessous (variable FILES).
#
# Utilise ../run.sh, qui lui-même exécute ../chronos
#
# Les fichiers de sortie s'appellent *.stderr, et correspondent à ce
# qui atteint le canal d'erreur standard.
#
# Les fichiers *.stderr.ref sont des sorties réalisées avec une
# version de référence, afin que vous puissiez y comparer vos sorties,
# sachant que beaucoup de choses peuvent varier (le temps, l'ordre des
# arrêts de processus, etc.)
#

# Ajouter -z ci-dessous pour débuter à la seconde zéro
RUN=../run.sh

FILES= \
	sujet.12secondes.stderr \
	jack.2cycles.stderr \
	sequential.3cycles.stderr \
	overtake.3cycles.stderr \
	rush.2cycles.stderr \
	overlap.3cycles.stderr \
	pipeline.3cycles.stderr

all: $(FILES)

sujet.12secondes.stderr:
	$(RUN) ../sujet.table 12 TERM > /dev/null 2> $@

jack.2cycles.stderr: jack.table
	$(RUN) $< 14.5 TERM > /dev/null 2> $@

sequential.3cycles.stderr: sequential.table
	$(RUN) $< 7.5 TERM > /dev/null 2> $@

overtake.3cycles.stderr: overtake.table
	$(RUN) $< 15.5 TERM > /dev/null 2> $@

rush.2cycles.stderr: rush.table
	$(RUN) $< 18.5 TERM > /dev/null 2> $@

overlap.3cycles.stderr: overlap.table
	$(RUN) $< 12.5 TERM > /dev/null 2> $@

pipeline.3cycles.stderr: pipeline.table
	$(RUN) $< 15.5 TERM > /dev/null 2> $@


clean:
	rm -f $(FILES)
