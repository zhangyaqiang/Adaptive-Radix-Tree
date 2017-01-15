strsearch:strsearch.o trie.o
	gcc strsearch.c trie.o -o strsearch
strsearch.o:strsearch.c trie.c
	gcc -c strsearch.c -o strsearch.o
trie.o:trie.c
	gcc -c trie.c -o trie.o
clean:
	rm -rf*.o strsearch
