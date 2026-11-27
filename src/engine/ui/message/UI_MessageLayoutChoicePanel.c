#include "engine/slus/slus.h"

/* counts the row bytes of the D_801490B0 stream into the
 * D_801490CF table and lays out the panel box from that count and
 * D_801490C6.
 */
/* func_8015A554 */
#ifdef NON_MATCHING
NON_MATCHING void UI_MessageLayoutChoicePanel(void) {
    u8* cursor;
    u8  flag;
    u8  count;
    u32 height;
    s32 row;
    s32 base;
    u8  i;

    count  = 0;
    cursor = D_801490B0;
    row    = 0;
    if (g_UIMessageWindow.last_row >= 0) {
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
        } while (g_UIMessageWindow.last_row >= (row & BYTE_MASK));
    }

    g_UIPanelCurrent->unk_0A        = 220;
    height                          = count * 13;
    g_UIPanelCurrent->unk_0B        = (s32)height + 8 + g_UIMessageWindow.last_row * 2;
    g_UIPanelCurrent->u.addr.unk_18 = 48;
    g_UIPanelCurrent->pos.vx        = ((g_UIPanelCurrent->unk_0A >> 1) + 48) * 16;
    g_UIPanelCurrent->pos.vy        = ((((u32)g_UIPanelCurrent->unk_0B >> 1) + 120) - (height >> 1)) * 16;
    g_UIPanelCurrent->u.addr.unk_1A = 120 - ((s32)height + g_UIMessageWindow.last_row) / 2;
    g_UIPanelCurrent->u.addr.unk_10 = 0;
    g_UIPanelCurrent->u.addr.unk_12 = 0;
    g_UIPanelCurrent->u.addr.unk_14 = (g_UIPanelCurrent->unk_0A * 16) / 5;
    g_UIPanelCurrent->u.addr.unk_16 = (g_UIPanelCurrent->unk_0B * 16) / 5;
    base                            = 124 - ((s32)height + g_UIMessageWindow.last_row) / 2;
    for (i = 0; g_UIMessageWindow.last_row >= i; i++) {
        D_801490CF[i] = base + D_801490CF[i] * 13 + i * 2;
    }
}
#else
INCLUDE_ASM(UI_MessageLayoutChoicePanel);
#endif
