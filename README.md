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

## Usage

### Single Header
The easiest way to use libmorse is to download the single-file header from the [latest release](https://github.com/memoryhole/libmorse/releases) and include it in your application.


### Shared Library
To build and install libmorse as a shared library you can download the [latest release](https://github.com/memoryhole/libmorse/releases) tarball follow the usual autotools dance:


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

