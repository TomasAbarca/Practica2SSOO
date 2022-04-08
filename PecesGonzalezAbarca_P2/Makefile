DIROBJ := obj/
DIREXE := exec/
DIRSRC := src/
DIRHEA := include/
DIRBOOKS := Books/

CFLAGS :=  -I$(DIRHEA) -Wall -ansi
LDLIBS := -pthread -std=c++11
CC := g++

all : dirs ssooiigle exe

dirs:
	mkdir -p $(DIROBJ) $(DIREXE)

ssooiigle:
	$(CC) -o $(DIROBJ)SSOOIIGLE.o $(DIRSRC)SSOOIIGLE.cpp $(CFLAGS) -c $(LDLIBS)

exe:
	$(CC) -o $(DIREXE)SSOOIIGLE $(DIROBJ)SSOOIIGLE.o $(CFLAGS) $(LDLIBS)

test_a:
	./$(DIREXE)SSOOIIGLE $(DIRBOOKS)ACTITUD-DE-VENDEDOR.txt escuela 7

test_b:
	./$(DIREXE)SSOOIIGLE $(DIRBOOKS)25-MANERAS-DE-GANARSE-A-LA-GENTE.txt falta 14

test_c:
	./$(DIREXE)SSOOIIGLE $(DIRBOOKS)SEAMOS-PERSONAS-DE-INFLUENCIA.txt usted 20

clean:
	rm -r $(DIREXE) $(DIROBJ)