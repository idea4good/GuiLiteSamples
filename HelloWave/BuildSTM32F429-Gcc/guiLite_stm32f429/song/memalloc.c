//
// Created by song on 17-5-12.
//

#include "memalloc.h"

uint8_t *memPool = (uint8_t *) POOLSTART;
uint8_t *manangeTable = (uint8_t *) MANAGESTART;

void *mapply(uint16_t size) {
    uint16_t tablesize = (uint16_t) (TABLESIZE);
    uint16_t bsize = 0;
    if (size % BLOCKSIZE == 0) {
        bsize = (uint16_t) (size / BLOCKSIZE);
    } else {
        bsize = (uint16_t) (size / BLOCKSIZE + 1);
    }

    for (int i = 0; i < tablesize; ++i) {
        if (manangeTable[i] == 0) {
            uint8_t flag = 1;
            uint32_t tmp = 0;
            uint32_t j = 0;
            for (j = i; j < i + bsize; j++) {
                if (manangeTable[j] != 0) {
                    tmp = manangeTable[j];
                    flag = 0;
                    break;
                }
            }

            if (flag) {
                for (uint32_t k = 0; k < bsize; ++k) {
                    manangeTable[i + k] = (uint8_t) bsize;
                }
                return (void *) ((uint32_t) memPool + 64 * i);
            } else {
                i = j + tmp;
            }
        } else {
            i += manangeTable[i] - 1;
        }
    }

    return 0;

}

void mfree(void *p) {

    uint32_t pos = (uint32_t) (p - (uint32_t) memPool) / BLOCKSIZE;
    uint32_t size = manangeTable[pos];
    for (uint32_t i = pos; i < pos + size; ++i) {
        manangeTable[i] = 0;
    }

}

void pool_init() {

    for (uint32_t i = 0; i < MAXSIZE; ++i) {
        memPool[i] = 0;
    }
    for (uint32_t j = 0; j < TABLESIZE; ++j) {
        manangeTable[j] = 0;
    }
}

