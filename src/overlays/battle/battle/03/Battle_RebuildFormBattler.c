#include "battle_03.h"

/* Once the loader is ready, rebuilds the acting party battler from its template and refreshes its panel and palette. */
/* func_801E7BA0 */
MATCH void Battle_RebuildFormBattler(void) {
    PartyMember* saved;
    u8           slot;
    u8           facing;
    u8           i;
    u8*          cells;

    if (!EMI_IsReady()) {
        return;
    }
    GFX_FreePaletteFadeTarget(&g_Game.members[g_BattleEffectBattler->slot]);
    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        g_Battle.living_party_count = 0;
        g_Battle.party_count        = D_801463CF;
        for (i = 0; i < g_Battle.party_count; i++) {
            if (!(s_BattleBattlerTemplates[i].chr.status & 0x4000)) {
                g_Battle.living_party_count++;
            }
        }
        D_8014835E = g_Battle.party_count;
        D_80148358 = s_BattleBattlerStepIds[g_Battle.party_count + 0x2B];
        for (i = 1; i < g_Battle.party_count; i++) {
            g_BattleEffects[(u8)Battle_AllocEffect(0, 0x11)].target.party = &g_Game.members[i];
        }
    }

    saved       = g_Task;
    g_Task      = g_BattleEffectBattler;
    g_GameState = &g_Game.members[g_Task->slot];
    if (g_Game.members[g_Task->slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[g_Task->slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
        D_801EB4C8 = g_Game.members[g_Task->slot].chr.ap;
        D_801EB4CC = g_Game.members[g_Task->slot].chr.status;
        D_801EB4D0 = g_Game.members[g_Task->slot].u.turn.damage_flags.value;
        D_801EB4D4 = g_Game.members[g_Task->slot].u.turn.action_flags.value;
        D_801EB4CC &= ~0x4000;
        D_801EB4D0 &= 0xFFFE7FFF;
        D_801EB4D4 &= 0xFFF884FD;
    }

    slot                                     = g_Task->slot;
    facing                                   = g_Game.members[slot].facing;
    g_Game.members[slot]                     = s_BattleBattlerTemplates[slot];
    g_Game.members[g_Task->slot].header.mode = 6;
    g_Game.members[g_Task->slot].header.step = 4;
    g_Game.members[g_Task->slot].unk_03      = 4;
    g_Game.members[g_Task->slot].unk_04      = 1;
    g_Game.members[g_Task->slot].facing      = facing;
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
    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        D_801454F5[0] = D_801463D4;
        D_801454F6[0] = D_801463D5;
    } else {
        D_801454F5[g_Task->slot * 3] = D_801463D4;
        D_801454F6[g_Task->slot * 3] = D_801463D5;
    }
    g_Task = saved;
    g_Battle.flags &= ~BATTLE_STATE_RELOAD_PARTY;
    saved->header.mode++;
}
