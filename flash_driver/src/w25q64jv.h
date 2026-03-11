
#ifndef W25Q64JV_H
#define W25Q64JV_H

#include <stdint.h>
#ifndef TEST
#include <linux/spi/spidev.h>
int spi_transfer(int fd, uint8_t *tx_buf, uint8_t *rx_buf, uint32_t len);
#else
#include "mock_spidev.h"
#endif

// SPI instruction set
#define CMD_READ_MFG_DEV_ID  0x90
#define CMD_READ_DEV_ID      0xAB
#define CMD_READ_UNIQUE_ID   0x4B
#define CMD_WRITE_ENABLE     0x06
#define CMD_WRITE_DISABLE    0x04
#define CMD_READ_DATA        0x03
#define CMD_FAST_READ        0x0B
#define CMD_PAGE_PROGRAM     0x02
#define CMD_ERASE_4K         0x20
#define CMD_ERASE_32K        0x52
#define CMD_ERASE_64K        0xD8
#define CMD_ERASE_CHIP       0x60
#define CMD_READ_STATUS      0x05

// Keep legacy aliases
#define MFG_ID   CMD_READ_MFG_DEV_ID
#define DEV_ID   CMD_READ_DEV_ID
#define UU_ID    CMD_READ_UNIQUE_ID
#define WR_EN    CMD_WRITE_ENABLE
#define WR_DIS   CMD_WRITE_DISABLE
#define READ_D   CMD_READ_DATA
#define READ_FD  CMD_FAST_READ
#define PAGE_PGM CMD_PAGE_PROGRAM
#define ER_4K    CMD_ERASE_4K
#define ER_32K   CMD_ERASE_32K
#define ER_64K   CMD_ERASE_64K
#define ER_ALL   CMD_ERASE_CHIP
#define READ_STAT CMD_READ_STATUS

// Winbond W25Q64JV expected ID values
#define W25Q64JV_MANUFACTURER_ID  0xEF
#define W25Q64JV_DEVICE_ID        0x17

#define PAGE_SIZE    256
#define NUM_OF_PAGES 32768

typedef struct {
    uint16_t address;
    uint8_t  tx[PAGE_SIZE];
    uint8_t  rx[PAGE_SIZE];
} Page;

typedef struct {
    uint8_t manufacturer_id;
    uint8_t device_id;
} W25Q64JV_ID_t;

int w25q64jv_read_id(int fd, W25Q64JV_ID_t *id);
int w25q64jv_get_busy_bit(int fd);

#endif // W25Q64JV_H
