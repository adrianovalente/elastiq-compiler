<p align="center">
<img src="https://user-images.githubusercontent.com/8186616/30614558-44fa0604-9d62-11e7-8515-7e3314535a7c.png"/>
<h2 align="center">Hello <s>World</s> Elastiq.</h2>
</p>

> elastiq is a flexible and simple imperative programming language you can use to build great applications

[![Build Status](https://travis-ci.org/adrianovalente/elastiq-compiler.svg?branch=master)](https://travis-ci.org/adrianovalente/elastiq-compiler)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)]()
[![platforms](https://img.shields.io/badge/platform-linux--64%20%7C%20osx--64-orange.svg)]()

```
program hello

declare int a;
declare int b;

begin
  a := 1;
  b := 2;

  echo "1 + 2 equals ";
  echo (a + b);

end;
```

## What is this repo about?

This repo holds the `elastiq` compiler, as well as the language documentation.

To build the compiler, just the following command:

``` bash
make build
```

## Lexical Analyzer
In our first concept of the language, it will have:
  - identifiers (such as variable names);
  - numbers;
  - arithmetic operators;
  - logical operators;
  - control structures such as `if`s and `while`s

You can take an example of program written in *Elastiq* [here](./src/fixtures/hello.el).

The **[Lexical Analyzer](https://en.wikipedia.org/wiki/Lexical_analysis)** is responsible for parsing the source code and outputting `tokens`. To run the lexical analyzer, all you have to do is to `make` and then `./dist/lexical-analyzer PATH_TO_YOUR_FILE`:

![image](https://user-images.githubusercontent.com/8186616/31050550-7949ec4c-a624-11e7-8a92-0691c218714c.png)

## Contributing and Testing
Please feel free to open a pull request or open a issue. There are automated tests you can run with `make test` (or, if you are a js-fanboy like me, you can also `npm test` or `npm run test:watch`).
