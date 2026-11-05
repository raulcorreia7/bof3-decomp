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
        GAME_WORK_AREA_PTR->interaction_flags = GAME_WORK_AREA_PTR->interaction_flags & ~ACTOR_FLAG_FADE_BLACK;
        g_Task->mode                          = g_Task->unk_03;
        g_Task->unk_04                        = 0;
    }
}
