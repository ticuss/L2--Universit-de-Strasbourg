main: main.o listeui.o listeg.o dico.o graphurbain
	gcc -g $^ -o $@ 

main.o: main.c dico.h graphurbain.h
	gcc -g -c $^

listeui.o: listeui.c listeui.h
	gcc -g -c $^

graphurbain.o: graphurbain.h
	gcc -g -c $^

listeg.o: listeg.c listeg.h
	gcc -g -c $^

dico.o: dico.c dico.h listeg.h listeui.h
	gcc -g -c $^
	