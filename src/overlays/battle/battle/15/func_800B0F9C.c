#include "battle_15.h"

/* Draws the dragon gene list: marks the occupied gene rows, draws the panel, then the three visible
 * rows with the gene icon, its name, the AP cost in the affordability color and the cursor box or
 * the party highlight.
 */
/* func_800B0F9C */
MATCH void func_800B0F9C(void) {
    s32 entry;
    u16 line_y;
    s32 line;
    s32 i;
    u8  clut;
    u8  slot_b;
    u8  slot_a;
    u8  slot_c;
    u8  sum;
    u8  step;
    s16 cursor;

    Battle_DrawTitledFrame(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_UIPanelCurrent->unk_08, g_UIPanelCurrent->unk_09, 0);
    for (i = 0; (i & BYTE_MASK) < 6U; i++) {
        D_800B70AC[i & BYTE_MASK] = g_BattleTargetRows[i & BYTE_MASK].gate_03 + 1;
    }
    UI_ListDrawScrollbar(D_800B70AC, ((BattlePanelByteCells*)(void*)g_UIPanelCurrent)->scale, (g_UIPanelCurrent->pos.vx + 0x80), (g_UIPanelCurrent->pos.vy + 0x18), 3,
                         ((BattlePanelByteCells*)(void*)g_UIPanelCurrent)->rows, 0x5C);
    for (i = 0; (i & BYTE_MASK) < 3U; i++) {
        line   = i & BYTE_MASK;
        entry  = (s16)g_UIPanelCurrent->u.battle.row_base + line;
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
        if (g_Game.members[BATTLE_ACTIVE_MEMBER->slot].chr.ap < (sum & BYTE_MASK)) {
            clut = 7;
        }
        TEXT_Format(g_UITextFormatBuffer, D_80096A28, entry + 1);
        line_y = line << 5;
        UI_TextDrawAscii((g_UIPanelCurrent->pos.vx + 4), (g_UIPanelCurrent->pos.vy + (line_y + 0x20)), clut, g_UITextFormatBuffer);
        slot_a = g_BattleTargetRows[(s16)g_UIPanelCurrent->u.battle.row_base + line].gate_03;
        if (slot_a != GAME_NONE) {
            func_800B1DAC((g_UIPanelCurrent->pos.vx + 0x10), (g_UIPanelCurrent->pos.vy + (line_y + 0x18)), slot_a & 0x1F);
            line_y += 0x2D;
            UI_TextDrawString((g_UIPanelCurrent->pos.vx + 16), (g_UIPanelCurrent->pos.vy + line_y), clut, TEXT_LENGTH_MAX,
                              UI_MessageGetText(D_800B4C90[g_BattleTargetRows[(s16)g_UIPanelCurrent->u.battle.row_base + line].gate_03 & 0x1F]));
            TEXT_Format(g_UITextFormatBuffer, D_80096A2C, sum & BYTE_MASK);
            UI_TextDrawGlyphString((g_UIPanelCurrent->pos.vx + 88), (g_UIPanelCurrent->pos.vy + line_y), clut, g_UITextFormatBuffer);
        }
    }
    step = g_Battle.ui_step;
    if ((step == 6) && (g_Battle.ui_mode != 5)) {
        cursor = g_UIPanelCurrent->u.battle.cursor;
        func_800B1F04(((u16)g_UIPanelCurrent->pos.vx + 5) & HALF_MASK, ((u16)g_UIPanelCurrent->pos.vy + (cursor * 32 + 0x18)) & HALF_MASK, 121, 32, 0, step);
    } else {
        cursor = g_UIPanelCurrent->u.battle.cursor;
        UI_CursorDraw((g_UIPanelCurrent->pos.vx + 7) & HALF_MASK, ((u16)g_UIPanelCurrent->pos.vy + 0x20 + cursor * 32) & HALF_MASK, 0);
    }
}
