rm -f cw_diff_log dump_orig dump_us dump_orig_parsed
./corewar $1 $2 $3 $4 -s -log 1 > dump_us
./resources/corewar -v 6 $1 $2 $3 $4 > dump_orig
python3.7 parse_orig.py > dump_orig_parsed
DIFF=$(diff dump_orig_parsed dump_us)
if [ "$DIFF" != "" ]
then
	echo "$DIFF" >> cw_diff_log
	echo "Difference found and saved in cw_diff_log"
fi
echo "Done"