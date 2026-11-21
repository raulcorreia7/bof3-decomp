#include "engine/slus/slus.h"

/* Draws the text described by a control stream and returns the byte after its terminator. */
MATCH u8* UI_TextDrawAt(s32 x, s32 y, u8* text) {
    u8* saved;
    u8  flags;
    u8  count;
    u8  color;
    s32 column;
    u8  code;
    u8* p;
    s32 left;
    s32 row;

    p      = text;
    left   = x;
    row    = y;
    flags  = 0;
    saved  = NULL;
    count  = 0;
    color  = 0;
    column = left;
    for (;;) {
        switch (*p) {
            case STRING_END:
                if (flags & 0x1) {
                    flags &= 0xFE;
                    p = saved++;
                    break;
                }
                flags &= 0xFE;
                return p + 1;
            case STRING_NEWLINE:
                column = left;
                row += 13;
                break;
            case STRING_VAR:
                flags |= 1;
                p++;
                saved = p;
                count = 32;
                p     = (u8*)&D_801490D7 + (*p << 5);
                break;
            case STRING_GOTO:
                flags |= 1;
                saved = p;
                p     = (u8*)&g_Game + 0x73;
                count = 5;
                break;
            case STRING_INSERT:
                flags |= 1;
                x = left;
                p++;
                saved = p;
                count = 5;
                p     = (u8*)&D_80144967 + *p * PARTY_RECORD_STRIDE;
                break;
            case STRING_COLOR:
                p++;
                color = *p;
                break;
            case STRING_NOCOLOR:
                color = 0;
                break;
            case STRING_LINK:
                flags |= 1;
                p++;
                saved = p;
                count = 16;
                {
                    u8   index;
                    u16* offsets;

                    index   = *p;
                    p       = (u8*)(D_80010004 + SLUS_LOAD_ADDRESS);
                    offsets = (u16*)((index << 1) + (u32)p);
                    p += offsets[0];
                }
                break;
            case STRING_NOP:
                break;
            default:
                UI_TextDraw(column, row, color, 1, p);
                code = *p;
                if ((code == STRING_SKIP) || (code == STRING_SKIP_ALT) || (code == STRING_NUM)) {
                    p++;
                }
                if (flags & 0x1) {
                    if (--count == 0) {
                        p = saved;
                        flags &= 0xFE;
                    }
                }
                column += 8;
                break;
        }
        p++;
    }
}
