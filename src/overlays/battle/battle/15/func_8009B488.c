#include "battle_15.h"

/* Seeds the battle work rows for the next phase: resets the scratch markers, folds the speed table into the
 * phase words, records the damage-delta shift, streams the three enemy slots and clears every active row's action
 * bytes. */
/* FAKE: retail takes the s32 view of the return value. */
MATCH void func_8009B488(void) {
    s32          speed_offset;
    u8           value;
    s32          count;
    u8           index;
    u8           state;
    volatile u8* phase;

    index                 = 2;
    g_BattleEventSlots[0] = 0;
    func_801DE560(1, 0, 0, 0x3C, (u8*)&D_801EB082);
    g_BattleMessageState = 1;
    speed_offset         = g_BattleScrollDir * index;
    g_AreaCameraStep     = 0x20;
    *(u16*)&D_8014930A += (s8)((u8*)D_800B44C0)[speed_offset];
    value = ((u8*)D_800B44C0)[speed_offset + 1];
    *(u16*)&D_8014930E += (s8)value;
    if (g_BattleUiStep == 2) {
        g_AreaCameraHeightStep =
            (s16)((s32)((((s32 (*)(s32, s32))Area_SampleHeight)(g_AreaScrollTargetX, g_AreaScrollTargetY) -
                         g_AreaCameraHeight)
                        << 16) >>
                  21);
    } else {
        g_AreaCameraHeightStep = 0;
    }
    EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_SE);
    index = 5;
    if (D_80145FA9 == 5) {
        func_801DDE7C(D_80145FB2, D_80145FAA[0]);
    }
    if (D_801460E9 == 5) {
        func_801DDE7C(D_801460F2, D_801460EA);
    }
    if (D_80146229 == 5) {
        func_801DDE7C(D_80146232, D_8014622A);
    }
    count = 0;
    if (g_BattlePartyCount != 0) {
        do {
            index = count & BYTE_MASK;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                g_BattlePartyBattlers[index].mode_119 = 0;
                g_BattlePartyBattlers[index].step_01  = 2;
                state                                 = g_BattlePartyBattlers[index].word_08.byte.facing_08;
                g_BattlePartyBattlers[index].unk_02   = 0;
                g_BattlePartyBattlers[index].unk_03   = 0;
                g_BattlePartyBattlers[index].unk_04   = 0;
                g_BattlePartyBattlers[index].word_08.byte.facing_08 = state ^ 2;
            }
            count++;
        } while ((u32)(count & BYTE_MASK) < (u8)g_BattlePartyCount);
    }
    phase = &g_BattleUiState;
    *phase += 1;
}
