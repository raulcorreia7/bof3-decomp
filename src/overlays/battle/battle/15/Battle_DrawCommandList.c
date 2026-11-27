#include "battle_15.h"

/* Draws the battle command list: copies the command page, draws up to three lines with the affordability color
 * and the price text, and the cursor box.
 */
/* func_800B1728 */
MATCH void Battle_DrawCommandList(void) {
    s32 entry;
    u16 line_y;
    s32 line;
    s32 i;
    u8  clut;
    u8  slot_b;
    u8  slot_a;
    u8  slot_c;
    u8  sum;

    Battle_DrawTitledFrame(g_UiPanelCurrent->pos.vx, g_UiPanelCurrent->pos.vy, g_UiPanelCurrent->unk_08, g_UiPanelCurrent->unk_09, 1);
    for (i = 0; (i & BYTE_MASK) < 12U; i++) {
        D_800B70B8[i & BYTE_MASK] = D_80145518[i & BYTE_MASK].gate_03 + 1;
    }
    UI_ListDrawScrollbar(D_800B70B8, ((BattlePanelByteCells*)(void*)g_UiPanelCurrent)->scale, (g_UiPanelCurrent->pos.vx + 0x80), (g_UiPanelCurrent->pos.vy + 0x18), 3,
                         ((BattlePanelByteCells*)(void*)g_UiPanelCurrent)->rows, 0x5C);
    for (i = 0; (i & BYTE_MASK) < 3U; i++) {
        line   = i & BYTE_MASK;
        entry  = (s16)g_UiPanelCurrent->u.battle.row_base + line;
        slot_a = D_80145518[entry].gate_03;
        if (slot_a != GAME_NONE) {
            slot_b = D_80145518[entry].slot_01;
            sum    = D_800B4C7C[D_80145518[entry].slot_00];
            if (slot_b != GAME_NONE) {
                sum += D_800B4C7C[slot_b];
            }
            slot_c = D_80145518[entry].slot_02;
            if (slot_c != GAME_NONE) {
                sum += D_800B4C7C[slot_c];
            }
            line_y = line << 5;
            clut   = 0;
            if (g_Game.members[BATTLE_ACTIVE_MEMBER->slot].chr.ap < sum) {
                clut = 7;
            }
            func_800B1DAC((g_UiPanelCurrent->pos.vx + 0x10), (g_UiPanelCurrent->pos.vy + (line_y + 0x18)), slot_a & 0x1F);
            line_y += 0x2D;
            UI_TextDrawString((g_UiPanelCurrent->pos.vx + 16), (g_UiPanelCurrent->pos.vy + line_y), clut, TEXT_LENGTH_MAX,
                              UI_MessageGetText(((u8*)&D_800B4C90)[D_80145518[(s16)g_UiPanelCurrent->u.battle.row_base + line].gate_03 & 0x1F]));
            TEXT_Format(g_UiTextFormatBuffer, D_80096A2C, sum & BYTE_MASK);
            UI_TextDrawGlyphString((g_UiPanelCurrent->pos.vx + 88), (g_UiPanelCurrent->pos.vy + line_y), clut, g_UiTextFormatBuffer);
        }
    }
    if ((g_Battle.ui_step != 6) || (g_Battle.ui_mode != 5)) {
        UI_CursorDraw((g_UiPanelCurrent->pos.vx + 7) & HALF_MASK, ((u16)g_UiPanelCurrent->pos.vy + 0x20 + *(s16*)&g_UiPanelCurrent->u.battle.cursor * 32) & HALF_MASK, 0);
    }
}
