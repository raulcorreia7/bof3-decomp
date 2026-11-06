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
    if (D_801490BC.last_row >= 0) {
        do {
            D_801490CF[row & 0xFF] = count;
            flag                   = 1;
            do {
                switch (*cursor) {
                    case 0:
                        flag = 0;
                        /* fallthrough */
                    case 1:
                        count++;
                        break;
                    case 4:
                    case 5:
                    case 7:
                    case 8:
                    case 9:
                    case 18:
                    case 19:
                        cursor++;
                        break;
                }
                cursor++;
            } while (flag);
            row++;
        } while (D_801490BC.last_row >= (row & 0xFF));
    }

    rows                          = &D_801490BC.last_row;
    height                        = count * 0xD;
    g_MenuCurrentPanel->unk_0A    = 0xDC;
    g_MenuCurrentPanel->unk_0B    = height + 8 + *rows * 2;
    g_MenuCurrentPanel->unk_18    = 0x30;
    g_MenuCurrentPanel->pos.x.raw = ((g_MenuCurrentPanel->unk_0A >> 1) + 48) * 16;
    top                           = (g_MenuCurrentPanel->unk_0B >> 1) + 0x78;
    g_MenuCurrentPanel->pos.y.raw = (top - (height >> 1)) * 16;
    g_MenuCurrentPanel->unk_10    = 0;
    g_MenuCurrentPanel->unk_12    = 0;
    g_MenuCurrentPanel->unk_1A    = 0x78 - ((s32)height + *rows) / 2;
    g_MenuCurrentPanel->unk_14    = (g_MenuCurrentPanel->unk_0A * 0x10) / 5;
    g_MenuCurrentPanel->unk_16    = (g_MenuCurrentPanel->unk_0B * 0x10) / 5;
    base                          = 0x7C - ((s32)height + *rows) / 2;
    i                             = 0;
    if (*rows >= 0) {
        do {
            D_801490CF[i & 0xFF] = base + D_801490CF[i & 0xFF] * 0xD + (i & 0xFF) * 2;
            i++;
        } while (*rows >= (i & 0xFF));
    }
}
#else
INCLUDE_ASM(func_8015A554);
#endif
