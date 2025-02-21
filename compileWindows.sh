#!/bin/bash

FLAGS="-Wall -Werror -I./pcre2/build -L./pcre2/build -lpcre2-8"

gcc *.c *.h ${FLAGS} -o Demo_Renamer.exe
