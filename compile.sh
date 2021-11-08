#!/bin/bash

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 fun1.c fun2.c fun3.c shell.c shell.h -o shell
