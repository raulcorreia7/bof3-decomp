#include "game_00.h"

MATCH void func_801B26E0(void) {
    u8 i;
    u8 level;

    g_SpadWork->unk_09 -= 1;
    g_SpadWork->direction_08 = (g_SpadWork->direction_08 + 1) & 7;
    Actor_SelectScript(g_SpadWork->direction_08);
    i     = 1;
    level = g_SpadWork->unk_09;
    if (i < g_PartySize) {
        do {
            g_SpadWork = (Actor*)&g_BattlePartyBattlers[i];
            if (g_SpadWork->unk_01 == 3) {
                g_SpadWork->tint.bytes.unk_5D = -(level << 5);
                g_SpadWork->tint.bytes.unk_5E = g_SpadWork->tint.bytes.unk_5D;
                g_SpadWork->tint.bytes.unk_5F = g_SpadWork->tint.bytes.unk_5D;
            }
            i++;
        } while (i < g_PartySize);
    }
    g_GameState = (GameState*)g_BattlePartyBattlers;
    g_SpadWork  = (Actor*)g_BattlePartyBattlers;
    if (D_80145E99 == 0) {
        for (i = 1; i < g_PartySize; i++) {
            g_SpadWork = (Actor*)&g_BattlePartyBattlers[i];
            if (g_SpadWork->unk_01 == 3) {
                GFX_StagePalette(GAME_PALETTE_STAGE + (g_SpadWork->unk_05 << 6), 0);
                g_SpadWork->flags_00 &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
                g_SpadWork->tint.bytes.unk_5D = 0;
                g_SpadWork->tint.bytes.unk_5E = 0;
                g_SpadWork->tint.bytes.unk_5F = 0;
                g_SpadWork->tint.bytes.flags  = 0;
                g_SpadWork->unk_09            = 0;
                Actor_ClearVelocity();
                g_SpadWork->unk_18  = 0;
                g_SpadWork->unk_1C  = 0;
                g_SpadWork->gravity = 0;
            }
        }
        g_SpadWork = (Actor*)g_BattlePartyBattlers;
        g_BattlePartyBattlers[0].unk_02 += 1;
    }
}
