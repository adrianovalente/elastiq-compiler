build: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	mkdir -p dist
	gcc -o dist/elastiq-compiler src/main.c src/utils/strings.c src/code-generator/temp-vars.c src/code-generator/code-repository.c src/code-generator/expression-evaluator.c src/code-generator/code-generator.c src/code-generator/code-generator-transition.c src/syntatic-analyser.c src/create_ape.c src/ape.c src/lexical-analyser.c src/token.c src/states-machine.c -I.

test: src/lexical-analyser.test.c src/states-machine.test.c src/lexical-analyser.c src/states-machine.c src/token.c
	@mkdir -p dist
	@gcc -o dist/states-machine.test src/states-machine.test.c src/states-machine.c -I.
	@gcc -o dist/lexical-analyser.test src/lexical-analyser.test.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	@gcc -o dist/syntatic-analyser.test src/syntatic-analyser.test.c src/syntatic-analyser.c src/code-generator/code-generator-transition.c src/create_ape.c src/ape.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	@gcc -o dist/code-generator.test src/code-generator/code-generator.test.c src/utils/strings.c src/code-generator/temp-vars.c src/code-generator/code-repository.c src/code-generator/expression-evaluator.c src/code-generator/code-generator.c src/code-generator/code-generator-transition.c src/syntatic-analyser.c src/create_ape.c src/ape.c src/lexical-analyser.c src/token.c src/states-machine.c -I.
	@./dist/states-machine.test
	@./dist/lexical-analyser.test src/fixtures/hello.el
	@./dist/syntatic-analyser.test
	@./dist/code-generator.test

clean: $
	\rm main
