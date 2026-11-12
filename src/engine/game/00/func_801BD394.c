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
    if (((g_Game.members[0].chr.character_id == CHAR_ID_TEEPO) || (g_Game.members[0].chr.character_id == CHAR_ID_PECO)) && ((*(u32*)g_Game.members & 0xFFFF00) == 0x10A00)) {
        flag = 1;
    }
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        flag = 1;
    }
    work  = g_Task;
    slot  = (Actor*)((u8*)g_Game.members + work->unk_06 * BATTLE_PARTY_STRIDE);
    count = slot->timer;
    x     = slot->pos.x.fixed + slot->vx * count;
    y     = slot->pos.y.fixed + slot->vy * count;
    range = TO_COORD(1) + COORD_HALF;
    if (slot->state_70.byte != 0) {
        range = TO_COORD(2);
    }
    dx = work->pos.x.fixed - x;
    dx = ABS(dx);
    if (dx > range) {
        flag = 1;
    } else {
        dy = work->pos.y.fixed - y;
        dy = ABS(dy);
        if (dy > range) {
            flag = 1;
        }
    }
    if ((g_Game.walk_flags & (AREA_WALK_LEADER_SWITCH_ACTIVE | AREA_WALK_MENU_ACTIVE | AREA_WALK_TRANSITION)) || flag) {
        g_Game.current->u.field.mode_12B.u8_value = 0;
    } else {
        D_801CD1D8[g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK]();
    }
    if (g_Game.current->u.field.mode_12B.u8_value == 0) {
        Actor_RequestScript(g_Task->direction_08);
        g_Task->timer = 0;
        Party_ClearBattlerState(g_Task->unk_05);
        g_Task->header.mode  = 1;
        g_Task->param.unk_0B = 0;
        func_801BC000();
    }
}
