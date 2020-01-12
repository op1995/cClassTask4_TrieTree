all: frequency

frequency: trieTree.c trieTree.h
	gcc -Wall trieTree.c -o frequency

.PHONY: clean all 

clean:
	rm -f *.o all frequency *.out