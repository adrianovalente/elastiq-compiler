#build-syntatic: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	# @mkdir -p dist
	# @gcc -o dist/syntatic src/main.c src/lexical-analyser.c src/syntatic-analyser.c src/create_ape.c  src/ape.c src/token.c src/states-machine.c -I.

build-lexical: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	@mkdir -p dist
	@gcc -o dist/lexical src/main.c src/lexical-analyser.c src/token.c src/states-machine.c -I.

test: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	@mkdir -p dist
	@gcc -o dist/states-machine.test src/states-machine.test.c src/states-machine.c -I.
	@gcc -o dist/lexical-analyser.test src/lexical-analyser.test.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	@gcc -o dist/syntatic-analyser.test src/syntatic-analyser.test.c src/syntatic-analyser.c src/create_ape.c src/ape.c src/lexical-analyser.c src/token.c src/states-machine.c -I.

	@./dist/states-machine.test
	@./dist/lexical-analyser.test src/fixtures/hello.el
	@./dist/syntatic-analyser.test

clean: $
	\rm main
