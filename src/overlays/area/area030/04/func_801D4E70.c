#include "area030_04.h"

/* Draws one panel row: counts the work timer down, draws the entry for the current key at the
 * offset set by the direction flag, then the frame, and resets the state to 8 once the timer reaches zero. */
MATCH void func_801D4E70(void) {
    FishingState* work;
    s16           key;
    s16           key_a;
    s16           key_b;
    s32           index;
    s32           mask;
    u8            fish;

    FISHING_STATE->step_timer_09--;
    func_801E0ED0(0, 0x4E);
    key   = FISHING_STATE->bounce_3C.half.key_3E;
    fish  = g_FishBestCatch[key];
    index = key & 0xFF;
    if (fish == 0) {
        index = 0xFF;
        fish  = 0;
    }
    func_801E1004(index, fish, 0);
    work = FISHING_STATE;
    if (work->counter_08 == 0) {
        key_a = work->bounce_3C.half.key_3E;
        if (g_FishBestCatch[key_a] != 0) {
            func_801E0F4C((work->step_timer_09 * 0x30) + 0x80, 0x5B, key_a & 0xFF);
        } else {
            func_801E0F4C((work->step_timer_09 * 0x30) + 0x80, 0x5B, 0xFF);
        }
    } else {
        key_b = work->bounce_3C.half.key_3E;
        if (g_FishBestCatch[key_b] != 0) {
            func_801E0F4C(0x80 - (work->step_timer_09 * 0x30), 0x5B, key_b & 0xFF);
        } else {
            func_801E0F4C(0x80 - (work->step_timer_09 * 0x30), 0x5B, 0xFF);
        }
    }
    func_801E1320(0xB0, 0x9C);
    func_801E162C(8, 0x94, 0xFFFF);
    func_801D7B64();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & 0xFF;
    }
    func_801D7C10(0x58, 0x28, mask);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->handler_index_01 = 8;
    }
}
