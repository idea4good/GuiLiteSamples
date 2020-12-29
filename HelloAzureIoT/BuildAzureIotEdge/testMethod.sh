iotHub=iotHubYou
device=edgeDeviceAmd64
module=gui-lite-module

url="https://$iotHub.azure-devices.net/twins/$device/modules/$module/methods?api-version=2018-06-30"

# Get sas token from Azure Cloud Shell
# az iot hub generate-sas-token -n iotHubYou --duration 360000
author="Authorization: SharedAccessSignature sr=iotHubYou.azure-devices.net&sig=JRkbf4FnLKDUjd88Id2a5%2F2VA99zUeh%2B7cc%2Fl1wytUY%3D&se=1609077650&skn=iothubowner"

curl -X POST \
  $url \
  -H "$author" \
  -H 'Content-Type: application/json' \
  -d '{
    "methodName": "Echo",
    "responseTimeoutInSeconds": 200,
    "payload": {
        "input1": "someInput",
        "input2": "anotherInput"
    }
}' > response.txt
