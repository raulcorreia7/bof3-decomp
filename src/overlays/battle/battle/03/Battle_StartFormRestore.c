#include "battle_03.h"

/* Rebuilds the acting party battler from its template in place and shows it again. */
/* func_801E8684 */
MATCH void Battle_StartFormRestore(void) {
    PartyMember* saved;
    u8*          cells;
    u8           i;

    saved = SELF(PartyMember);
    SELF_SET(g_BattleEffectBattler);
    g_GameState                                         = &g_Game.members[SELF(PartyMember)->slot];
    SELF(PartyMember)->scale.x                          = 0;
    g_Game.members[SELF(PartyMember)->slot]             = s_BattleBattlerTemplates[SELF(PartyMember)->slot];
    g_Game.members[SELF(PartyMember)->slot].header.mode = 6;
    g_Game.members[SELF(PartyMember)->slot].header.step = 4;
    g_Game.members[SELF(PartyMember)->slot].unk_03      = 4;
    g_Game.members[SELF(PartyMember)->slot].unk_04      = 1;
    g_Game.members[SELF(PartyMember)->slot].unk_48      = 2;
    g_Game.members[SELF(PartyMember)->slot].scale.x     = 0;
    g_Game.members[SELF(PartyMember)->slot].u.turn.damage_flags.value |= BATTLER_DAMAGE_FORM_EFFECT_PLAYING;
    g_BattleEffects[SELF(PartyMember)->slot].pos.x.fixed = g_AreaEncounterPlacement.party[SELF(PartyMember)->slot].x.fixed;
    g_BattleEffects[SELF(PartyMember)->slot].pos.y.fixed = g_AreaEncounterPlacement.party[SELF(PartyMember)->slot].y.fixed;
    g_BattleEffects[SELF(PartyMember)->slot].pos.z.fixed = Area_HeightSample(g_BattleEffects[SELF(PartyMember)->slot].pos.x.fixed, g_BattleEffects[SELF(PartyMember)->slot].pos.y.fixed) << 16;
    if (g_Game.members[SELF(PartyMember)->slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[SELF(PartyMember)->slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
        g_Game.members[SELF(PartyMember)->slot].chr.ap                    = D_801EB4C8;
        g_Game.members[SELF(PartyMember)->slot].chr.status                = D_801EB4CC;
        g_Game.members[SELF(PartyMember)->slot].chr.fatigue               = g_Characters[g_Game.members[SELF(PartyMember)->slot].character_index].fatigue;
        g_Game.members[SELF(PartyMember)->slot].u.turn.damage_flags.value = D_801EB4D0;
        g_Game.members[SELF(PartyMember)->slot].u.turn.action_flags.value = D_801EB4D4;
        for (i = 0; i < 8; i++) {
            cells    = (u8*)&g_Game.members[SELF(PartyMember)->slot].status;
            cells[i] = 0;
        }
        func_801E0B64();
    }
    Battle_RescaleStats(SELF(PartyMember)->slot);
    g_UiPanelTasks[SELF(PartyMember)->slot + 13].u.battle.hp = g_Game.members[SELF(PartyMember)->slot].chr.hp;
    g_UiPanelTasks[SELF(PartyMember)->slot + 13].u.battle.ap = g_Game.members[SELF(PartyMember)->slot].chr.ap;
    g_UiPanelTasks[SELF(PartyMember)->slot + 13].unk_0B      = g_Game.members[SELF(PartyMember)->slot].chr.hp * 55 / g_Game.members[SELF(PartyMember)->slot].chr.stats.max_hp;
    g_UiPanelTasks[SELF(PartyMember)->slot + 13].unk_0C      = g_Game.members[SELF(PartyMember)->slot].chr.ap * 55 / g_Game.members[SELF(PartyMember)->slot].chr.stats.max_ap;
    Script_Select(SELF(PartyMember)->facing + 4);
    GFX_PaletteLoad((u8*)(BATTLE_ACTION_BLOCK_TABLE + (SELF(PartyMember)->slot << 6)), 0);
    func_801DDAB4(g_Game.members[SELF(PartyMember)->slot].chr.status);
    GFX_PaletteUploadRows();
    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF_SET(saved);
    saved->header.mode++;
}
