# DIFF_DIR=diffs
# SCRIPT=$(readlink "$0")
# echo "$0"

# echo "$SCRIPT"
SCRIPTPATH=$(dirname "$0")
echo "$SCRIPTPATH"
mkdir -p $SCRIPTPATH/diffs