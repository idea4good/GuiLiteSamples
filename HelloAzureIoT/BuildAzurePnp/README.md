You can choose DPS or Connection string method for IoT Hub connection
## Prerequisite for DPS
1. Create IoT Hub
2. Create IoT Device Provision Service(DPS), and link to IoT Hub
3. Create individual enrollment
4. Update main.c::s_Configuration with ID Scope/REGISTRATION ID/key you created above

Note: **No capital** letter for DPS enrollment ID/name.

## Prerequisite for Connection string
1. Create IoT Hub
2. Create IoT Device in IoT Hub
3. Enable macro main.c::USING_CONNECTION_STRING
4. Update main.c::s_ConnectionString with `connection string` of IoT Device

## How to build/run on Linux-X86
```bash
cmake . && make
./pnpGuiLite
```

## How to update libs
```bash
git clone https://github.com/Azure/azure-iot-sdk-c.git
cd azure-iot-sdk-c
git submodule update --init
cmake -Duse_prov_client=ON -Dhsm_type_symm_key=ON -Drun_e2e_tests=OFF .
make
```
Copy all libs files to libs folder.

## Send message from Azure IoT Hub
1. Open Azure portal -> IoT Hub -> IoT Device -> Direct method
2. Fill "method name" with: YOU_METHOD_NAME
3. Fill "payload" with: 123/"YOUR_PAYLOAD_STRING" (double quotes should be included)
4. Click: Invoke Method

## Send message from Azure IoT Explorer
1. Open Azure IoT Explorer -> iotHub -> Devices -> <ins>YOUR DEVICE</ins> -> IoT Plug and Play components -> DEFAULT_COMPONENT -> Commands
2. Click: Send command
