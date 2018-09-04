::echo off
set url=https://api.powerbi.com/beta/72f988bf-86f1-41af-91ab-2d7cd011db47/datasets/ca74872f-2a7e-41ba-8496-58642517cf55/rows?key=zF119dK%%2Bxgdq8BOJcECGoW7V0jJ5NHpVgQlNQiGrUSAHh0MLpu1NJN0P%%2FdNQUzOtZHsMR46pq%%2Fymd9SBA86%%2FjA%%3D%%3D
set date=
for /f "tokens=2-4 delims=/ "  %%a in ("%date%") do (set MM=%%a& set DD=%%b& set YYYY=%%c)
set datetime=%YYYY%-%MM%-%DD%T%time%
set devie_info=Windows-MFC-%USERNAME%

set raw_data=[{^
\"HR\" : %1,^
\"SPO2\" :%2,^
\"RESP\" :%3,^
\"SYS\" : %4,^
\"DIA\" : %5,^
\"MEAN\" : %6,^
\"Time\" :\"%datetime%\",^
\"Device info\" :\"%devie_info%\",^
\"Weight\" : 1^
}]

curl --include --request POST --header "Content-Type: application/json" --data-binary^
 "%raw_data%" "%url%"