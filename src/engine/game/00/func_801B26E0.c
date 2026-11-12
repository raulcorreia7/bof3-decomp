#include "game_00.h"

MATCH void func_801B26E0(void) {
    u8 i;
    u8 level;

    g_Task->timer -= 1;
    g_Task->direction_08 = (g_Task->direction_08 + 1) & 0x7;
    Actor_SelectScript(g_Task->direction_08);
    i     = 1;
    level = g_Task->timer;
    if (i < g_PartySize) {
        do {
            TASK_SET(&g_Game.members[i]);
            if (g_Task->header.mode == 3) {
                g_Task->tint.bytes.unk_5D = -(level << 5);
                g_Task->tint.bytes.unk_5E = g_Task->tint.bytes.unk_5D;
                g_Task->tint.bytes.unk_5F = g_Task->tint.bytes.unk_5D;
            }
            i++;
        } while (i < g_PartySize);
    }
    g_GameState = g_Game.members;
    TASK_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 0) {
        for (i = 1; i < g_PartySize; i++) {
            TASK_SET(&g_Game.members[i]);
            if (g_Task->header.mode == 3) {
                GFX_LoadPalette(GAME_PALETTE_STAGE + (g_Task->unk_05 << 6), 0);
                g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                ACTOR_CLEAR_TINT();
                g_Task->tint.bytes.flags = 0;
                g_Task->timer            = 0;
                Actor_ClearVelocity();
                g_Task->unk_18  = 0;
                g_Task->unk_1C  = 0;
                g_Task->gravity = 0;
            }
        }
        TASK_SET(g_Game.members);
        g_Game.members[0].header.step += 1;
    }
}
