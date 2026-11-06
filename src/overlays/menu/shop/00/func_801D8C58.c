#include "shop_00.h"

/* nonmatching 79.49%: s16 x/y and u8 index/flag params, a 24-byte stack frame. Retail copies x to s5 after the first
 * call and sign-extends x in place in s1, loads the slot base after the s2 save, and adds 0x16 after the index product.
 * resume: a source form that gives x two homes (raw s5, extended s1) and delays the slot base load. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8C58(s16 x, s16 y, u8 index, u8 flag) {
    u8* slot;
    s16 tx;
    s32 value;
    /* FAKE: retail reserves 24 frame bytes (0x18..0x2F) no statement uses. */
    STACK_PADS(u8, 24);
    slot = &D_80144952;
    UI_DrawWindow(x + 3, y + 3, 101, 37, 0, slot[0]);
    slot += index * 0xA4;
    slot += 0x16;
    if (flag == 0) {
        tx = x + 0x2C;
    } else {
        tx = x + 0x26;
    }
    if (flag == 0) {
        UI_DrawText(tx, y + 7, 0, 0xFF, &D_801E5844);
    } else {
        UI_DrawText(tx, y + 7, 0, 0xFF, &D_801E5848);
    }
    if (flag == 0) {
        value = FIELD(s32, slot, 0x8);
    } else {
        value = Char_GetExpForLevel(index, (FIELD(u8, slot, 0x6) + 1) & BYTE_MASK);
    }
    if (value != -1) {
        sprintf((s8*)g_UiFormatBuffer, &D_801D0CF8, value);
    } else {
        sprintf((s8*)g_UiFormatBuffer, &D_801D0CFC);
    }
    UI_DrawAsciiString(x + 21, y + 26, 0, g_UiFormatBuffer);
    UI_DrawSpriteRun(x, y, D_801E5680, 1);
}
#else
/* First difference: s0 is saved early. */
INCLUDE_ASM(func_801D8C58);
#endif
