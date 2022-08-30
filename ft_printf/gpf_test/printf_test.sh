##! /bin/bash

TEST=$(pwd)
BASE="/Users/rvuorenl/hive/tests/printf"
RESULTS=$TEST/results
SRCFILES=$TEST/src 
declare -i LINE1;


# printf "'1' to setup path\n'2' to start test\n'3' to quit\n"
# printf ": "

# read INPUT
# if [ "$INPUT" = "1" ]
# then
#     setup_path

# elif [ "$INPUT" = "2" ]
# then
#     setup_test
# else
#     printf "Exit test\n"
#     exit
# if

printf "Str base $BASE\n"
printf "Str test $TEST\n"

while true; do
    printf "[1]\tSTART TEST\n[2]\tSETUP_PATH (current: $BASE)\n[3]\tQUIT\n"
    read -r -p ": " answer
    case $answer in
        [1]* )  printf "\nStarting test...\n"; break;;
        [2]* )  printf "\n\t--- SETUP PATH ---\n";
                LINE1=$(sed -n '/^BASE/=' $0);
                while :;
                do
                    printf "\nEnter the path to folder containing \"ft_printf\" (without trailing slash)\n";
                    printf "(CTRL + C to quit)\n"
                    # printf "Example: /Users/login_handle/evals\n"
                    printf "Example: /Users/rvuorenl/hive/repos\n: ";
                    read PATHSRC;
                    #           /Users/rvuorenl/hive/tests
                    if [ ! -d $PATHSRC ];
                    then
                        printf "\nERROR, directory \"$PATHSRC\" not found!\n";
                        # exit;
                    else
                        printf "\nPath OK, starting test!\n";
                        break;
                    fi;
                done
                sed -e "${LINE1}s|.*|BASE=\"${PATHSRC}\"|" $0 > $0.tmp;
                chmod 744 $0.tmp;
                mv $0.tmp $0;
                BASE=$PATHSRC
                printf "\nNEW BASE = $BASE\n";
                break;;
        [3]* ) printf "\nExit test\n"; exit;;
        * ) printf "\nInvalid answer, exit...\n"; exit;;
    esac
done

# while true; do
#     read -r -p "Do you wish to reboot the system? (Y/N): " answer
#     case $answer in
#         [Yy]* ) reboot; break;;
#         [Nn]* ) exit;;
#         * ) echo "Please answer Y or N.";;
#     esac
# done
printf "End base /test $BASE\t\n"
printf "End test $TEST\n"

while :
do 
    printf "\nEnter tested folder_name (clone_name)\n: "
    read EVAL 
    if [ ! -d $BASE/$EVAL ]
    then 
        printf "\nERROR, directory \"$BASE/$EVAL\" not found!\n"
    else 
        break ;
    fi 
done

# compiling
# add #include "$BASE/$EVAL/ft_printf.h" to all .c test files 

# change tests to have "diffed" line & testcase in same line ?
# would make diff > error_output easier, rather than diff > error & linenumber - 1 > error

if [ diff -s ] 