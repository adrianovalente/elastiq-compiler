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
