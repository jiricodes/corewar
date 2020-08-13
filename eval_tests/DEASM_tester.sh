if [ $# -eq 0 ]
  then
    echo "No File supplied"
	exit -1
fi

## COLORS ##
GREEN="\033[0;32m"
RED="\033[0;31m"
EOC="\033[0m"

DEASM_TMP="deasm_tmp"
rm -rf $DEASM_TMP
mkdir $DEASM_TMP

cp $1 $DEASM_TMP
TMP=$(basename $1)
TMP_S="$DEASM_TMP/$TMP"
TMP_COR="${TMP_S%.s}.cor"

echo "\nTesting $TMP_S"
../asm "$TMP_S"
if [ ! -f "$TMP_COR" ]
then
	echo "$RED ASM failed to create $TMP_COR from original $EOC"
	exit -2
fi
hexdump $TMP_COR > $DEASM_TMP/orig_dump
rm -f $TMP_S
../deasm "$TMP_COR"
if [ ! -f "$TMP_S" ]
then
	echo "$RED DEASM failed to create $TMP_S $EOC"
	exit -3
fi
rm -f $TMP_COR
../asm $TMP_S
if [ ! -f "$TMP_COR" ]
then
	echo "$RED ASM failed to re-create $TMP_COR from DEASM's file $EOC"
	exit -4
fi
hexdump $TMP_COR > $DEASM_TMP/deasm_dump
DIFF=$(diff $DEASM_TMP/orig_dump $DEASM_TMP/deasm_dump)
if [ "$DIFF" != "" ]
then
	echo "$RED Diff found $EOC!"
	echo "$TMP DIFF:" >> deasm_diff
	echo $DIFF >> deasm_diff
	exit -5
else
	echo "$GREEN Done! $EOC"
fi