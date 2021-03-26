# exit while meet error
set -e

# build xWindow
cd ExternalWindow/X11
gcc xWindow.c -lX11 -lpthread -o xWindow
cd ../..

#build HelloXXX
for file in ./Hello*
do
    echo -e "\e[44m $file building...\e[49m"
	if [ "$file" == "./HelloAzureIoT" ]; then
		echo "skip $file"
		continue
	fi
    cd $file
    cmake .
    make -j4
    cd ..
done

#build HostMonitor
echo -e "\e[44m ./HostMonitor building...\e[49m"
cd HostMonitor
cmake .
make -j4
