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
    func_801DE560(1, 0, 0, 60, (u8*)&D_801EB082);
    g_BattleMessageState = 1;
    speed_offset         = g_Battle.scroll_dir * index;
    g_AreaCameraStep     = 0x20;
    *(u16*)&g_AreaTargetCellX += (s8)((u8*)D_800B44C0)[speed_offset];
    value = ((u8*)D_800B44C0)[speed_offset + 1];
    *(u16*)&g_AreaTargetCellY += (s8)value;
    if (g_Battle.ui_step == 2) {
        g_AreaCameraHeightStep = (((((s32 (*)(s32, s32))Area_SampleHeight)(g_AreaScrollTargetX, g_AreaScrollTargetY) - g_AreaCameraHeight) << 16) >> 21);
    } else {
        g_AreaCameraHeightStep = 0;
    }
    EMI_LoadArchive(EMI_SLOT_BATL_SE);
    index = 5;
    if (g_Game.members[0].u.turn.command.type == BATTLE_COMMAND_ITEM) {
        func_801DDE7C(D_80145FB2, g_Game.members[0].u.turn.command.id);
    }
    if (D_801460E9 == 5) {
        func_801DDE7C(D_801460F2, D_801460EA);
    }
    if (D_80146229 == 5) {
        func_801DDE7C(D_80146232, D_8014622A);
    }
    count = 0;
    if (g_Battle.party_count != 0) {
        do {
            index = count & BYTE_MASK;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                g_Game.members[index].u.turn.command.type = 0;
                g_Game.members[index].header.mode         = 2;
                state                                     = g_Game.members[index].facing;
                g_Game.members[index].header.step         = 0;
                g_Game.members[index].unk_03              = 0;
                g_Game.members[index].unk_04              = 0;
                g_Game.members[index].facing              = state ^ 0x2;
            }
            count++;
        } while ((u32)(count & BYTE_MASK) < g_Battle.party_count);
    }
    phase = &g_Battle.ui_state;
    *phase += 1;
}
