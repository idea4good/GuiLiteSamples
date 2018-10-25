echo off
set argC=0
for %%x in (%*) do Set /A argC+=1
if NOT "7" == "%argC%" (
    echo "Invalidate arguments"
    goto :eof
    )

set url=https://api.powerbi.com/beta/72f988bf-86f1-41af-91ab-2d7cd011db47/datasets/e0e71bab-d932-4bb8-bfcf-faec5aeadb60/rows?key=J9cQJK6rZyLYQ9NsuWV6RYyrgODk1Wu29tuzwMyBET62Xp1dxuJ5iR%%2B0ZtL6o0ams029nNUhWci%%2B%%2B4GzxXHyBQ%%3D%%3D
set date=
for /f "tokens=2-4 delims=/ "  %%a in ("%date%") do (set MM=%%a& set DD=%%b& set YYYY=%%c)
set datetime=%YYYY%-%MM%-%DD%T%time: =0%0+0800
set devie_info=%7-%USERNAME%

set raw_data=[{^
\"hr\" : %1,^
\"spo2\" :%2,^
\"resp\" :%3,^
\"sys\" : %4,^
\"dia\" : %5,^
\"mean\" : %6,^
\"time\" :\"%datetime%\",^
\"device_info\" :\"%devie_info%\",^
\"weight\" : 1^
}]

curl.exe --include --request POST --header "Content-Type: application/json" --data-binary^
 "%raw_data%" "%url%"