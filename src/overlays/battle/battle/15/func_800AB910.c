#include "battle_15.h"

/* Queues a battler action record from the local or enemy work entry and copies its target offsets and stage id. */
#ifdef NON_MATCHING
NON_MATCHING void func_800AB910(void) {
    u32 slot;
    u8* work;
    u8  target;
    u8  unit;
    u8  state;
    u8  stage;
    u32 flags;
    u16 off_y;
    u16 off_x;
    u16 off_z;

    slot                                   = Battle_AllocEffect(0, 3);
    g_BattleEffects[(u8)slot].target.party = BATTLE_WORK;
    target                                 = g_BattleActingBattler;
    if (BATTLER_IS_PLAYER(target)) {
        flags = FIELD(u32, D_80146390, 0xCu);
        if (flags & 2) {
            state = 7;
        } else {
            state = D_801C90ED[D_80145F12[target * BATTLE_PARTY_STRIDE] * 0x18];
        }
    } else {
        flags = FIELD(u32, D_80146390, 0xCu);
        if (flags & 2) {
            state = 7;
        } else {
            state = D_801EB721[(target - 3) * 0x118];
        }
    }
    g_BattleEffects[(u8)slot].unk_07 = state;
    work                             = (u8*)BATTLE_WORK;
    unit                             = work[0x05];
    if (BATTLER_IS_PLAYER(unit)) {
        off_y                            = FIELD(u16, work, 0x2Eu);
        off_x                            = FIELD(u16, work, 0x30u);
        off_z                            = FIELD(u16, work, 0x32u);
        flags                            = FIELD(u8, g_GameState, 0x79u);
        g_BattleEffects[(u8)slot].unk_32 = off_z;
        stage                            = work[0x08];
        g_BattleEffects[(u8)slot].unk_2E = off_y + (s8)g_BattlePanelOffsets[stage * 2 + flags * 8];
        g_BattleEffects[(u8)slot].unk_30 = off_x + (s8)(g_BattlePanelOffsets + 1)[stage * 2 + flags * 8];
        g_BattleEffects[(u8)slot].unk_08 = g_BattlePartyBattlers[unit].unk_08;
    } else {
        off_y                            = FIELD(u16, work, 0x2Eu);
        off_x                            = FIELD(u16, work, 0x30u);
        off_z                            = FIELD(u16, work, 0x32u);
        flags                            = FIELD(u8, g_GameState, 0x79u);
        g_BattleEffects[(u8)slot].unk_32 = off_z;
        g_BattleEffects[(u8)slot].unk_2E = off_y + (s8)g_BattleCurrentEnemy->unk_E2;
        g_BattleEffects[(u8)slot].unk_30 = off_x + (s8)g_BattleCurrentEnemy->unk_E3;
        g_BattleEffects[(u8)slot].unk_08 = D_801EB638[(unit - 3) * 0x118];
    }
}
#else
INCLUDE_ASM(func_800AB910);
#endif
