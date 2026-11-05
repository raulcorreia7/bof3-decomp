#include "area030_04.h"

/* The world state word and the pad word share the PsyQ button bits:
 * PADLleft|PADLdown is 0xC000, PADLup|PADLright is 0x3000 and PADRdown is
 * 0x40. */

/* D_80146889 and D_801468A4 are two views of the 0x98-byte world-state row
 * table at 0x80146888, so both are stepped with the row size. */

/* Updates the world panel's selection state from the pad and the
 * world state word: it latches the new mode, steps the row timer, refreshes
 * the slot timer word and counts the state changes. */
MATCH void func_801DB140(void) {
    FishingState* work;
    u8*           counter;

    D_801E31FC = D_801E31F8;
    if (g_ActorSlots[0].y.fixed > 0x3E7FFF) {
        D_80144199                                             = 1;
        D_8014419E                                             = 4;
        D_8014403D                                             = 4;
        D_80144125                                             = 7;
        g_ActorSlots[0].unk_01                                 = 0;
        D_8014420D                                             = 0;
        D_80146889[D_801E3208 * sizeof(FishingSelectionState)] = 6;
        SND_PlayCue(EMI_CUE_ID(2, 3));
        SND_StopSequence(0, 1);
        SND_PlayBgm(0x2A, 0x64, 8);
        Actor_RequestScript(0xA);
        FISHING_STATE->sub_index_03 = 3;
        return;
    }
    if (g_InputHeld & (PADLleft | PADLdown)) {
        if (g_InputPressed & (PADLleft | PADLdown)) {
            D_801E31F8                   = 2;
            FISHING_STATE->step_timer_09 = 8;
            D_8014421C                   = D_801E320C->unk_05;
            Actor_RequestScript(8);
            goto counted; /* the pad press counts as one state change */
        }
        work = FISHING_STATE;
        if (work->step_timer_09 != 0) {
            work->step_timer_09 -= 1;
            func_8014D978();
        counted:
            D_80144216 += 1;
        } else {
            D_8014421C = 0;
            D_801E31F8 = 0;
            Actor_RequestScript(7);
        }
        if (g_InputPressed & PADRdown) {
            D_801468A4[D_801E3208].state = (s32)(s8)(D_801468A4[D_801E3208].state - (D_801E320C->unk_03 + 2));
            Actor_RequestScript(7);
            func_801DB04C();
            goto counted_again; /* the slot timer moved, so the state changed */
        }
        if (g_InputHeld & PADRdown) {
            func_801DB0AC();
            func_801DB04C();
            func_8014D978();
        counted_again:
            counter = &D_80144216;
            *counter += 1;
        }
    } else if (g_InputHeld & (PADLup | PADLright)) {
        s32* word = (s32*)((u8*)D_801468A4 + D_801E3208 * sizeof(FishingSelectionState));

        D_801E31F8 = 0;
        D_8014421C = D_801E320C->unk_06;
        *word      = 0;
        Actor_RequestScript(0);
        D_80144216 -= 1;
    } else if (g_InputHeld & PADRdown) {
        if (g_InputPressed & PADRdown) {
            D_801468A4[D_801E3208].state = (s32)(s8)(D_801468A4[D_801E3208].state - (D_801E320C->unk_03 + 2));
        } else {
            func_801DB0AC();
        }
        D_801E31F8 = 1;
        D_8014421C = D_801E320C->unk_04;
        Actor_RequestScript(7);
        func_8014D978();
        D_80144216 += 1;
    } else {
        D_801E31F8                   = 0;
        D_8014421C                   = 0;
        D_801468A4[D_801E3208].state = 0;
        Actor_RequestScript(7);
    }
    func_801DDD4C();
}
