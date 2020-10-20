src=../../GuiLite
# exit while meet error
set -e
declare -i sum=0

#build HelloXXX
for file in ./Hello*
do
    echo -e "\e[44m $file sync up...\e[49m"
    cd $file
    cp $src/GuiLite.h UIcode/GuiLite.h
    cd ..
    sum+=1
done

#build HostMonitor
echo -e "\e[44m ./HostMonitor sync up...\e[49m"
cd HostMonitor
cp $src/GuiLite.h UIcode/include/GuiLite.h
sum+=1

echo $sum files updated.
