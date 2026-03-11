
#ifndef W25Q64JV_H
#define W25Q64JV_H

#include <stdint.h>
#ifndef TEST
#include <linux/spi/spidev.h>
#else
#include "mock_spidev.h"
#endif

// Instructions
#define MFG_ID 0x90
#define DEV_ID 0xAB
#define UU_ID  0x4B
#define WR_EN  0x06
#define WR_DIS 0x04
#define READ_D 0x03
#define READ_FD 0x0B
#define PAGE_PGM 0x02
#define ER_4K 0x20
#define ER_32K 0x52
#define ER_64K 0xD8
#define ER_ALL 0x60

#define PAGE_SIZE 256
#define NUM_OF_PAGES 32768

typedef struct{
    uint16_t address;
    uint8_t tx[PAGE_SIZE];
    uint8_t rx[PAGE_SIZE];
}Page;

#endif // W25Q64JV_H
