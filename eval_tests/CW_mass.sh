if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
	exit
fi
TEST_DIR=$1

FUCK="FAILED:\n"
for f in $TEST_DIR/*.cor ; do
	./cw_tester_log.sh "$f"
	if [ $? -eq -1 ]
	then
		FUCK+="$f\n"
	fi
done
