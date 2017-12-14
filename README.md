<p align="center">
<img src="https://user-images.githubusercontent.com/8186616/30614558-44fa0604-9d62-11e7-8515-7e3314535a7c.png"/>
<h2 align="center">Hello <s>World</s> Elastiq.</h2>
</p>

> elastiq is a flexible and simple imperative programming language you can use to build great applications

[![Build Status](https://travis-ci.org/adrianovalente/elastiq-compiler.svg?branch=master)](https://travis-ci.org/adrianovalente/elastiq-compiler)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)]()
[![platforms](https://img.shields.io/badge/platform-linux--64%20%7C%20osx--64-orange.svg)]()

```
PROGRAM

VAR hello, world;

hello := 3;
world := 2 * hello + 5;

END PROGRAM;
```

## Getting Started
To have a copy of the compiler running on your computer, just `git clone` it and then run `make`.

After that, you can compile a `.el` file using the generated binary:

``` bash
./dist/elastiq-compiler tests/fixtures/factorial.el factorial.mvn
```

<img src="http://g.recordit.co/lOaswZN7To.gif" width="80%"/>

Once it's compiled, you can use the MVN Simuulator to run the code:

``` bash
./bin/mounter factorial
```

## But how it works?
**elastiq** is a language created during our [PCS2056 (Languages and Compilers)](https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=PCS2056) course. It was built with a **Lexical Analyzer (tokenizer)**, a **Syntactic Analyzer** and a **Code Generator**.

### Lexical Analyzer
Extracts tokens from the source code, such as:
  - identifiers (such as variable names);
  - numbers;
  - arithmetic operators;
  - logical operators;
  - control structures such as `if`s and `while`s

<!-- You can take an example of program written in *Elastiq* [here](./src/fixtures/hello.el). -->

The [Lexical Analyzer](https://en.wikipedia.org/wiki/Lexical_analysis) is responsible for parsing the source code and outputting `tokens`.

<!-- ![image](http://g.recordit.co/9FLVepoRb0.gif) -->

### Syntactical Analyzer
Syntax Analysis will verify if the program is valid and will also generate a syntactic tree.
You can see the Wirth Notation for *Elastiq* [here](./src/fixtures/syntax.wirth).

Identifiers and Numbers are ignored here because Lexical Analyzer already holds it.

To build the syntactic analyzer, just the following command:
``` bash
make build-syntatic
dist/lexical /path/to/your/file.el
```

![image](http://g.recordit.co/GNq28A5OBz.gif)

## Special Thanks
Special thanks to [Roro](https://github.com/rogerioyuuki), who helped us with his [Automata Generator](https://github.com/rogerioyuuki/poli-github/blob/master/compiladores/entrega3/syntax/), a Python Script that writes down the C code for a Stack Automata from any With Notation.

## Contributing and Testing
Please feel free to open a pull request or open a issue. There are automated tests you can run with `make test` (or, if you are a js-fanboy like me, you can also `npm test` or `npm run test:watch`).
