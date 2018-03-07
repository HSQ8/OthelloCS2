#!/bin/bash
# edit the line on the bottom ./testgame ____ ___ to set player configuration, edit the for loop to set how many times we run the experiment
TRIALS=5  # this number is half of all total trials
PLAYER1=Cortana
PLAYER2=SimplePlayer
TIME=300000
TEMPFILE1=out.dat1
TEMPFILE2=out.dat2


rm -rf $TEMPFILE1

for ((i=0; i<TRIALS; i++));
do
	./testgame $PLAYER1 $PLAYER2 $TIME >> $TEMPFILE1
done


VICTORY1="$(tr ' ' '\n' < $TEMPFILE1 | grep "BLACK_V" | wc -l)"
TOTAL1="$(tr ' ' '\n' < $TEMPFILE1 | grep "#-#-#" | wc -l)"

echo " " >> $TEMPFILE1
echo " " >> $TEMPFILE1
echo "BlackVictory: "$VICTORY1 >> $TEMPFILE1
echo "Total Trials: "$TOTAL1 >> $TEMPFILE1


rm -rf $TEMPFILE2

for ((i=0; i<TRIALS; i++));
do
	./testgame $PLAYER2 $PLAYER1 $TIME >> $TEMPFILE2
done

VICTORY2="$(tr ' ' '\n' < $TEMPFILE2 | grep "BLACK_V" | wc -l)"
TOTAL2="$(tr ' ' '\n' < $TEMPFILE2 | grep "#-#-#" | wc -l)"

echo " " >> $TEMPFILE2
echo " " >> $TEMPFILE2
echo "BlackVictory: "$VICTORY2 >> $TEMPFILE2
echo "Total Trials: "$TOTAL2 >> $TEMPFILE2

let TOTALVICTORY=$VICTORY1+$TOTAL2-$VICTORY2
let TOTALTRIALS=$TRIALS+$TRIALS

cat $TEMPFILE2 >> $TEMPFILE1
rm -rf $TEMPFILE2

echo "$PLAYER1 victories / total: " "${TOTALVICTORY}" / "${TOTALTRIALS}"
