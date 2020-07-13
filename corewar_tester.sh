TEST_DIR="resources/champs"
rm $TEST_DIR/*.cor
rm diff_log
for f in $TEST_DIR/*.s ; do
	[ -f original_temp ] && rm original_temp
	[ -f our_temp ] && rm our_temp
	[[ -f "$f" ]] || continue
	STATUS=$(./resources/asm "$f")
	COR="${f%.s}.cor"
	if [ ! -f "$COR" ]
	then
		echo "Original ASM failed to create $COR\n$STATUS\n" >> diff_log
		echo "Fake" > original_temp
	else
		hexdump $COR > original_temp
	fi
	STATUS=$(./asm "$f")
	if [ ! -f "$COR" ]
	then
		echo "Our ASM failed to create $COR\n$STATUS\n" >> diff_log
		continue
	fi
	hexdump $COR > our_temp
	DIFF=$(diff original_temp our_temp)
	if [ "$DIFF" != "" ]
	then
		echo "Difference for $f /n" >> diff_log
		echo "$DIFF" >> diff_log
		echo "" >> diff_log
	fi
done
[ -f original_temp ] && rm original_temp
[ -f our_temp ] && rm our_temp
rm $TEST_DIR/*.cor