#include "area030_04.h"

/* Slides the AREA030 fishing panel in: steps the slide counter at
 * work+0x09 down, draws the panel bars, the recorded or blank catch row keyed
 * by work+0x3E, the counter panel and the frame offset by that counter, then
 * the option mask, and advances the work state at work+0x01 once the counter
 * reaches zero. */
MATCH void func_801D4984(void) {
    s16 key;
    s32 mask;

    FISHING_STATE->step_timer_09--;
    func_801E0ED0(-(FISHING_STATE->step_timer_09 * 0x50), 0x4E);
    key = FISHING_STATE->bounce_3C.half.key_3E;
    if (g_FishBestCatch[key] != 0) {
        func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + 0x80, 0x5B, key);
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK,
                      g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E], FISHING_STATE->step_timer_09);
    } else {
        func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + 0x80, 0x5B, 0xFF);
        func_801E1004(0xFF, 0, FISHING_STATE->step_timer_09);
    }
    func_801E1320(0xB0, FISHING_STATE->step_timer_09 * 0x1E + 0x9C);
    func_801E162C(8, FISHING_STATE->step_timer_09 * 0x1E + 0x94, 0xFFFF);
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);
    if (FISHING_STATE->step_timer_09 == 0) {
        FISHING_STATE->handler_index_01++;
    }
}
