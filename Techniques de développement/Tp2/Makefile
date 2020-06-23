CFLAGS = -Wall -c 
MYNAME= Bogdanas_Constantin
VERSION= _v2.0
IFLAGS = -I$(INCPATH)
ARCHIVE=$(MYNAME)$(VERSION)
INCPATH = include
OBJPATH = obj
SRCPATH = src
MOVE = mv $@ $(OBJPATH)/

vpath %.h $(INCPATH)
vpath %.c $(SRCPATH)
vpath %.o $(OBJPATH)
vpath main 
	
	
exe: main.o alea.o io.o tri.o 
	gcc -Wall -o exe $(OBJPATH)/main.o $(OBJPATH)/alea.o $(OBJPATH)/io.o $(OBJPATH)/tri.o 
	
main.o: main.c
	gcc $(CFLAGS) -o main.o $<
	mkdir $(OBJPATH)
	$(MOVE)
alea.o: $(SRCPATH)/alea.c 
	gcc $(CFLAGS) -o alea.o $< $(IFLAGS)
	$(MOVE)
io.o: io.c  
	gcc $(CFLAGS) -c -o io.o $<
	$(MOVE)
tri.o: $(SRCPATH)/tri.c  
	gcc $(CFLAGS) -c -o tri.o $<
	$(MOVE)

clean :
	-rm exe 
	-rm -r $(OBJPATH)
	@echo Clean!

dist :
	tar -czf $(ARCHIVE).tar.gz \
		src/*.c include/*.h Makefile





