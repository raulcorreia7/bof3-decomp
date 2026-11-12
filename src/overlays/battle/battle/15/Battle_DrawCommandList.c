#include "battle_15.h"

/* Draws the battle command list: copies the command page, draws up to three rows with the affordability color
 * and the price text, and the cursor box.
 */
/* func_800B1728 */
MATCH void Battle_DrawCommandList(void) {
    s32 entry;
    u16 line_y;
    s32 row;
    s32 i;
    u8  clut;
    u8  slot_b;
    u8  slot_a;
    u8  slot_c;
    u8  sum;

    Battle_DrawTitledFrame((s16)g_MenuCurrentPanel->pos.x, g_MenuCurrentPanel->pos.y, g_MenuCurrentPanel->unk_08, g_MenuCurrentPanel->unk_09, 1);
    for (i = 0; (i & BYTE_MASK) < 12U; i++) {
        D_800B70B8[i & BYTE_MASK] = D_80145518[i & BYTE_MASK].gate_03 + 1;
    }
    func_801AFA1C(D_800B70B8, ((BattlePanelByteCells*)(void*)g_MenuCurrentPanel)->scale, (g_MenuCurrentPanel->pos.x + 0x80), (g_MenuCurrentPanel->pos.y + 0x18), 3,
                  ((BattlePanelByteCells*)(void*)g_MenuCurrentPanel)->rows, 0x5C);
    for (i = 0; (i & BYTE_MASK) < 3U; i++) {
        row    = i & BYTE_MASK;
        entry  = (s16)g_MenuCurrentPanel->u.battle.row_base + row;
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
            line_y = row << 5;
            clut   = 0;
            if (g_Game.members[BATTLE_ACTIVE_ROW->slot].chr.ap < sum) {
                clut = 7;
            }
            func_800B1DAC((g_MenuCurrentPanel->pos.x + 0x10), (g_MenuCurrentPanel->pos.y + (line_y + 0x18)), slot_a & 0x1F);
            line_y += 0x2D;
            UI_DrawTextString((g_MenuCurrentPanel->pos.x + 16), (g_MenuCurrentPanel->pos.y + line_y), clut, 255,
                              Message_GetText(((u8*)&D_800B4C90)[D_80145518[(s16)g_MenuCurrentPanel->u.battle.row_base + row].gate_03 & 0x1F]));
            TEXT_Format(g_UiFormatBuffer, D_80096A2C, sum & BYTE_MASK);
            UI_DrawGlyphString((g_MenuCurrentPanel->pos.x + 88), (g_MenuCurrentPanel->pos.y + line_y), clut, g_UiFormatBuffer);
        }
    }
    if ((*(u8*)&g_Battle.ui_step != 6) || (*(u8*)&g_Battle.ui_state != 5)) {
        Menu_DrawCursorSprite((g_MenuCurrentPanel->pos.x + 7) & HALF_MASK, (g_MenuCurrentPanel->pos.y + 0x20 + *(s16*)&g_MenuCurrentPanel->u.battle.cursor * 32) & HALF_MASK, 0);
    }
}
