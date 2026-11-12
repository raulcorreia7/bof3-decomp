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

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    key  = FISHING_STATE->bounce_3C.half.key_3E;
    fish = g_FishingBestCatch[key];
    if (fish != 0) {
        func_801E1004(key & BYTE_MASK, fish, 0);
        Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, FISHING_STATE->bounce_3C.half.key_3E);
        Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, FISHING_STATE->bounce_3C.half.key_3E);
    } else {
        func_801E1004(0xFF, 0, 0);
        Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, GAME_NONE);
        Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 65535);
    }
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    func_801D7B64();
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
    mask = 0;
    if (D_80145E93[0] >= 3u) {
        mask = BIT(FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
}
