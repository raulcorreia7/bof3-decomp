#include "game_00.h"

MATCH void func_801BD394(void) {
    Actor* work;
    Actor* slot;
    s32    x;
    s32    y;
    s32    range;
    s32    dx;
    s32    dy;
    u8     count;
    u8     flag;

    flag = 0;
    if (((D_80145F09 == 3) || (D_80145F09 == 6)) && ((*(u32*)g_BattlePartyBattlers & 0xFFFF00) == 0x10A00)) {
        flag = 1;
    }
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        flag = 1;
    }
    work  = g_Task;
    slot  = (Actor*)((u8*)g_BattlePartyBattlers + work->unk_06 * BATTLE_PARTY_STRIDE);
    count = slot->unk_09;
    x     = slot->pos.x.fixed + slot->vx * count;
    y     = slot->pos.y.fixed + slot->vy * count;
    range = 0x18000;
    if (slot->state_70.byte != 0) {
        range = 0x20000;
    }
    dx = work->pos.x.fixed - x;
    if (dx < 0) {
        dx = -dx;
    }
    if (dx > range) {
        flag = 1;
    } else {
        dy = work->pos.y.fixed - y;
        if (dy < 0) {
            dy = -dy;
        }
        if (dy > range) {
            flag = 1;
        }
    }
    if ((g_AreaWalkFlags & (AREA_WALK_STEP_ACTIVE | AREA_WALK_RUN_ACTIVE | AREA_WALK_TRANSITION)) || flag) {
        g_GameState->mode_12B.u8_value = 0;
    } else {
        D_801CD1D8[g_SaveData.emi_loaded_character_index & EMI_LOADED_INDEX_MASK]();
    }
    if (g_GameState->mode_12B.u8_value == 0) {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->unk_09 = 0;
        Party_ClearBattlerState(g_Task->unk_05);
        g_Task->header.mode = 1;
        g_Task->unk_0B      = 0;
        func_801BC000();
    }
}
