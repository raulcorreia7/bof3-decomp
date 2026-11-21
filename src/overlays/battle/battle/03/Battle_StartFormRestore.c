#include "battle_03.h"

/* Rebuilds the acting party battler from its template in place and shows it again. */
/* func_801E8684 */
MATCH void Battle_StartFormRestore(void) {
    PartyMember* saved;
    u8*          cells;
    u8           i;

    saved                                    = g_Task;
    g_Task                                   = g_BattleEffectBattler;
    g_GameState                              = &g_Game.members[g_Task->slot];
    g_Task->scale.x                          = 0;
    g_Game.members[g_Task->slot]             = s_BattleBattlerTemplates[g_Task->slot];
    g_Game.members[g_Task->slot].header.mode = 6;
    g_Game.members[g_Task->slot].header.step = 4;
    g_Game.members[g_Task->slot].unk_03      = 4;
    g_Game.members[g_Task->slot].unk_04      = 1;
    g_Game.members[g_Task->slot].unk_48      = 2;
    g_Game.members[g_Task->slot].scale.x     = 0;
    g_Game.members[g_Task->slot].u.turn.damage_flags.value |= BATTLER_DAMAGE_FORM_EFFECT_PLAYING;
    g_BattleEffects[g_Task->slot].pos.x.fixed = g_EncounterParty[g_Task->slot].x.fixed;
    g_BattleEffects[g_Task->slot].pos.y.fixed = g_EncounterParty[g_Task->slot].y.fixed;
    g_BattleEffects[g_Task->slot].pos.z.fixed = Area_SampleHeight(g_BattleEffects[g_Task->slot].pos.x.fixed, g_BattleEffects[g_Task->slot].pos.y.fixed) << 16;
    if (g_Game.members[g_Task->slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[g_Task->slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
        g_Game.members[g_Task->slot].chr.ap                    = D_801EB4C8;
        g_Game.members[g_Task->slot].chr.status                = D_801EB4CC;
        g_Game.members[g_Task->slot].chr.fatigue               = g_Characters[g_Game.members[g_Task->slot].character_index].fatigue;
        g_Game.members[g_Task->slot].u.turn.damage_flags.value = D_801EB4D0;
        g_Game.members[g_Task->slot].u.turn.action_flags.value = D_801EB4D4;
        for (i = 0; i < 8; i++) {
            cells    = (u8*)&g_Game.members[g_Task->slot].status;
            cells[i] = 0;
        }
        func_801E0B64();
    }
    Battle_RescaleStats(g_Task->slot);
    g_UiPanelTasks[g_Task->slot + 13].u.battle.hp = g_Game.members[g_Task->slot].chr.hp;
    g_UiPanelTasks[g_Task->slot + 13].u.battle.ap = g_Game.members[g_Task->slot].chr.ap;
    g_UiPanelTasks[g_Task->slot + 13].unk_0B      = g_Game.members[g_Task->slot].chr.hp * 55 / g_Game.members[g_Task->slot].chr.stats.max_hp;
    g_UiPanelTasks[g_Task->slot + 13].unk_0C      = g_Game.members[g_Task->slot].chr.ap * 55 / g_Game.members[g_Task->slot].chr.stats.max_ap;
    Script_Select(g_Task->facing + 4);
    GFX_LoadPalette((u8*)(BATTLE_ACTION_BLOCK_TABLE + (g_Task->slot << 6)), 0);
    func_801DDAB4(g_Game.members[g_Task->slot].chr.status);
    GFX_UploadPaletteRows();
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task = saved;
    saved->header.mode++;
}
