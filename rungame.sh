rm -rf out.dat
for run in {1..10}
do
	./testgame Cortana SimplePlayer >> out.dat
done

tr ' ' '\n' < out.dat | grep "BLACK_V" | wc -l >> out.dat