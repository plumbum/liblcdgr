#include "uart_proxy.h"

#include "utils.h"

static char _encHex(uint8_t v)
{
    if(v < 10)
        return (v+'0');
    else
        return (v+'A'-10);
}

void udbgPutHex(uint8_t a)
{
    udbgPutch(_encHex((a>>4) & 0x0F));
    udbgPutch(_encHex((a>>0) & 0x0F));
}

void udbgPutHex16(uint16_t a)
{
    udbgPutch(_encHex((a>>12) & 0x0F));
    udbgPutch(_encHex((a>>8) & 0x0F));
    udbgPutch(_encHex((a>>4) & 0x0F));
    udbgPutch(_encHex((a>>0) & 0x0F));
}

void udbgPutHex32(uint32_t a)
{
    udbgPutch(_encHex((a>>28) & 0x0F));
    udbgPutch(_encHex((a>>24) & 0x0F));
    udbgPutch(_encHex((a>>20) & 0x0F));
    udbgPutch(_encHex((a>>16) & 0x0F));
    udbgPutch(_encHex((a>>12) & 0x0F));
    udbgPutch(_encHex((a>>8) & 0x0F));
    udbgPutch(_encHex((a>>4) & 0x0F));
    udbgPutch(_encHex((a>>0) & 0x0F));
}

void udbgPutHexDump(const uint8_t* data, int len)
{
    while(len--)
        udbgPutHex(*data++);
}

void udbgPutUint(uint32_t val)
{
    char anum[16];
    ultoa(val, anum);
    udbgPuts(anum);
}

void udbgPutInt(int32_t val)
{
    char anum[16];
    ltoa(val, anum);
    udbgPuts(anum);
}


