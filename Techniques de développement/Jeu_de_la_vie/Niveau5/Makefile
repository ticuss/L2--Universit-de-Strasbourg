.PHONY: all clean

LIBPATH=lib/

WARNFLAGS := -Wall -Wpedantic -Wextra -Waddress -Waggressive-loop-optimizations \
  -Wcast-qual -Wcast-align -Wmissing-declarations \
  -Wdouble-promotion -Wuninitialized -Winit-self \
  -Wstrict-aliasing -Wsuggest-attribute=const -Wtrampolines -Wfloat-equal \
  -Wshadow -Wunsafe-loop-optimizations -Wlogical-op \
  -Wdisabled-optimization -Wconversion -Wunused-result
CPPFLAGS += -Iinclude -I/usr/include/cairo
CFLAGS += -Wall -Wextra
LDLIBS +=-lm -L$(LIBPATH)  -lX11 -lcairo  -ljeu
MYNAME= Bogdanas_Constatin
VERSION=_v3.0
OBJPATH=obj/
BINPATH=bin/
DOCGEN=doxygen Doxyfile
ARCHIVE=$(MYNAME)$(VERSION)
RM=rm -rf $(OBJPATH) $(BINPATH) $(LIBPATH)

vpath %.h include/
vpath %.c src/

ifneq ($(MODE),TEXTE)
all:$(BINPATH)cairo
else 
all:$(BINPATH)main
endif

$(BINPATH)main: $(addprefix $(OBJPATH), main.o) $(LIBPATH)libjeu.a | $(BINPATH)
	gcc   $(LDFLAGS) -o $@ $< $(LDLIBS)
	@echo Compilation texte avec success!

$(BINPATH)cairo: $(addprefix $(OBJPATH),main_cairo.o ) $(LIBPATH)libjeu.a | $(BINPATH)
	gcc   $(LDFLAGS) -o $@ $< $(LDLIBS)
	@echo Compilation cairo avec success!
	
$(LIBPATH)libjeu.a: $(addprefix $(OBJPATH), graphics.o grille.o io.o jeu.o ) |$(LIBPATH)
	ar -crv $@ $^

$(OBJPATH)main.o: main.c grille.h io.h jeu.h

$(OBJPATH)main_cairo.o: graphics.h settings.h main_cairo.c 

$(OBJPATH)grille.o: grille.h grille.c

$(OBJPATH)io.o: io.h io.c grille.h

$(OBJPATH)jeu.o: jeu.h jeu.c

$(OBJPATH)graphics.o: graphics.c graphics.h settings.h 



$(OBJPATH)%.o : %.c | $(OBJPATH)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o  $@

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(BINPATH):
	mkdir -p $(BINPATH)

$(LIBPATH):
	mkdir -p $(LIBPATH)

clean:
	@$(RM) 
	@echo Clean!

dist:
	tar -czf $(ARCHIVE).tar.gz \
		src/*.c include/*.h  Makefile Doc  grilles/*.txt   README.md

doc:
	$(DOCGEN)
 
