#include "plc_compiler.h"
#include "plc_basic.h"

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
    FILE *f;
    if ( argc < 2)
    {
        printf("Usage: plc inputfile outputfile\n");
        return 1;
    }
    f = fopen(argv[1], "rb");
    if (!f)
    {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }
    char inBuffer[65535];
    int len = fread(inBuffer, 1, sizeof(inBuffer), f);
    fclose(f);
    if (len <= 0)
    {
        printf("Failed to read file: %s\n", argv[1]);
        return 1;
    }
    inBuffer[len] = '\0';
    uint8_t outBuffer[65535];
    PlcCompiler compiler(outBuffer, sizeof(outBuffer));
    if (!compiler.compile(inBuffer))
    {
        printf("Failed to compile at line %i\n", compiler.getErrorLine() );
        return 1;
    }
    if (argc < 3)
    {
        uint16_t pc = 0;
        while (pc < compiler.getBinarySize())
        {
            uint16_t len = plcCommandLen(outBuffer[pc]);
            for (uint16_t i=0; i<len; i++)
                printf("%02X ", outBuffer[pc + i]);
            printf("\n");
            if (outBuffer[pc] == PLC_END_STATE) printf("\n");
            pc += len;
        }
        printf("~\n");
    }
    else
    {
        f = fopen(argv[2], "wb");
        if (!f)
        {
            printf("Error opening file: %s\n", argv[2]);
            return 1;
        }
        fwrite(outBuffer, 1, compiler.getBinarySize(), f);
        fclose(f);
    }
    return 0;
}
