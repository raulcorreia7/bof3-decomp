#include "battle_03.h"

extern s8 D_801EAEA4[];

/* Reserves the battle stage's selection panel entries and fills one ring record per active battler
 * from its stage tables.
 */
/* func_801D1828 */
MATCH void Battle_ReserveStagePanels(void) {
    u8* group;
    u8  slot;
    u8  battler;
    u8  first;
    u8* counter;
    s32 index;
    s16 panel_x;
    s16 panel_y;

    D_801EBF04               = 0;
    D_801EC328               = 0;
    slot                     = Menu_ArmPanelTask(0x14, 3) & BYTE_MASK;
    D_80148332[slot].mode_00 = 7;
    D_80148332[slot].x_02    = 0x14;
    D_80148332[slot].unk_01  = 0;
    D_80148332[slot].y_04    = -0x16;
    group                    = &g_BattleSurprise;
    if (*group == 1) {
        BattleStageSelectionRingRecord(2, 0x30, Resource_GetText(BATTLE_TEXT_INITIATIVE_PARTY));
    }
    if (*group == 2) {
        BattleStageSelectionRingRecord(2, 0x30, Resource_GetText(BATTLE_TEXT_INITIATIVE_OPPONENT));
    }
    for (battler = 0; battler < BATTLE_PARTY_SLOT_COUNT; battler++) {
        if (ACTOR_IN_USE(g_BattlePartyBattlers[battler])) {
            Menu_ArmPanelTask((battler + 0xD) & BYTE_MASK, 3);
            D_80148332[battler + 0xD].mode_00 = 5;
            D_80148332[0xD + battler].unk_01  = 0;
            /* FAKE: barrier keeps the row-byte load after the two panel byte stores. */
            MATCH_BARRIER();
            first   = g_BattlePartyBattlers[battler].word_08.byte.facing_08;
            index   = first * 2 + D_80145F09[battler][0] * 8;
            panel_x = g_BattlePartyBattlers[battler].unk_2E.half + (s8)g_BattlePanelOffsets[index];
            panel_x = (s8)D_801EAEA4[(g_BattleScrollDir & 0xFE) ^ 2] + panel_x;
            D_80148332[battler + 0xD].x_02 = panel_x;
            /* The y lookup reloads the row bytes; the x store may have changed them. */
            index   = g_BattlePartyBattlers[battler].word_08.byte.facing_08 * 2 + D_80145F09[battler][0] * 8;
            panel_y = g_BattlePartyBattlers[battler].unk_30.half + (s8)(g_BattlePanelOffsets + 1)[index] + 0xC;
            D_80148332[battler + 0xD].battler_08 = battler;
            D_80148332[battler + 0xD].unk_06     = 0;
            D_80148332[battler + 0xD].unk_07     = 0;
            D_80148332[battler + 0xD].y_04       = panel_y;
        }
    }
    func_801D9304(0);
    func_800AC964();
    counter = &g_BattleSubStep;
    *counter += 1;
}
