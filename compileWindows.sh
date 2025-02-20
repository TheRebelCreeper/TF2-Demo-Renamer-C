#!/bin/bash

FLAGS="-Wall -Werror -g"

gcc *.c *.h ${FLAGS} -fcommon -o Demo_Renamer.exe
