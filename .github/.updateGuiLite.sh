# exit while meet error
set -e

#build HelloXXX
for file in ./Hello*
do
    echo -e "\e[44m $file sync up...\e[49m"
    cd $file
    cp ../../GuiLite/GuiLite.h UIcode/GuiLite.h
    cd ..
done

#build HostMonitor
echo -e "\e[44m ./HostMonitor sync up...\e[49m"
cd HostMonitor
cp ../../GuiLite/GuiLite.h UIcode/include/GuiLite.h
