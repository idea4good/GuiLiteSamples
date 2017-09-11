# NoodleLinuxSample
## Welcome to the Noodle Linux Sample Repo!

## Quickly run
###Show UI in display APP:
1. `cd NoodleLinuxSample\prebuild\x86` or `cd NoodleLinuxSample\prebuild\x64` 
2. `chmod 777 *`
3. `./display | ./sample_native shared-fb` for Linux 32 bits.

###Save UI as bitmap:
1. `cd NoodleLinuxSample\prebuild\x86` or `cd NoodleLinuxSample\prebuild\x64` 
2. `chmod 777 *`
3. `./sample_native 1 8`
4. input `sslp`, and open Display.html with internet browser.

###Run on embeded Linux device:
Coming soon...

## How to build/run with display APP?
1. `cd NoodleLinuxSample`
2. `cmake .`
3. `make`
4. `chmod 777 *`
5. `./display-x86 | ./sample_native shared-fb` for Linux 32 bits.
6. `./display-x64 | ./sample_native shared-fb` for Linux 64 bits.

## How to build/run without display APP?
1. `cd NoodleLinuxSample`
2. `cmake .`
3. `make`
4. `chmod 777 *`
5. `./sample_native 1 8`
6. input 'sslp', and open Display.html with internet browser.

## How to build/run it on embeded Linux device with different LCD size.
Coming soon...

## Note:
1. 'display-x86/64' should be in same directory with sample_native, it just virtual display device, and has nothing with NoodlUI.
2. display-x86/64 APP depend on QT, you can type: `sudo apt-get install qtcreator` to install it.

3. You can find source code in "display.src". You can do some research for the code -- it's very simple code. This will help you move this sample to other device.