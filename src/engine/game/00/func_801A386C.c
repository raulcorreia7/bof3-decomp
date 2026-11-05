#include "game_00.h"

MATCH void func_801A386C(void) {
    u8 index;

    if (D_80145BD4[g_CurrentActor->unk_93].red_offset < 0x1F) {
        D_80145BD4[g_CurrentActor->unk_93].red_offset = D_80145BD4[g_CurrentActor->unk_93].red_offset + 1;
    }
    if (D_80145BD4[g_CurrentActor->unk_93].green_offset < 0x1F) {
        D_80145BD4[g_CurrentActor->unk_93].green_offset = D_80145BD4[g_CurrentActor->unk_93].green_offset + 1;
    }
    if (D_80145BD4[g_CurrentActor->unk_93].blue_offset < 0x1F) {
        D_80145BD4[g_CurrentActor->unk_93].blue_offset = D_80145BD4[g_CurrentActor->unk_93].blue_offset + 1;
    }
    index = g_CurrentActor->unk_93;
    if ((D_80145BD4[index].blue_offset + D_80145BD4[index].green_offset + D_80145BD4[index].red_offset) == 0x5D) {
        GFX_FreePaletteFade(index);
        GAME_WORK_AREA_PTR->flags_74 = GAME_WORK_AREA_PTR->flags_74 & ~ACTOR_FLAG_FADE_BLACK;
        g_SpadWork->unk_01           = g_SpadWork->unk_03;
        g_SpadWork->unk_04           = 0;
    }
}
