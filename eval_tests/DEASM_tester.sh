if [ $# -eq 0 ]
  then
    echo "No File supplied"
	exit
fi
DEASM_TMP="deasm_tmp"
rm -rf $DEASM_TMP deasm_diff
mkdir $DEASM_TMP

cp $1 $DEASM_TMP
TMP=$(basename $1)
TMP_S="$DEASM_TMP/$TMP"
TMP_COR="${TMP_S%.s}.cor"

echo "Testing $TMP_S"
../asm $TMP_S
hexdump $TMP_COR > $DEASM_TMP/orig_dump
../deasm $TMP_COR
rm -f $TMP_COR
../asm $TMP_S
hexdump $TMP_COR > $DEASM_TMP/deasm_dump
DIFF=$(diff $DEASM_TMP/orig_dump $DEASM_TMP/deasm_dump > deasm_diff)
if [ "$DIFF" != "" ]
then
	echo "Diff found $TMP"
	echo $DIFF >> deasm_diff
else
	echo "ALL GUCCI"
fi