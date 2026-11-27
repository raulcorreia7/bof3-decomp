#include "area030_04.h"

/* Draws the catch page for pond slot g_FishingHookedFish (fish id and
 * length) and, on a 0x50 pad press, resolves the catch: fish 0x16 sets
 * message 1, a failed inventory add of item fish + 0x38 sets message 2,
 * and a successful add jumps the state (unk_03) to 0xD; then queues cue
 * 0x102 and advances the state. */
/* func_801DBBAC */
MATCH void Fishing_CatchPage(void) {
    u16 fish;
    s32 offset;

    Fishing_DrawCatchBar(0, FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, g_Actors[g_FishingHookedFish].unk_06);
    offset = g_FishingHookedFish * 0x98;
    Fishing_DrawCatchRow(g_Actors[g_FishingHookedFish].unk_06, D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    func_801E1C7C();

    if (g_PadStates[0].pressed & (PADRup | PADRdown)) {
        g_FishingNewRecord              = 0;
        SELF(FishingState)->saved_index = 0;
        /* pond record +6 (fish id), read through the table base: the
         * D_8014688E spelling lets gcc hold its address across the calls */
        /* FAKE: retail reads g_Actors as u8[]. */
        fish                            = ((u8*)g_Actors)[g_FishingHookedFish * 0x98 + 6];
        if ((u8)fish == 0x16) {
            SELF(FishingState)->timer       = 4;
            SELF(FishingState)->saved_index = 1;
        } else if (!(Item_Add(ITEM_CATEGORY_ITEM, (fish + ITEM_JELLYFISH) & BYTE_MASK, 1, 0) & BYTE_MASK)) {
            SELF(FishingState)->timer       = 4;
            SELF(FishingState)->saved_index = 2;
        } else {
            SELF(FishingState)->sub_index = 0xD;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SELF(FishingState)->sub_index++;
    }
    Script_AnimStepLoop();
    Fishing_DrawDimScreen();
}
