```
  _ _ _                          
 | (_) |__ _ __  ___ _ _ ___ ___ 
 | | | '_ \ '  \/ _ \ '_(_-</ -_)
 |_|_|_.__/_|_|_\___/_| /__/\___|
```                           

# libmorse  [![Build Status](https://travis-ci.org/memoryhole/libmorse.svg?branch=master)](https://travis-ci.org/memoryhole/libmorse)

libmorse is a small c library for working with morse code.

##### Features

* no dynamic memory allocations (malloc)
* ascii to morse code
* morse code to ascii
* streaming morse code to ascii

## Building and Installing

### From GIT

```bash
./bootstrap
./configure
make
make install
```

### From Tarball

```bash
./configure
make
make install
```

## Run Tests

```bash
make check
```

## CLI

libmorse includes a [sample program](src/main.c) which excercises all library functions

```
$ morse -h
Usage: morse [OPTION] [STRING]
Converts standard input or argument to morse or text

  -t        morse to text
  -m        text to morse

```

## API

See see the [morse.h](src/morse.h) header for API documentation.

