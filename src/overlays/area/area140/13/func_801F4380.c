#include "area140_13.h"

/* The party at (x, y) facing the leader's way stands on a trigger: sets its flag and recolours the cell, or starts
 * the scene event while a party member stands ahead on the trigger's cell. Returns 1 when the trigger fired. */
MATCH u8 func_801F4380(s32 x, s32 y) {
    s32 i;
    s32 j;
    u8  actor_slot;
    s32 ahead_x;
    s32 ahead_y;

    for (i = 0; i < AREA140_TRIGGER_COUNT; i++) {
        if ((u8)x == D_801F4A84[i].x && (u8)y == D_801F4A84[i].y && (D_801F4A84[i].facing & 0xF) == g_Game.members[0].facing) {
            break;
        }
    }
    if (i == AREA140_TRIGGER_COUNT) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneEventFlags, D_801F4A84[i].flag) != 0) {
        return 0;
    }
    if (D_801F4A84[i].type != 0) {
        for (j = 0; j < g_PartySize; j++) {
            ahead_x = g_Game.members[j].pos.x.fixed + g_Game.members[j].unk_0C * g_Game.members[j].unk_09;
            ahead_y = g_Game.members[j].pos.y.fixed + g_Game.members[j].unk_10 * g_Game.members[j].unk_09;
            if ((u16)((ahead_y >> 16) - D_801F4AB4[D_801F4A84[i].type].y) < 2 && (u16)((ahead_x >> 16) - D_801F4AB4[D_801F4A84[i].type].x) < 2) {
                Game_SetScriptActive();
                g_SceneEventMode = 0x29;
                g_SceneEventStep = 0xA;
                return 0;
            }
        }
    }
    SYS_SetFlag(g_SceneEventFlags, D_801F4A84[i].flag);
    Area_CellSetPalette(D_801F4A84[i].x, D_801F4A84[i].y);
    if (D_801F4A84[i].spawn != 0) {
        actor_slot = Actor_FindFreeSpawned();
        if (actor_slot != GAME_NONE) {
            g_SpawnedActors[actor_slot].type         = 0x71;
            g_SpawnedActors[actor_slot].header.flags = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[actor_slot].pos.x.fixed  = D_801F4A84[i].x << 16;
            g_SpawnedActors[actor_slot].pos.y.fixed  = D_801F4A84[i].y << 16;
            g_SpawnedActors[actor_slot].link         = D_801F4A84[i].flag;
        }
    }
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
    return 1;
}
