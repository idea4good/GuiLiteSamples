package main

// #cgo LDFLAGS: -L./libs/amd64 -L./libs/arm -lUIcode -lcore -lgui -lpthread -ldl
// #include "main.h"
import "C"
import "os"

func main() {
    argc := C.int(len(os.Args))
    if(argc == 2){
        C.Cmain(argc, C.CString(os.Args[1]))
    }else{
        C.Cmain(argc, C.CString(""))
    }
}
