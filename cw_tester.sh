rm -f cw_diff_log
for (( i=0; i<=20000; i+=100 ))
do
	./corewar resources/champs/examples/zork.cor resources/champs/Gagnant.cor resources/champs/jumper.cor -s -d $i > dump_us
	./resources/corewar -d $i resources/champs/examples/zork.cor resources/champs/Gagnant.cor resources/champs/jumper.cor > dump_orig
	DIFF=$(diff dump_orig dump_us)
	if [ "$DIFF" != "" ]
	then
		echo "DUMP DIFF $i /n" >> cw_diff_log
		echo "$DIFF" >> cw_diff_log
		echo "" >> cw_diff_log
	fi
done