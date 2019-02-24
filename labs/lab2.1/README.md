# Lab 2.1

## Description
In this lab I created a Go program that acts as a server and a Go program that acts as a client 
of several clock servers at once, reading the times from each one and displaying the results in a table, 
akin to the wall of clocks seen in some business offices.

## Instructions
To run the program you must first run clock2.go followed by the port you will be assigning to that server and the time zone.
```
$ ./clock2 8010 US/Eastern
$ ./clock2 8020 Asia/Tokyo
$ ./clock2 8030 Europe/London
```
No that we have the servers up and running we can run the client program.
Run the program followed by the name of a city that corresponds to the time zone followed bye `=zones.localhost:` 
and the port number you want to access to.
```
$ ./clockWall NewYork=localhost:8010 Tokyo=localhost:8020 London=localhost:8030
start client
NewYork : 16:32:37
Tokyo : 06:32:38
London : 21:32:39
```
