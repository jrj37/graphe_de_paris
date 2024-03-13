
INCLUDE_PATH = ./headers
LDLIBS=-lm -ltps -lSDL2 -lSDL2_ttf

graph : objects/main.o objects/fichierBinaire.o objects/ParseOption.o objects/MST.o objects/utilitaires.o objects/ui.o headers/*.h
	gcc -O1 -o graph objects/main.o objects/fichierBinaire.o objects/ParseOption.o objects/MST.o objects/utilitaires.o objects/ui.o $(LDLIBS) -Wall -Wextra

test : objects/tests.o objects/fichierBinaire.o objects/ParseOption.o objects/MST.o objects/utilitaires.o objects/ui.o
	gcc -o tests/tests_unit objects/tests.o objects/fichierBinaire.o objects/ParseOption.o objects/MST.o objects/utilitaires.o objects/ui.o $(LDLIBS) -Wall -Wextra
objects/tests.o : tests/tests.c
	gcc -o objects/tests.o -c tests/tests.c -Wall -Wextra -I$(INCLUDE_PATH)

objects/%.o : sources/%.c
	mkdir -p objects
	gcc -O1 -o $@ -c $< -Wall -Wextra -I$(INCLUDE_PATH)



clean : 
	rm -f graph
	rm -f tests/tests_unit
	rm -f objects/*.o

doc:
	doxygen Doxyfile