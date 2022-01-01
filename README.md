# diyDB

[![Unit Tests](https://github.com/cmmeyer1800/diyDB/actions/workflows/test.yml/badge.svg)](https://github.com/cmmeyer1800/diyDB/actions/workflows/test.yml)

Homemade DB written in c++

The Idea behind this repo is to learn how to build a real world product. As such it will probably not be incredible in its execution but incredible in the learning that it imparts.

diyDB is an in memory database allowing it to be very fast. Alongside this it persists to disk by writing to a write ahead log with every key value addition.

The database currently supports any number of user named dictionaries which themselves support any number of string key value pairs.

To use diyDB download the source code and extract into a directory. Then from this Directory run:
```
make
```
Then,
```
make install
```
Finally, to open the shell run:
```
diyDB
```
From here:
```
~diyDB $ help
```
to see how to utilize the shell
