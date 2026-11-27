#include "area030_04.h"

/* The world state word and the pad word share the PsyQ button bits:
 * PADLleft|PADLdown is 0xC000, PADLup|PADLright is 0x3000 and PADRdown is
 * 0x40. */

/* D_80146889 and D_801468A4 are two views of the 0x98-byte world-state row
 * table at 0x80146888, so both are stepped with the row size. */

/* Updates the world panel's selection state from the pad and the
 * world state word: it latches the new mode, steps the row timer, refreshes
 * the slot timer word and counts the state changes. */
/* func_801DB140 */
MATCH void Fishing_HookedReel(void) {
    FishingState* work;
    u8*           counter;

    D_801E31FC = D_801E31F8;
    if (g_SpawnedActors[0].pos.y.fixed >= FISHING_CATCH_HEIGHT) {
        D_80144199                                                      = 1;
        D_8014419E                                                      = 4;
        D_8014403D                                                      = 4;
        D_80144125                                                      = 7;
        g_SpawnedActors[0].header.mode                                  = 0;
        D_8014420D                                                      = 0;
        D_80146889[g_FishingHookedFish * sizeof(FishingSelectionState)] = 6;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        SND_SeqStop(0, 1);
        SND_BGMPlay(0x2A, 0x64, 8);
        Script_Request(0xA);
        SELF(FishingState)->sub_index = 3;
        return;
    }
    if (g_PadStates[0].held & (PADLleft | PADLdown)) {
        if (g_PadStates[0].pressed & (PADLleft | PADLdown)) {
            D_801E31F8                = 2;
            SELF(FishingState)->timer = 8;
            D_8014421C                = g_FishingRodRow->cursor_left_speed;
            Script_Request(8);
            goto counted; /* the pad press counts as one state change */
        }
        work = SELF(FishingState);
        if (work->timer != 0) {
            work->timer -= 1;
            Script_AnimStepLoop();
        counted:
            D_80144216 += 1;
        } else {
            D_8014421C = 0;
            D_801E31F8 = 0;
            Script_Request(7);
        }
        if (g_PadStates[0].pressed & PADRdown) {
            D_801468A4[g_FishingHookedFish].state = (s8)(D_801468A4[g_FishingHookedFish].state - (g_FishingRodRow->reel_cursor_size + 2));
            Script_Request(7);
            func_801DB04C();
            goto counted_again;
        }
        if (g_PadStates[0].held & PADRdown) {
            func_801DB0AC();
            func_801DB04C();
            Script_AnimStepLoop();
        counted_again:
            counter = &D_80144216;
            *counter += 1;
        }
    } else if (g_PadStates[0].held & (PADLup | PADLright)) {
        s32* word = (s32*)((u8*)D_801468A4 + g_FishingHookedFish * sizeof(FishingSelectionState));

        D_801E31F8 = 0;
        D_8014421C = g_FishingRodRow->cursor_right_speed;
        *word      = 0;
        Script_Request(0);
        D_80144216 -= 1;
    } else if (g_PadStates[0].held & PADRdown) {
        if (g_PadStates[0].pressed & PADRdown) {
            D_801468A4[g_FishingHookedFish].state = (s8)(D_801468A4[g_FishingHookedFish].state - (g_FishingRodRow->reel_cursor_size + 2));
        } else {
            func_801DB0AC();
        }
        D_801E31F8 = 1;
        D_8014421C = g_FishingRodRow->cursor_return_speed;
        Script_Request(7);
        Script_AnimStepLoop();
        D_80144216 += 1;
    } else {
        D_801E31F8                            = 0;
        D_8014421C                            = 0;
        D_801468A4[g_FishingHookedFish].state = 0;
        Script_Request(7);
    }
    func_801DDD4C();
}
