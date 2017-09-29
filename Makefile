lexical: src/main.c src/lexical.c
	\mkdir -p dist
	gcc -o dist/lexical src/main.c src/lexical.c -I.

test: src/lexical.test.c src/lexical.c
	\mkdir -p dist
	gcc -o dist/lexical.test src/lexical.test.c src/lexical.c -I.
	./dist/lexical.test

clean: $
	\rm main
