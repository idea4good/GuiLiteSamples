# exit while meet error
set -e

#test HelloXXX
for file in ./Hello*
do
    echo -e "\e[44m $file running...\e[49m"
	if [ "$file" == "./HelloAzureIoT" ]; then
		echo "skip $file"
		continue
	fi
    cd $file/BuildLinux
    timeout 5s ./.sync_build.sh &
    sleep 6s
    cd ../..
done

#test HostMonitor
echo -e "\e[44m ./HostMonitor running...\e[49m"
cd HostMonitor/BuildLinux
timeout 5s ./.sync_build.sh
