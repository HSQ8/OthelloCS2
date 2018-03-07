#!/bin/bash
# edit the line on the bottom ./testgame ____ ___ to set player configuration, edit the for loop to set how many times we run the experiment
rm -rf out.dat

for run in {1..5}
do
	./testgame SimplePlayer Cortana 300000 >> out.dat
done
echo " " >> out.dat

VICTORY="$(tr ' ' '\n' < out.dat | grep "BLACK_V" | wc -l)"
TOTAL="$(tr ' ' '\n' < out.dat | grep "#-#-#" | wc -l)"

echo " " >> out.dat
echo " " >> out.dat
echo "BlackVictory: "$VICTORY >> out.dat
echo "Total Trials: "$TOTAL >> out.dat

echo "Black victories / total: " "${VICTORY}" / "${TOTAL}"
