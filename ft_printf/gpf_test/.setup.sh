##! /bin/bash

# sleep 3

# declare -i LINE1

# BASE="/Users/rvuorenl/hive/repos"
# CUR=$(pwd)
# SKRI="$CUR/printf_test.sh"

# # LINE1=$(sed -n "/^BASE/=" $SKRI)  //workiing
# LINE1=$(sed -n "/^BASE/=" $0)

# printf "\n line = $LINE1\n"
# printf "\n script = $SKRI\n"
# printf "\n cur = $CUR\n"

# read SRCPATH

# NBUFF="BASE=\"$SRCPATH\""
# printf "\n BUF = $NBUFF\n"

# # LIN1E=$(sed -n "BASE=" $SCRIPT)

# # sed -i "${LINE1}s/.*/$NBUFF/" $SCRIPT > $SCRIPT.tmp
# # sed -e "${LINE1}s|.*|$NBUFF|" $0
# sed -e "${LINE1}s|.*|$NBUFF|" $0 > $0.tmp
# chmod 744 $0.tmp
# mv $0.tmp $0



# # gives nr of lines
# # LINE1=$(sed -n '/# define BUFF_SIZE /=' $HEAD)
# # NEWBUFF="# define BUFF_SIZE $BUFF"

# # sed -e "${LINE1}s/.*/$NEWBUFF/" $HEAD > $HEAD.tmp
# # mv $HEAD.tmp $HEAD


# #               /Users/rvuorenl/hive/tests


VAR1="random"

printf "\n$VAR1\n"


VAR1="else"

printf "\n$VAR1\n"
