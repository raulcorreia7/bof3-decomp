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
    GFX_PaletteFreeFadeTarget(&g_Game.members[g_BattleEffectBattler->slot]);
    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        g_Battle.living_party_count = 0;
        g_Battle.party_count        = g_Battle.unk_EF;
        for (i = 0; i < g_Battle.party_count; i++) {
            if (!(s_BattleBattlerTemplates[i].chr.status & 0x4000)) {
                g_Battle.living_party_count++;
            }
        }
        g_UIPanelTasks[1].unk_0A = g_Battle.party_count;
        g_UIPanelTasks[1].pos.vx = s_BattleBattlerStepIds[g_Battle.party_count + 0x2B];
        for (i = 1; i < g_Battle.party_count; i++) {
            g_BattleEffects[(u8)Battle_AllocEffect(0, 0x11)].target.party = &g_Game.members[i];
        }
    }

    saved = SELF(PartyMember);
    SELF_SET(g_BattleEffectBattler);
    g_GameState = &g_Game.members[SELF(PartyMember)->slot];
    if (g_Game.members[SELF(PartyMember)->slot].chr.character_id == CHAR_ID_RYU_ADULT || g_Game.members[SELF(PartyMember)->slot].chr.character_id == CHAR_ID_RYU_YOUNG) {
        D_801EB4C8 = g_Game.members[SELF(PartyMember)->slot].chr.ap;
        D_801EB4CC = g_Game.members[SELF(PartyMember)->slot].chr.status;
        D_801EB4D0 = g_Game.members[SELF(PartyMember)->slot].u.turn.damage_flags.value;
        D_801EB4D4 = g_Game.members[SELF(PartyMember)->slot].u.turn.action_flags.value;
        D_801EB4CC &= ~0x4000;
        D_801EB4D0 &= 0xFFFE7FFF;
        D_801EB4D4 &= 0xFFF884FD;
    }

    slot                                                = SELF(PartyMember)->slot;
    facing                                              = g_Game.members[slot].facing;
    g_Game.members[slot]                                = s_BattleBattlerTemplates[slot];
    g_Game.members[SELF(PartyMember)->slot].header.mode = 6;
    g_Game.members[SELF(PartyMember)->slot].header.step = 4;
    g_Game.members[SELF(PartyMember)->slot].unk_03      = 4;
    g_Game.members[SELF(PartyMember)->slot].unk_04      = 1;
    g_Game.members[SELF(PartyMember)->slot].facing      = facing;
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
    g_UIPanelTasks[SELF(PartyMember)->slot + 13].u.battle.hp = g_Game.members[SELF(PartyMember)->slot].chr.hp;
    g_UIPanelTasks[SELF(PartyMember)->slot + 13].u.battle.ap = g_Game.members[SELF(PartyMember)->slot].chr.ap;
    g_UIPanelTasks[SELF(PartyMember)->slot + 13].unk_0B      = g_Game.members[SELF(PartyMember)->slot].chr.hp * 55 / g_Game.members[SELF(PartyMember)->slot].chr.stats.max_hp;
    g_UIPanelTasks[SELF(PartyMember)->slot + 13].unk_0C      = g_Game.members[SELF(PartyMember)->slot].chr.ap * 55 / g_Game.members[SELF(PartyMember)->slot].chr.stats.max_ap;
    Script_Select(SELF(PartyMember)->facing + 4);
    GFX_PaletteLoad((u8*)(BATTLE_ACTION_BLOCK_TABLE + (SELF(PartyMember)->slot << 6)), 0);
    func_801DDAB4(g_Game.members[SELF(PartyMember)->slot].chr.status);
    GFX_PaletteUploadRows();
    if (g_Battle.flags & BATTLE_STATE_RELOAD_PARTY) {
        D_801454F5[0] = g_Battle.unk_F4[0];
        D_801454F6[0] = g_Battle.unk_F4[1];
    } else {
        D_801454F5[SELF(PartyMember)->slot * 3] = g_Battle.unk_F4[0];
        D_801454F6[SELF(PartyMember)->slot * 3] = g_Battle.unk_F4[1];
    }
    SELF_SET(saved);
    g_Battle.flags &= ~BATTLE_STATE_RELOAD_PARTY;
    saved->header.mode++;
}
