#include "area030_04.h"

/* The status panel frame the row is drawn into. */
#define FISHING_FRAME_STEP    0x10
#define FISHING_PANEL_Y       0x12
#define FISHING_PANEL_HEIGHT  0x13
#define FISHING_PANEL_X       0x14
#define FISHING_ROW_STEP      0x1E
#define FISHING_CURSOR_Y      0x28
#define FISHING_CURSOR_STEP   0x2D
#define FISHING_BAR_Y         0x4E
#define FISHING_CURSOR_ORIGIN 0x58
#define FISHING_ICON_Y        0x5B
#define FISHING_ICON_X        0x80
#define FISHING_ROW_ORIGIN_Y  0x94
#define FISHING_ROW_ORIGIN_X  0x9C
#define FISHING_PANEL_WIDTH   0x118

/* Draws one row of the rotating status display. */
MATCH void func_801D5048(void) {
    s32 mask;
    u8  height;

    height = FISHING_PANEL_HEIGHT;
    if (FISHING_STATE->saved_index_0B == 0) {
        func_801D9534(FISHING_PANEL_X, (FISHING_PANEL_Y - (FISHING_STATE->step_timer_09 * FISHING_FRAME_STEP)) & 0xFFFE,
                      FISHING_PANEL_WIDTH, height, 0);
        mask = 0;
        func_801D7C10(((FISHING_STATE->step_timer_09 * FISHING_CURSOR_STEP) + FISHING_CURSOR_ORIGIN) & HALF_MASK,
                      FISHING_CURSOR_Y, 0);
        goto draw; /* the shared tail draws the row once, from either arm */
    }
    func_801D9534(FISHING_PANEL_X, FISHING_PANEL_Y, FISHING_PANEL_WIDTH, height, 0);
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    } else {
        mask = 0;
    }
    func_801D7C10(FISHING_CURSOR_ORIGIN, FISHING_CURSOR_Y, mask);
draw:
    FISHING_STATE->step_timer_09++;
    func_801E0ED0((-(FISHING_STATE->step_timer_09 * 0x500000) >> 0x10), FISHING_BAR_Y);
    if (g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E] != 0) {
        func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + FISHING_ICON_X, FISHING_ICON_Y,
                      FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK);
        func_801E1004(FISHING_STATE->bounce_3C.half.key_3E & BYTE_MASK,
                      g_FishBestCatch[FISHING_STATE->bounce_3C.half.key_3E], FISHING_STATE->step_timer_09);
    } else {
        func_801E0F4C(FISHING_STATE->step_timer_09 * 0x30 + FISHING_ICON_X, FISHING_ICON_Y, 0xFF);
        func_801E1004(0xFF, 0, FISHING_STATE->step_timer_09);
    }
    func_801E1320(0xB0, FISHING_STATE->step_timer_09 * FISHING_ROW_STEP + FISHING_ROW_ORIGIN_X);
    func_801E162C(8, FISHING_STATE->step_timer_09 * FISHING_ROW_STEP + FISHING_ROW_ORIGIN_Y, 0xFFFF);
    if (FISHING_STATE->step_timer_09 == 4) {
        if (FISHING_STATE->saved_index_0B == 0) {
            FISHING_STATE->handler_index_01 = 0;
        } else if (FISHING_STATE->cue_index_06 == 0) {
            FISHING_STATE->handler_index_01 = 2;
        } else if (FISHING_STATE->cue_index_06 == 2) {
            FISHING_STATE->handler_index_01++;
        }
    }
}
