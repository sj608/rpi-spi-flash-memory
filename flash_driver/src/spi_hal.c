
#ifndef TEST

#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdint.h>

int spi_transfer(int fd, uint8_t *tx_buf, uint8_t *rx_buf, uint32_t len)
{
    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf       = (unsigned long)tx_buf;
    tr.rx_buf       = (unsigned long)rx_buf;
    tr.len          = len;
    tr.bits_per_word = 8;

    return ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
}

#endif // TEST
