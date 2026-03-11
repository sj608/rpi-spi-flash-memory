#ifndef SPIDEV_H
#define SPIDEV_H

#include <stdint.h>

int spi_transfer(int fd, uint8_t *tx_buf, uint8_t *rx_buf, uint32_t len);

#endif // SPIDEV_H
