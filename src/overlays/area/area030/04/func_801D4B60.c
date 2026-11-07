#include "area030_04.h"

/* Draws the AREA030 fishing panel: stages the panel bars at y 0x4E,
 * selects the fishing record row by the scratch pose, shows the recorded or
 * blank catch row and the pose-keyed icon, then draws the counter panel, the
 * frame at (0x14, 0x12, 0x118, 0x13) and the option mask derived from the work
 * slot when the area state is at least 3. */
MATCH void func_801D4B60(void) {
    s16 key;
    u8  fish;
    s32 mask;

    func_801E0ED0(0, 0x4E);
    key  = FISHING_STATE->bounce_3C.half.key_3E;
    fish = g_FishBestCatch[key];
    if (fish != 0) {
        func_801E1004(key & BYTE_MASK, fish, 0);
        func_801E0F4C(0x80, 0x5B, FISHING_STATE->bounce_3C.half.key_3E);
        func_801E162C(8, 0x94, FISHING_STATE->bounce_3C.half.key_3E);
    } else {
        func_801E1004(0xFF, 0, 0);
        func_801E0F4C(0x80, 0x5B, 0xFF);
        func_801E162C(8, 0x94, 0xFFFF);
    }
    Fishing_DrawRank(0xB0, 0x9C);
    func_801D7B64();
    func_801D9534(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(0x58, 0x28, mask);
}
