#include "battle_03.h"

/* The actor record the panel rows are measured against. */
typedef struct BattleActor {
    u8  pad_00[8];
    u8  unk_08;
    u8  pad_09[0x25];
    u16 unk_2E;
    u16 unk_30;
    u16 unk_32;
} BattleActor;

/* The panel row the battle state is written into. */
typedef struct BattlePanelState {
    u8    index_00;
    u8    pad_01;
    s16   unk_02;
    s16   unk_04;
    u16   unk_06;
    void* state_08;
    void* work_0C;
} BattlePanelState;

/* Advances the battle actor: picks the next actor from the turn
 * table, writes its panel rows and copies the actor state into the battle
 * state block.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D2B58(void) {
    BattleActor*      actor;
    BattlePanelState* row;
    u8*               table;
    u8*               state;
    u8                kind;
    u8                index;
    u32               offset;
    s32               state_offset;
    u8                value;
    u16               depth;
    u8*               cursor;
    u8*               fa8;
    u8*               fa8_118;
    u8*               fa8_88;
    u8*               eb3dc;
    u8*               eb3dc_2f4;
    BattlePanelState* row1;
    BattlePanelState* row2;

    cursor    = (u8*)&g_Battle.turn_cursor;
    fa8       = D_80145FA8;
    fa8_118   = D_80145FA8 - 0x118;
    fa8_88    = D_80145FA8 - 0x88;
    eb3dc     = (u8*)&D_801EB3DC;
    eb3dc_2f4 = (u8*)&D_801EB3DC + 0x2F4;
    row1      = (BattlePanelState*)(cursor + 0x52);
    row2      = (BattlePanelState*)(cursor + 0x62);
    if (cursor[0] < (u8)g_Battle.turn_count) {
        table = g_Battle.turn_order;
        do {
            value = table[cursor[0] & BYTE_MASK];
            kind  = value & BYTE_MASK;
            if (kind == GAME_NONE) {
                cursor[0] += 1;
                if (cursor[0] >= cursor[1]) {
                    goto done; /* leaves the loop for the final stores */
                }
                continue;
            }
            index = value;
            if (kind < 3U) {
                func_800AB0B8(kind, cursor[0], &g_Battle.turn_cursor);
            } else {
                func_801E25E0((index - 3) & BYTE_MASK);
            }
            row           = row1;
            row->index_00 = index;
            if (kind < 3U) {
                actor         = (BattleActor*)D_8014637C;
                offset        = kind * BATTLE_PARTY_STRIDE;
                row->state_08 = (void*)(fa8_118 + offset);
                row->work_0C  = (void*)(fa8 + offset);
                row->unk_02   = (s16)(actor->unk_2E + (s8)g_BattlePanelOffsets[(actor->unk_08 * 2) + (g_Game.members[kind].chr.character_id * 8)]);
                row->unk_04   = (s16)(actor->unk_30 + (s8)(g_BattlePanelOffsets + 1)[(actor->unk_08 * 2) + (g_Game.members[kind].chr.character_id * 8)]);
                depth         = actor->unk_32;
                state         = fa8_88 + offset;
            } else {
                actor         = (BattleActor*)D_8014637C;
                state_offset  = kind * 0x118;
                row->work_0C  = (void*)(eb3dc + state_offset);
                row->state_08 = (void*)(eb3dc - 0xF4 + state_offset);
                row->unk_02   = (s16)(actor->unk_2E + ENEMY_COMBATANT(kind).panel_offset_x);
                row->unk_04   = (s16)(actor->unk_30 + ENEMY_COMBATANT(kind).panel_offset_y);
                depth         = actor->unk_32;
                state         = eb3dc_2f4 + (kind - 3) * 0x118;
            }
            row->unk_06                = depth;
            *(s32*)D_801EC308          = *(s32*)state;
            *(s32*)(D_801EC308 + 4)    = *(s32*)(state + 4);
            *(s32*)(D_801EC308 + 8)    = *(s32*)(state + 8);
            *(s32*)(D_801EC308 + 0xC)  = *(s32*)(state + 0xC);
            *(s32*)(D_801EC308 + 0x10) = *(s32*)(state + 0x10);
            *(s32*)(D_801EC308 + 0x14) = *(s32*)(state + 0x14);
            *(s32*)(D_801EC308 + 0x18) = *(s32*)(state + 0x18);
            *(s32*)(D_801EC308 + 0x1C) = *(s32*)(state + 0x1C);
            row                        = row2;
            if (cursor[0] < 3U) {
                actor         = (BattleActor*)g_Battle.selected_actor;
                offset        = cursor[0] * BATTLE_PARTY_STRIDE;
                row->state_08 = (void*)(fa8_118 + offset);
                row->work_0C  = (void*)(fa8 + offset);
                row->unk_02   = (s16)(actor->unk_2E + (s8)g_BattlePanelOffsets[(actor->unk_08 * 2) + (g_Game.members[cursor[0]].chr.character_id * 8)]);
                value         = (g_BattlePanelOffsets + 1)[(actor->unk_08 * 2) + (g_Game.members[cursor[0]].chr.character_id * 8)];
            } else {
                state_offset  = cursor[0] * 0x118;
                row->state_08 = (void*)(g_BattleEnemies + state_offset);
                row->work_0C  = (void*)(D_801EB3DC + state_offset);
                row->unk_02   = (s16)(actor->unk_2E + ENEMY_COMBATANT(cursor[0]).panel_offset_x);
                value         = ENEMY_COMBATANT(cursor[0]).panel_offset_y;
            }
            row->unk_04 = (s16)(actor->unk_30 + (s8)value);
            row->unk_06 = actor->unk_32;
            g_Battle.phase.sub_step += 1;
            cursor[0] += 1;
            return;
        } while (1);
    }
done:
    g_Battle.phase.mode = BATTLE_MODE_ROUND_END;
    g_Battle.phase.step = 0;
}
#else
INCLUDE_ASM(func_801D2B58);
#endif
