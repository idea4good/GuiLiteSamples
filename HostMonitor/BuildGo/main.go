package main

// #cgo LDFLAGS: -L./libs/amd64 -L./libs/arm -lUIcode -lGuiLite -lpthread -ldl
// #include "main.h"
import "C"
import "os"
import "time"
import "fmt"

func main() {
    argc := C.int(len(os.Args))
    if(argc == 2){
        go C.Cmain(argc, C.CString(os.Args[1]))
    }else{
        go C.Cmain(argc, C.CString(""))
    }

    // Do something with Golang here:
    for {
        fmt.Println("Hello, I'm Golang")
        time.Sleep(time.Second * 1000)
    }
}
