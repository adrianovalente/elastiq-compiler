make: src/main.c src/lexical.c
	\mkdir -p dist
	gcc -o dist/lexical src/main.c src/lexical.c -I.

test: src/states-machine.test.c src/states-machine.c
	@mkdir -p dist
	@gcc -o dist/states-machine.test src/states-machine.test.c src/states-machine.c -I.
	@./dist/states-machine.test

clean: $
	\rm main
