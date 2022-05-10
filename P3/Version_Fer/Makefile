DIROBJ := obj/
DIREXE := exec/
DIRHEA := include/
DIRSRC := src/
DIRCLI := Clients/

CFLAGS := -I$(DIRHEA) -pthread -std=c++11
FILES  := $(DIRSRC)LineResult.cpp $(DIRSRC)ThreadResult.cpp $(DIRSRC)OrderQueue.cpp
CC     := g++

all: dirs SSOOIIGLE main

dirs: 
	mkdir -p $(DIREXE) $(DIROBJ)

SSOOIIGLE: 
	$(CC) $(CFLAGS) $(DIRSRC)SSOOIIGLE.cpp -o $(DIROBJ)SSOOIIGLE.o $(FILES) $(CFLAGS)

main: 
	$(CC) -o $(DIREXE)SSOOIIGLE $(DIRSRC)SSOOIIGLE.cpp $(FILES) $(CFLAGS)

execute: 
	$(DIREXE)SSOOIIGLE

clean: 
	rm -r $(DIREXE) $(DIROBJ) $(DIRCLI)
