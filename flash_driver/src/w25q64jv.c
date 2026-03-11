
#include "w25q64jv.h"

/*
 * Reads the Manufacturer ID and Device ID from the flash chip.
 *
 * Sends the READ_MFG_DEV_ID (0x90) instruction followed by a 24-bit address
 * of 0x000000. The device responds with the 1-byte Manufacturer ID (0xEF)
 * followed by the 1-byte Device ID (0x17) for the W25Q64JV.
 *
 * Returns 0 on success, negative errno on SPI failure.
 */
int w25q64jv_read_id(int fd, W25Q64JV_ID_t *id)
{
    uint8_t tx[6] = { CMD_READ_MFG_DEV_ID, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t rx[6] = { 0 };

    int ret = spi_transfer(fd, tx, rx, sizeof(tx));
    if (ret < 0)
        return ret;

    id->manufacturer_id = rx[4];
    id->device_id       = rx[5];

    return 0;
}

int w25q64jv_get_busy_bit(int fd)
{
    uint8_t tx[2] = {CMD_READ_STATUS, 0x00};
    uint8_t rx[2] = {0};
    uint8_t busy;
    int ret = spi_transfer(fd, tx, rx, sizeof(tx));
    if (ret < 0)
        return ret;
    busy = 0x1 & rx[1];
    
    return busy;
}
