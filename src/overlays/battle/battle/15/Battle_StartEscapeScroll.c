#include "battle_15.h"

/* Seeds the battle work rows for the next phase: resets the scratch markers, folds the speed table into the
 * phase words, records the damage-delta shift, streams the three enemy slots and clears every active row's action
 * bytes. */
/* FAKE: retail takes the s32 view of the return value. */
/* func_8009B488 */
MATCH void Battle_StartEscapeScroll(void) {
    s32          speed_offset;
    u8           value;
    s32          count;
    u8           index;
    u8           state;
    volatile u8* phase;

    index                        = 2;
    g_BattleEventSlots[0].active = 0;
    func_801DE560(1, 0, 0, 60, (u8*)&D_801EB082);
    g_BattleMessageState = 1;
    speed_offset         = g_Battle.scroll_dir * index;
    g_AreaCameraSpeed    = 0x20;
    *(u16*)&g_AreaTargetCellX += (s8)((u8*)g_BattleScrollDeltas)[speed_offset];
    value = ((u8*)g_BattleScrollDeltas)[speed_offset + 1];
    *(u16*)&g_AreaTargetCellY += (s8)value;
    if (g_Battle.ui_step == 2) {
        g_AreaCameraHeightDelta = (((((s32 (*)(s32, s32))Area_HeightSample)(g_AreaScrollTargetCoordX.fixed, g_AreaScrollTargetCoordY.fixed) - g_AreaCameraHeight) << 16) >> 21);
    } else {
        g_AreaCameraHeightDelta = 0;
    }
    EMI_ArchiveLoad(EMI_SLOT_BATL_SE);
    index = 5;
    if (g_Game.members[0].u.turn.command.type == BATTLE_COMMAND_ITEM) {
        func_801DDE7C(D_80145FB2, g_Game.members[0].u.turn.command.id);
    }
    if (g_Game.members[1].u.turn.command.type == 5) {
        func_801DDE7C(g_Game.members[1].u.turn.choice, g_Game.members[1].u.turn.command.id);
    }
    if (g_Game.members[2].u.turn.command.type == 5) {
        func_801DDE7C(g_Game.members[2].u.turn.choice, g_Game.members[2].u.turn.command.id);
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
    phase = &g_Battle.ui_mode;
    *phase += 1;
}
