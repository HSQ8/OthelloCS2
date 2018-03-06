#!/bin/bash     
rm -rf out.dat
for run in {1..4}
do
	./testgame Cortana SimplePlayer >> out.dat
done
echo " " >> out.dat
echo "Black Victories: " >> out.dat
tr ' ' '\n' < out.dat | grep "BLACK_V" | wc -l >> out.dat

VICTORY="$(tr ' ' '\n' < out.dat | grep "BLACK_V" | wc -l)"
TOTAL="$(tr ' ' '\n' < out.dat | grep "#-#-#" | wc -l)"

echo "Black victories / total: " "${VICTORY}" / "${TOTAL}"
