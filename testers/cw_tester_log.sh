# CW ABSOLUTE PATH
CW_PATH="~/Hive/corewar"
RESOURCES_PATH="~/Hive/corewar/resources"

#Pathing
DIFF_DIR=diffs
CURRENT_PATH=$(dirname "$0")
TMP=$CURRENT_PATH/DIFF_DIR
mkdir -p $TMP

# Save files
US=$TMP/dump_us
ORIG=$TMP/dump_orig
PARS=$TMP/dump_orig_parsed
LOG=$TMP/cw_diff_log
rm -f $US $ORIG $PARS $LOG

echo "$CW_PATH/corewar"
echo "\nOur CW"
time $CW_PATH/corewar $1 $2 $3 $4 -s -log 1 > $US
# echo "\nOriginal CW"
# time $RESOURCES_PATH/corewar -v 6 $1 $2 $3 $4 > $ORIG
# ./$CURRENT_PATH/parse_orig.py > $PARS
# DIFF=$(diff $PARS $US)
# echo ""
# if [ "$DIFF" != "" ]
# then
# 	echo "$DIFF" >> $LOG
# 	echo "\033[31mDifference found and saved in $LOG\033[0m"
# fi
# echo "\033[32mDone\033[0m"