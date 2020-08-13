if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
	exit
fi

## COLORS ##
GREEN="\033[0;32m"
RED="\033[0;31m"
EOC="\033[0m"

TEST_DIR=$1
rm -f deasm_diff

ASM_ORG=0
DEASM=0
ASM_NEW=0
DIFFS=0
for f in $TEST_DIR/*.s ; do
	./DEASM_tester.sh "$f"
	if [ $? -eq -2 ]; then
		ASM_ORG+=1
	elif [ $? -eq -3 ]; then
		DEASM+=1
	elif [ $? -eq -4 ]; then
		ASM_NEW+=1
	elif [ $? -eq -5 ]; then
		DIFFS+=1
	fi
done
echo "$GREEN Results $EOC"
echo "Original ASM fails: $ASM_ORG"
echo "DEASM fails: $DEASM"
echo "New ASM fails: $ASM_NEW"
echo "Differences: $DIFFS"