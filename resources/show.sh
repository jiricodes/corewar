for i in {0..4608}
do
echo "Cycle number $i"
./corewar -d $i champs/ex.cor champs/Survivor.cor
sleep 1
clear
done