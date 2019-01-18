## How to build for Win MFC?
### Prerequisite:
- core.lib gui.lib should be in BuildMFC\BuildMFC\libs\x86(x64), ⚠️rebuild them if meet link error.
### Build
1. Open "HelloMCU\BuildMFC\HelloMCU.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloMCU`

## How to build for STM32F103 + ILI934x?
### Prerequisite:
- Install Keil uvsion 5.6 or above.
- GuiLite.lib should be in BuildSTM32F103-Keil\USER, ⚠️rebuild it if meet Linking error.
- Your hardware should be compatible with: [正点原子精英STM32F103ZET6开发板套装](https://item.taobao.com/item.htm?spm=a230r.1.14.20.17b441b9u49Ujg&id=582084489839&ns=1&abbucket=7#detail).
### Build
1. Open "HelloMCU\BuildSTM32F103-Keil\USER\HelloWave.uvprojx" with Keil uvsion.
2. Choose your Device type(Default: STM32F103ZE) from option for target.
3. Build HelloMCU.
4. Connect your hardware with your host PC, and flash/run HEX file on it.

## How to port on any MCU?
![HowToPorting](../doc/HowToPorting.png)
1. Open your MCU project(Keil/IAR), import GuiLite library - `GuiLite.lib`
2. Import all cpp files from `UIcode` in your project.
3. Encapsulate draw piexel driver in `main.c`
4. Link your LCD driver with GuiLite, and call UI entry function(e.g, startHelloWave)
5. Build & Run ⚠️rebuild `GuiLite.lib` if meet Linking error.