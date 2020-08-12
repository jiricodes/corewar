## DIRECTORY TO RUN TEST ON ##
if [ $# -eq 0 ]
  then
    echo "No Folder supplied"
	exit
fi
TEST_DIR=$1

TEMP_DIR="deasm_temps"
rm -rf $TEMP_DIR
mkdir $TEMP_DIR
## DIFF_LOG
DIFF_LOG="deasm_diff_log"

## DEASM FILES
DEASM_COR="deasm_test.cor"
DEASM_S="deasm_test.s"

## COLORS ##
GREEN="\033[0;32m"
RED="\033[0;31m"
EOC="\033[0m"

## SCRIPT ##
rm $TEST_DIR/*.cor
rm $DIFF_LOG
./ASM_mass.sh $TEST_DIR
mv $TEST_DIR/*.cor $TEMP_DIR
for f in $TEMP_DIR/*.cor ; do
	echo "DEASM: $f"
	../deasm $f
done
# for f in $TEMP_DIR/*.s ; do
# 	[ -f original_temp ] && rm original_temp
# 	[ -f our_temp ] && rm our_temp
# 	[[ -f "$f" ]] || continue
# # 	STATUS=$(../asm "$f")
# 	COR="${f%.s}.cor"
# 	if [ ! -f "$COR" ]
# 	then
# 		echo "$RED ASM failed to create$EOC $COR\n$STATUS\n"
# 		continue
# 	else
# 		hexdump $COR > original_temp
# 	fi
# 	mv $COR $DEASM_COR
# 	../deasm $DEASM_COR
# 	rm -f $DEASM_COR
# 	STATUS=$(../asm "$DEASM_S")
# 	if [ ! -f $DEASM_COR ]
# 	then
# 		echo "$RED Our ASM failed to re-create$EOC $DEASM_COR\n$STATUS\n"
# 		continue
# 	fi
# 	hexdump $DEASM_COR > our_temp
# 	DIFF=$(diff original_temp our_temp)
# 	if [ "$DIFF" != "" ]
# 	then
# 		echo "Difference for $f /n" >> $DIFF_LOG
# 		echo "$DIFF" >> $DIFF_LOG
# 		echo "" >> $DIFF_LOG
# 		echo "$RED Diff in hexdump$EOC"
# 	fi
# 	echo ""
# done
# [ -f original_temp ] && rm original_temp
# [ -f our_temp ] && rm our_temp
# rm $TEST_DIR/*.cor