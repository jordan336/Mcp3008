/* Jordan Ebel */

#include "mcp3008.h"

static const char *SPI_BUS="/dev/spidev0.0";

int main(int argv, char **argc)
{
    if (mcp3008_init(SPI_BUS) != MCP3008_OK)
    {
        return 1;
    }

    mcp3008_close();

    return 0;
}

