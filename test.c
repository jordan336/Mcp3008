/* Jordan Ebel */

#include "mcp3008.h"

static const char *SPI_BUS="/dev/spidev0.0";

int main(int argv, char **argc)
{
    uint16_t value = 0x0;
    uint8_t channel = 0x7;

    if (mcp3008_init(SPI_BUS) != MCP3008_OK)
    {
        return 1;
    }

    mcp3008_read_ch(channel, false, &value);

    printf("channel: 0x%x value: 0x%x\n", channel, value);

    mcp3008_close();

    return 0;
}

