#include "area008_13.h"

MATCH void func_801F3D18(void) {
    char* buffer;
    char* fmt;
    u8    value;

    buffer = (char*)g_UiFormatBuffer;
    Menu_DrawHeaderBar(200, 160, 34, 20, 1u);
    value = g_ScriptVars[3];
    fmt   = WORLD00_AREA008_D_801F2C10;
    TEXT_Format(buffer, fmt, value);
    UI_DrawAsciiString(0xD1, 0xA3, 0, buffer);
}
