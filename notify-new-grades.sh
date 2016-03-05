#!/bin/sh

## Caveat: it will only display the last line of the diff it creates so if
## there's a bigger change in your grades it will not find out. Also it does not
## tell you which module the new grade belonogs to – unless you can identify it
## by its’ course ID.

## An option to let it run repeadetly in a loop:
##
## while [ true ]; do ./notify_new_grades.sh ; sleep 60; done

OUTPUT="$(getgrades)"

if [[ $OUTPUT ]];
then
    echo "$OUTPUT" > ~/.config/getgrades/.latest-lookup.txt
else
    exit 1
fi

if [ -f ~/.config/getgrades/.last-lookup.txt ];
then
    DIFF=$(diff ~/.config/getgrades/.last-lookup.txt ~/.config/getgrades/.latest-lookup.txt)
    if [[ $DIFF ]];
    then
        # Maybe it should just say that a new grade appeared
        notify-send "$DIFF"
    fi
fi

mv ~/.config/getgrades/.latest-lookup.txt ~/.config/getgrades/.last-lookup.txt

exit 0
