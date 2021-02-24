if [ "$#" -ne 6 ]; then
    echo "Invalid arguments"
    exit -1
fi

url="https://api.powerbi.com/beta/72f988bf-86f1-41af-91ab-2d7cd011db47/datasets/e0e71bab-d932-4bb8-bfcf-faec5aeadb60/rows?key=J9cQJK6rZyLYQ9NsuWV6RYyrgODk1Wu29tuzwMyBET62Xp1dxuJ5iR%2B0ZtL6o0ams029nNUhWci%2B%2B4GzxXHyBQ%3D%3D"
time=`date +%Y-%m-%dT%H:%M:%S.000+0800`
device_info=`uname -s -n -m`"-Go"
curl --include --request POST --header "Content-Type: application/json" --data-binary "[{
\"hr\" : $1,
\"spo2\" :$2,
\"resp\" :$3,
\"sys\" : $4,
\"dia\" : $5,
\"mean\" : $6,
\"time\" :\"$time\",
\"device_info\" :\"$device_info\",
\"weight\" : 1
}]" $url
