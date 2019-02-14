# Lab #2

## Description
This lab is about static linking one file to another using C. It consists of strlib.c file which contains the following functions:
```
int strlen(char *str)
char* stradd(char *origin, char *addition)
int strfind(char *origin, char *substr)
```
And a str-main.c file that contains our main function where we will be executing the functions of strlib.c.

## Instructions
To compile this program you need to download both files and insert the following commands on the Terminal.
```
gcc -c str-main.c -o str-main.o
gcc -c strlib.c -o strlib.o
gcc str-main.o strlib.o -o str-final.o
```
This will generate our outpufile called str-final.o.
To run the code type ./str-final.o followed by three string parameter like the example below:
```
./str-final.o originalVeryLongString Addition Add
```
