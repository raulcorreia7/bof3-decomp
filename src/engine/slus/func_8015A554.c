#include "engine/slus/slus.h"

/* counts the row bytes of the D_801490B0 stream into the
 * D_801490CF table and lays out the panel box from that count and
 * D_801490C6.
 */
/* 50.39%; regalloc: retail keeps count/cursor in t0/a0; this draft uses a3/t0. */
#ifdef NON_MATCHING
NON_MATCHING void func_8015A554(void) {
    u8* cursor;
    s8* rows;
    u8  flag;
    u8  count;
    u32 height;
    s32 row;
    s32 top;
    s32 base;
    s32 i;

    count  = 0;
    cursor = D_801490B0;
    row    = 0;
    if (g_MessageWindow.last_row >= 0) {
        do {
            D_801490CF[row & BYTE_MASK] = count;
            flag                        = 1;
            do {
                switch (*cursor) {
                    case STRING_END:
                        flag = 0;
                        /* fallthrough */
                    case STRING_NEWLINE:
                        count++;
                        break;
                    case STRING_INSERT:
                    case STRING_COLOR:
                    case STRING_VAR:
                    case STRING_LINK:
                    case STRING_NOP:
                    case STRING_SKIP:
                    case STRING_SKIP_ALT:
                        cursor++;
                        break;
                }
                cursor++;
            } while (flag);
            row++;
        } while (g_MessageWindow.last_row >= (row & BYTE_MASK));
    }

    rows                              = &g_MessageWindow.last_row;
    height                            = count * 0xD;
    g_MenuCurrentPanel->unk_0A        = 0xDC;
    g_MenuCurrentPanel->unk_0B        = height + 8 + *rows * 2;
    g_MenuCurrentPanel->u.addr.unk_18 = 0x30;
    g_MenuCurrentPanel->pos.x         = ((g_MenuCurrentPanel->unk_0A >> 1) + 48) * 16;
    top                               = (g_MenuCurrentPanel->unk_0B >> 1) + 0x78;
    g_MenuCurrentPanel->pos.y         = (top - (height >> 1)) * 16;
    g_MenuCurrentPanel->u.addr.unk_10 = 0;
    g_MenuCurrentPanel->u.addr.unk_12 = 0;
    g_MenuCurrentPanel->u.addr.unk_1A = 0x78 - ((s32)height + *rows) / 2;
    g_MenuCurrentPanel->u.addr.unk_14 = (g_MenuCurrentPanel->unk_0A * 0x10) / 5;
    g_MenuCurrentPanel->u.addr.unk_16 = (g_MenuCurrentPanel->unk_0B * 0x10) / 5;
    base                              = 0x7C - ((s32)height + *rows) / 2;
    i                                 = 0;
    if (*rows >= 0) {
        do {
            D_801490CF[i & BYTE_MASK] = base + D_801490CF[i & BYTE_MASK] * 0xD + (i & BYTE_MASK) * 2;
            i++;
        } while (*rows >= (i & BYTE_MASK));
    }
}
#else
INCLUDE_ASM(func_8015A554);
#endif
