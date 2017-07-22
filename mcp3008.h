/* Jordan Ebel */

#ifndef _MCP_3008_H
#define _MCP_3008_H

#include "io_spa.h"

typedef enum
{
    MCP3008_OK          = 0,
    MCP3008_FAILURE     = 1,
} MCP3008_RC;

MCP3008_RC mcp3008_init(const char *bus);
MCP3008_RC mcp3008_read_ch(uint8_t channel, bool differential, uint16_t *result);
MCP3008_RC mcp3008_close(void);

#endif /* _MCP_3008_H */

