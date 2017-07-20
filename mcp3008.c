/* Jordan Ebel */

#include "mcp3008.h"

static IO_SPA_SPI_PARAMS params = {0};

MCP3008_RC mcp3008_init(const char *bus)
{
    params.bus = bus;
    params.bits_per_word = 8;
    params.max_speed_hz = 100000; /* 100 KHz */
    //params.clk_sample_falling_edge = false;
    //params.clk_idle_high = false;

    if (io_spa_spi_init(&params))
    {
        return MCP3008_FAILURE;
    }

    uint8_t tx[3];
    uint8_t rx[3];

    // start, single, CH0
    tx[0] = 0x1;
    tx[1] = 0x80;
    tx[2] = 0x0;

    io_spa_spi_add_transfer(&params, rx, tx, 3, false, 0);
    io_spa_spi_send_transfers(&params);

    printf("0x%x 0x%x 0x%x\n", rx[2], rx[1], rx[0]);

    return MCP3008_OK;
}

MCP3008_RC mcp3008_close()
{
    io_spa_spi_close(&params);
    return MCP3008_OK;
}

