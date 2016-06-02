#!/bin/sh/
#this belongs in a makefile
gcc jsontest.c -I../include/jsmn -L../include/jsmn -ljsmn -o jsontest
