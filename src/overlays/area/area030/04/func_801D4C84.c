#include "area030_04.h"

/* Advances the area panel's slide step (unk_09) and draws the fish
 * page for fish unk_3E: its g_FishBestCatch record byte, or id 0xFF and 0 while
 * that byte is 0, with the title sliding left in mode 0 (unk_08) and right
 * otherwise; at step 4 it makes unk_3C the current fish and advances unk_01. */
MATCH void func_801D4C84(void) {
    s32 mask;

    FISHING_STATE->step_timer_09++;
    func_801E0ED0(0, 0x4E);
    if (g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK,
                      g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E], 0);
    } else {
        func_801E1004(0xFF, 0, 0);
    }
    if (FISHING_STATE->counter_08 == 0) {
        if (g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
            func_801E0F4C(0x80 - FISHING_STATE->step_timer_09 * 0x30, 0x5B, FISHING_STATE->bounce_3C.half.key_3E);
        } else {
            func_801E0F4C(0x80 - FISHING_STATE->step_timer_09 * 0x30, 0x5B, 0xFF);
        }
    } else {
        if (g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
            func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + 0x80, 0x5B, FISHING_STATE->bounce_3C.half.key_3E);
        } else {
            func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + 0x80, 0x5B, 0xFF);
        }
    }
    func_801E1320(0xB0, 0x9C);
    func_801E162C(8, 0x94, 0xFFFF);
    func_801D7B64();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);
    if (FISHING_STATE->step_timer_09 == 4) {
        FISHING_STATE->bounce_3C.half.key_3E = FISHING_STATE->bounce_3C.half.unk_3C;
        FISHING_STATE->handler_index_01++;
    }
}
