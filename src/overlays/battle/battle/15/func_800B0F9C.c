#include "battle_15.h"

/* Draws the dragon gene list: marks the occupied gene rows, draws the panel, then the three visible
 * rows with the gene icon, its name, the AP cost in the affordability color and the cursor box or
 * the party highlight.
 */
/* func_800B0F9C */
MATCH void func_800B0F9C(void) {
    s32 entry;
    u16 line_y;
    s32 row;
    s32 i;
    u8  clut;
    u8  slot_b;
    u8  slot_a;
    u8  slot_c;
    u8  sum;
    u8  step;
    s16 cursor;

    Battle_DrawTitledFrame((s16)g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_08, g_MenuCurrentPanel->unk_09, 0);
    for (i = 0; (i & BYTE_MASK) < 6U; i++) {
        D_800B70AC[i & BYTE_MASK] = g_BattleTargetRows[i & BYTE_MASK].gate_03 + 1;
    }
    func_801AFA1C(D_800B70AC, ((BattlePanelByteCells*)(void*)g_MenuCurrentPanel)->scale, (g_MenuCurrentPanel->pos.x + 0x80), (g_MenuCurrentPanel->pos.y + 0x18), 3,
                  ((BattlePanelByteCells*)(void*)g_MenuCurrentPanel)->rows, 0x5C);
    for (i = 0; (i & BYTE_MASK) < 3U; i++) {
        row    = i & BYTE_MASK;
        entry  = (s16)g_MenuCurrentPanel->u.battle.row_base + row;
        slot_b = g_BattleTargetRows[entry].slot_01;
        sum    = D_800B4C7C[g_BattleTargetRows[entry].slot_00];
        if (slot_b != GAME_NONE) {
            sum += D_800B4C7C[slot_b];
        }
        slot_c = g_BattleTargetRows[entry].slot_02;
        if (slot_c != GAME_NONE) {
            sum += D_800B4C7C[slot_c];
        }
        clut = 0;
        if (g_Game.members[BATTLE_ACTIVE_ROW->slot].chr.ap < (sum & BYTE_MASK)) {
            clut = 7;
        }
        TEXT_Format(g_UiFormatBuffer, D_80096A28, entry + 1);
        line_y = row << 5;
        UI_DrawAsciiString((g_MenuCurrentPanel->pos.x + 4), (g_MenuCurrentPanel->pos.y + (line_y + 0x20)), clut, g_UiFormatBuffer);
        slot_a = g_BattleTargetRows[(s16)g_MenuCurrentPanel->u.battle.row_base + row].gate_03;
        if (slot_a != GAME_NONE) {
            func_800B1DAC((g_MenuCurrentPanel->pos.x + 0x10), (g_MenuCurrentPanel->pos.y + (line_y + 0x18)), slot_a & 0x1F);
            line_y += 0x2D;
            UI_DrawTextString((g_MenuCurrentPanel->pos.x + 16), (g_MenuCurrentPanel->pos.y + line_y), clut, 255,
                              Message_GetText(D_800B4C90[g_BattleTargetRows[(s16)g_MenuCurrentPanel->u.battle.row_base + row].gate_03 & 0x1F]));
            TEXT_Format(g_UiFormatBuffer, D_80096A2C, sum & BYTE_MASK);
            UI_DrawGlyphString((g_MenuCurrentPanel->pos.x + 88), (g_MenuCurrentPanel->pos.y + line_y), clut, g_UiFormatBuffer);
        }
    }
    step = g_Battle.ui_step;
    if ((step == 6) && (g_Battle.ui_state != 5)) {
        cursor = g_MenuCurrentPanel->u.battle.cursor;
        func_800B1F04((g_MenuCurrentPanel->pos.x + 5) & HALF_MASK, (g_MenuCurrentPanel->pos.y + (cursor * 32 + 0x18)) & HALF_MASK, 121, 32, 0, step);
    } else {
        cursor = g_MenuCurrentPanel->u.battle.cursor;
        Menu_DrawCursorSprite((g_MenuCurrentPanel->pos.x + 7) & HALF_MASK, (g_MenuCurrentPanel->pos.y + 0x20 + cursor * 32) & HALF_MASK, 0);
    }
}
