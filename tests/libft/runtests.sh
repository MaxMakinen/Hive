#!/bin/sh
gcc test_atoi.c ../libft.a -I ../
./a.out
gcc test_isalnum.c ../libft.a -I ../
./a.out
gcc test_itoa.c ../libft.a -I ../
./a.out
gcc test_split.c ../libft.a -I ../
./a.out
gcc test_strclr.c ../libft.a -I ../
./a.out
gcc test_strlen.c ../libft.a -I ../
./a.out
gcc test_strtrim.c ../libft.a -I ../
./a.out
gcc test_strjoin.c ../libft.a -I ../
./a.out
gcc test_strmap.c ../libft.a -I ../
./a.out
gcc test_strcmp.c ../libft.a -I ../
./a.out
rm a.out
