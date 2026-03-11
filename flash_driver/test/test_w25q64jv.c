
#include "unity.h"
#include "mock_spidev.h"
#include "w25q64jv.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/* --- w25q64jv_read_id ---------------------------------------------------- */

static int spi_transfer_inject_ids(int fd, uint8_t *tx_buf, uint8_t *rx_buf,
                                   uint32_t len, int num_calls)
{
    (void)fd; (void)num_calls;

    static const uint8_t expected_tx[] = {
        CMD_READ_MFG_DEV_ID, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    TEST_ASSERT_EQUAL_UINT32(6, len);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_tx, tx_buf, 6);

    rx_buf[4] = W25Q64JV_MANUFACTURER_ID;
    rx_buf[5] = W25Q64JV_DEVICE_ID;

    return (int)len;
}

void test_read_id_returns_manufacturer_and_device_id(void)
{
    W25Q64JV_ID_t id = { 0 };

    spi_transfer_Stub(spi_transfer_inject_ids);

    int ret = w25q64jv_read_id(3, &id);

    TEST_ASSERT_EQUAL(0, ret);
    TEST_ASSERT_EQUAL_HEX8(W25Q64JV_MANUFACTURER_ID, id.manufacturer_id);
    TEST_ASSERT_EQUAL_HEX8(W25Q64JV_DEVICE_ID,       id.device_id);
}

void test_read_id_returns_error_on_spi_failure(void)
{
    W25Q64JV_ID_t id = { 0 };

    spi_transfer_IgnoreAndReturn(-1);

    int ret = w25q64jv_read_id(3, &id);

    TEST_ASSERT_EQUAL(-1, ret);
}

/* --- w25q64jv_get_busy_bit ------------------------------------------------ */

static int spi_transfer_inject_sr1(uint8_t sr1_value,
                                   int fd, uint8_t *tx_buf, uint8_t *rx_buf,
                                   uint32_t len, int num_calls)
{
    (void)fd; (void)num_calls;

    static const uint8_t expected_tx[] = { CMD_READ_STATUS, 0x00 };

    TEST_ASSERT_EQUAL_UINT32(2, len);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_tx, tx_buf, 2);

    rx_buf[1] = sr1_value;

    return (int)len;
}

static int spi_transfer_sr1_not_busy(int fd, uint8_t *tx_buf, uint8_t *rx_buf,
                                     uint32_t len, int num_calls)
{
    return spi_transfer_inject_sr1(0x00, fd, tx_buf, rx_buf, len, num_calls);
}

static int spi_transfer_sr1_busy(int fd, uint8_t *tx_buf, uint8_t *rx_buf,
                                 uint32_t len, int num_calls)
{
    /* SR1 = 0x03: BUSY bit set, WEL bit set — only BUSY (bit 0) matters */
    return spi_transfer_inject_sr1(0x03, fd, tx_buf, rx_buf, len, num_calls);
}

void test_get_busy_bit_returns_0_when_not_busy(void)
{
    spi_transfer_Stub(spi_transfer_sr1_not_busy);

    int ret = w25q64jv_get_busy_bit(3);

    TEST_ASSERT_EQUAL(0, ret);
}

void test_get_busy_bit_returns_1_when_busy(void)
{
    spi_transfer_Stub(spi_transfer_sr1_busy);

    int ret = w25q64jv_get_busy_bit(3);

    TEST_ASSERT_EQUAL(1, ret);
}

void test_get_busy_bit_returns_error_on_spi_failure(void)
{
    spi_transfer_IgnoreAndReturn(-1);

    int ret = w25q64jv_get_busy_bit(3);

    TEST_ASSERT_EQUAL(-1, ret);
}

