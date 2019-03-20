# Lab 2.4 - Add syslog support to your Logger

## Description

A new initLoggerfunction will be added in order to add support for choosing between stdout or syslog logging.

int initLogger(char *logType)

You will handle the following log types:

- stdout or empty string for STDOUT logging
- syslog for SYSLOG logging

## Instructions

Type the following command:

`make`

Now you will have an executable file named testLogger, run it with the following command:

`./testLogger`
