# Lab 3.1 - File/Directory Monitor

## Description
 Program that logs all file creations, deletions, and renames under the directory named in its command-line argument. The program should monitor events in all of the subdirectories under the specified directory. To obtain a list of all of these subdirectories, you will need to make use of nftw(). When a new subdirectory is added under the tree or a directory is deleted, the set of monitored subdirectories should be updated accordingly.

## Instructions
To run the code just type

`make`

then type ´./monitor´ followd by the file to monito. For example:

´./monitor ´
