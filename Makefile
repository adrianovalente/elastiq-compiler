build: src/main.c src/hellomake.c
	\mkdir -p dist
	gcc -o dist/elastiq-compiler src/main.c src/hellomake.c -I.

clean: $
	\rm main
