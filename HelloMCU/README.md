## How to build for Win MFC?
### Prerequisite:
- core.lib gui.lib should be in BuildMFC\BuildMFC\libs\x86(x64), ⚠️rebuild them if meet link error.
### Build
- Open "HelloMCU\BuildMFC\HelloMCU.sln" by Visual studio 2017
- Click `F5` to build/run `HelloMCU`

## How to build for STM32F103ZET6 + ILI934x?
### Prerequisite:
- Install Keil uvsion 5.6 or above.
- GuiLite.lib should be in BuildMCU\USER, ⚠️rebuild it if meet Linking error.
- Your hardware should be compatible with: [正点原子精英STM32F103ZET6开发板套装](https://item.taobao.com/item.htm?spm=a230r.1.14.20.17b441b9u49Ujg&id=582084489839&ns=1&abbucket=7#detail).
### Build
- Open "HelloMCU\BuildMCU\USER\BuildMCU.uvprojx" with Keil uvsion.
- Choose your Device type(Default: STM32F103ZE) from option for target.
- Build HelloMCU.
- Connect your hardware with your host PC, and flash/run HEX file on it.