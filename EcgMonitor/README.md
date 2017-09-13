# GuiLite Sample
Welcome GuiLite Sample repo!

## How to build/run for Windows?
1. build sample.lib:
- Open "sample\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP(universal windows platform):
- Copy sample.lib you build to BuildWindows\sample_uwp_cpp\libs\
- Open "BuildWindows\GuiLite.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

## How to build/run for Linux?
1. build sample.lib:
- `cd sample`
- `cmake .`
- `make`

2. build/run Linux APP:
- Copy sample.lib you build to "BuildLinux\libs"
- `cd BuildLinux`
- `cmake .`
- `make`
- `chmod 777 *`
- `./display-x86 | ./sample_native shared-fb` for Linux 32 bits.
- `./display-x64 | ./sample_native shared-fb` for Linux 64 bits.

## How to build/run for Android?
1. build sample.lib:
- TBD

2. build Android APP:
- TBD