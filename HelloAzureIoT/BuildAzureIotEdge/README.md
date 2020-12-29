## How to build with VS Code
1. Right click module.json
2. Build and Push IoT module

## How to build with bash
```bash
./buildDocker.sh # build X86_64 image
./buildDocker.sh arm # build arm image
```

## How to deploy on ARM Linux
1. Install Azure IoT Edge on ARM Linux device
2. copy config-arm64-arm32.yaml to ARM Linux device
3. run
    ```bash
    iotedged -c config-arm64-arm32.yaml
    ```

## How to deploy on X86 Linux
This solution only works on VM(Azure IoT Edge on Ubuntu)
1. Install Azure IoT Edge on X86 Linux device
2. copy config-amd64.yaml to X86 Linux device
3. run
    ```bash
    iotedged -c config-amd64.yaml
    ```

## Test module method
1. Get 1 hour token by running: `az iot hub generate-sas-token -n iotHubYou --duration 3600` from Azure Cloud Shell
2. Update token in testMethod.sh
3. Run `testMethod.sh`, will get reponse in: response.txt
4. Check moudle on Azure IoT Edge device by running: `iotedge logs gui-lite-module`

## Test module method for Azure Portal
1. Open Azure portal -> IoT Hub -> IoT Edge -> <ins>YOUR DEVICE</ins> -> gui-lite-module -> Direct method
2. Fill "method name" with: {"your name": "method name"}
3. Fill "payload" with: {"your payload": "method payload"}
4. Click: Invoke Method

## Know issue:
1. Miss some folder
    ```bash
    sudo mkdir /var/lib/iotedge
    sudo mkdir /var/run/iotedge
    ```
2. Could not work on WSL 2
