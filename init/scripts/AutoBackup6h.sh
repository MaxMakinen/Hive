#!/bin/bash

#Colours for printing text
RED='\033[0;31m'
PRPL='\033[0;35m'
GRN='\033[0;32m'
NORM='\033[0m'

#Script that checks if it has been more than 6 hours since the last commit
#to the git branch. If yes, then it adds, commits and pushes a generically
#commented backup.

#time since last commit in Unix time
last_commit=$(git show --name-only --format="%at" | head -1)

#current time in Unix time
now=$(date +%s)

#Adds 21600 seconds (6 hours) to last_commit
let check=$last_commit+21600

#Relative time since last commit
relative_time=$(git show --name-only --format="%ar" | head -1)


echo -e "${PRPL}Attempting automated backup.${NORM}"

#If check is less than now, more than 6 hours have passed since last commit.
if (($check < $now)); then
	git add .
	git commit -m "Auto backup."
	git push
	echo -e "${GRN}Auto update complete at:${NORM} $(date)"
else
	echo -e "${RED}Nothing to do. It has been less than 6h since last commit.${NORM}\nlast commit $relative_time."
fi
