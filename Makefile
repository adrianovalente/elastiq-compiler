build: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	\mkdir -p dist
	gcc -o dist/lexical src/main.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	gcc -o dist/lexical src/main.c src/lexical-analyser.c src/token.c src/states-machine.c -I.

test: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	@mkdir -p dist
	@gcc -o dist/states-machine.test src/states-machine.test.c src/states-machine.c -I.
	@gcc -o dist/lexical-analyser.test src/lexical-analyser.test.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	@./dist/states-machine.test
	@./dist/lexical-analyser.test src/fixtures/hello.el

clean: $
	\rm main
