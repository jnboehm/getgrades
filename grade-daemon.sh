#!/bin/sh

if [[ $1 ]];
then
    SLEEP_TIME=$1
else
    SLEEP_TIME=180
fi

while [ true ];
do
    notify-new-grades.sh > /dev/null
    sleep $SLEEP_TIME
done
