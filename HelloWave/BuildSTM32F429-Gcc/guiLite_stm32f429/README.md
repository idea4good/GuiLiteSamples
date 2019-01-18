环境：

​	arm-none-eabi-gcc 8.2.1

​	cmake 3.5.1

编译方法：

​	

```bash
mkdir build
cd build
cmake ..
make -j8
cd main 
arm-none-eabi-objcopy -O binary App.elf App.bin 
```

