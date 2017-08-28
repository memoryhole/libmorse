```
  _ _ _                          
 | (_) |__ _ __  ___ _ _ ___ ___ 
 | | | '_ \ '  \/ _ \ '_(_-</ -_)
 |_|_|_.__/_|_|_\___/_| /__/\___|
```                           

# libmorse  [![Build Status](https://travis-ci.org/memoryhole/libmorse.svg?branch=master)](https://travis-ci.org/memoryhole/libmorse)

libmorse is a small c library for working with morse code.

#### Features

* no dynamic memory allocations
* ascii to morse code
* morse code to ascii
* streaming morse code to ascii

## Usage

#### Single Header

The easiest way to use libmorse is to download the single-file header from the [latest release](https://github.com/memoryhole/libmorse/releases/latest) and include it in your application.


#### Shared Library

To build and install libmorse as a shared library you can download the [latest release](https://github.com/memoryhole/libmorse/releases/latest) tarball and follow the usual autotools dance:

```bash
./configure
make
make install
```

If you clone the GIT repository then you will need to run bootstrap first:

```bash
./bootstrap
./configure
make
make install
```


## CLI

libmorse includes a [sample program](src/main.c) which excercises all library functions

```bash
$ morse -h
Usage: morse [OPTION] [STRING]
Converts standard input or argument to morse or text

  -t        morse to text
  -m        text to morse

```

##### text to morse
```bash
$ echo libmorse | morse -m
.-.. .. -... -- --- .-. ... .
```

##### morse to text
```bash
$ echo ".-.. .. -... -- --- .-. ... ." | morse -t
LIBMORSE
```

## API

See see the [morse.h](src/morse.h) header for API documentation.

