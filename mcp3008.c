/* Jordan Ebel */

#include "mcp3008.h"

#define MCP3008_CONST_MAX_CHANNEL  0x7
#define MCP3008_CONST_XFR_LEN      3

static IO_SPA_SPI_PARAMS params = {0};

MCP3008_RC mcp3008_init(const char *bus)
{
    params.bus = bus;
    params.bits_per_word = 8;
    params.max_speed_hz = 100000; /* 100 KHz */

    if (io_spa_spi_init(&params))
    {
        return MCP3008_FAILURE;
    }
}

MCP3008_RC mcp3008_read_ch(uint8_t channel, bool differential, uint16_t *result)
{
    uint8_t tx[MCP3008_CONST_XFR_LEN];
    uint8_t rx[MCP3008_CONST_XFR_LEN];

    if (channel > MCP3008_CONST_MAX_CHANNEL)
    {
        return MCP3008_FAILURE;
    }

    tx[0] = 0x1;   // start bit
    tx[2] = 0x0;   // padding
    tx[1] = (~differential) << 7; // bit 7 is single / differential
    tx[1] |= (channel << 4);      // bits 4-6 are the channel

    if (io_spa_spi_add_transfer(&params, rx, tx, MCP3008_CONST_XFR_LEN, false, 0) != IO_SPA_OK ||
        io_spa_spi_send_transfers(&params) != IO_SPA_OK)
    {
        return MCP3008_FAILURE;
    }

    rx[1] &= 0x03;  // only bits 0-1 are data
    *result = ((uint16_t)rx[1] << 8) | rx[2];

    return MCP3008_OK;
}

MCP3008_RC mcp3008_close()
{
    io_spa_spi_close(&params);
    return MCP3008_OK;
}

