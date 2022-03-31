#!/bin/bash

#Script creates a cron job to run a script that is copied from the later half of his file.
#We copy so that the cron job script in the beginning isn't run more than once.
#Makes sure that the user has execution rights for the script.

#Colours for printing text
RED='\033[0;31m'
PRPL='\033[0;35m'
GRN='\033[0;32m'
NORM='\033[0m'

#Script to to automate backup in cron.
#If job is already scheduled in cron, skip to script. 

crontab -l > cron_temp
TASK=AutoBackup6h.sh
FIND=$(grep ${TASK} cron_temp | wc -l)
if (($FIND > 0)); then
	echo -e "${PRPL}Job already scheduled in cron.${NORM}"
else
	echo -e "${PRPL}Scheduling job into cron${NORM}"
	echo "#!/bin/bash" > ${TASK}
	echo "" >> ${TASK}
	echo "$(tail -n 34 $0)" >> ${TASK}
	chmod +x $TASK
	echo "0 23 * * * $(realpath ${TASK}) >/dev/null 2>&1" >> cron_temp
	crontab cron_temp
	echo -e "${GRN}Job succesfully scheduled.${NORM}"
fi
rm cron_temp

bash $TASK
exit

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
