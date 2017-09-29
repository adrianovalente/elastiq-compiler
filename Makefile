lexical: src/main.c src/lexical.c
	\mkdir -p dist
	gcc -o dist/lexical src/main.c src/lexical.c -I.

clean: $
	\rm main
