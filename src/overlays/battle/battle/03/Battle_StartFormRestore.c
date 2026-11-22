#include "battle_03.h"

/* Rebuilds the acting party battler from its template in place and shows it again. */
/* func_801E8684 */
MATCH void Battle_StartFormRestore(void) {
    PartyMember* saved;
    u8*          cells;
    u8           i;

    saved                                         = g_Task;
    g_Task                                        = g_BattleEffectBattler;
    g_GameState                                   = &g_Game.members[BATTLE_WORK->slot];
    BATTLE_WORK->scale.x                          = 0;
    g_Game.members[BATTLE_WORK->slot]             = s_BattleBattlerTemplates[BATTLE_WORK->slot];
    g_Game.members[BATTLE_WORK->slot].header.mode = 6;
    g_Game.members[BATTLE_WORK->slot].header.step = 4;
    g_Game.members[BATTLE_WORK->slot].unk_03      = 4;
    g_Game.members[BATTLE_WORK->slot].unk_04      = 1;
    g_Game.members[BATTLE_WORK->slot].unk_48      = 2;
    g_Game.members[BATTLE_WORK->slot].scale.x     = 0;
    g_Game.members[BATTLE_WORK->slot].u.turn.damage_flags.value |= BATTLER_DAMAGE_FORM_EFFECT_PLAYING;
    g_BattleEffects[BATTLE_WORK->slot].pos.x.fixed = g_EncounterParty[BATTLE_WORK->slot].x.fixed;
    g_BattleEffects[BATTLE_WORK->slot].pos.y.fixed = g_EncounterParty[BATTLE_WORK->slot].y.fixed;
    g_BattleEffects[BATTLE_WORK->slot].pos.z.fixed = Area_HeightSample(g_BattleEffects[BATTLE_WORK->slot].pos.x.fixed, g_BattleEffects[BATTLE_WORK->slot].pos.y.fixed) << 16;
    if (g_Game.members[BATTLE_WORK->slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[BATTLE_WORK->slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
        g_Game.members[BATTLE_WORK->slot].chr.ap                    = D_801EB4C8;
        g_Game.members[BATTLE_WORK->slot].chr.status                = D_801EB4CC;
        g_Game.members[BATTLE_WORK->slot].chr.fatigue               = g_Characters[g_Game.members[BATTLE_WORK->slot].character_index].fatigue;
        g_Game.members[BATTLE_WORK->slot].u.turn.damage_flags.value = D_801EB4D0;
        g_Game.members[BATTLE_WORK->slot].u.turn.action_flags.value = D_801EB4D4;
        for (i = 0; i < 8; i++) {
            cells    = (u8*)&g_Game.members[BATTLE_WORK->slot].status;
            cells[i] = 0;
        }
        func_801E0B64();
    }
    Battle_RescaleStats(BATTLE_WORK->slot);
    g_UiPanelTasks[BATTLE_WORK->slot + 13].u.battle.hp = g_Game.members[BATTLE_WORK->slot].chr.hp;
    g_UiPanelTasks[BATTLE_WORK->slot + 13].u.battle.ap = g_Game.members[BATTLE_WORK->slot].chr.ap;
    g_UiPanelTasks[BATTLE_WORK->slot + 13].unk_0B      = g_Game.members[BATTLE_WORK->slot].chr.hp * 55 / g_Game.members[BATTLE_WORK->slot].chr.stats.max_hp;
    g_UiPanelTasks[BATTLE_WORK->slot + 13].unk_0C      = g_Game.members[BATTLE_WORK->slot].chr.ap * 55 / g_Game.members[BATTLE_WORK->slot].chr.stats.max_ap;
    Script_Select(BATTLE_WORK->facing + 4);
    GFX_PaletteLoad((u8*)(BATTLE_ACTION_BLOCK_TABLE + (BATTLE_WORK->slot << 6)), 0);
    func_801DDAB4(g_Game.members[BATTLE_WORK->slot].chr.status);
    GFX_PaletteUploadRows();
    BATTLE_WORK->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task = saved;
    saved->header.mode++;
}
