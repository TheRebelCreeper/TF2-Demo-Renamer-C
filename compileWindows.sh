#!/bin/bash

FLAGS="-Wall -Werror"

gcc *.c *.h ${FLAGS} -fcommon -o Demo_Renamer.exe
