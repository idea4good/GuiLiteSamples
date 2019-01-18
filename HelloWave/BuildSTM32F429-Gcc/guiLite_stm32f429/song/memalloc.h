//
// Created by song on 17-5-12.
//

#include "stdint.h"

#ifndef MOS_MEMALLOC_H
#define MOS_MEMALLOC_H

#define POOLSTART   0xD0025800 //前面的空间用作lcd显存
#define MANAGESTART 0xD0725800 //内存管理块的首地址
#define MAXSIZE     0x700000  //用来管理7M的空间
#define BLOCKSIZE 64
#define TABLESIZE MAXSIZE/BLOCKSIZE

void *mapply(uint16_t size);

void mfree(void *p);

void pool_init();

#endif //MOS_MEMALLOC_H
