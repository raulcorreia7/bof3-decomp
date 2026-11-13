#include "game_00.h"

MATCH void func_801999F8(MenuPanelTask* task) {
    u8   row;
    u8   count;
    u8   byte;
    s32  visible;
    u8   i;
    u8   shade;
    u8   flag;
    s16  y;
    u8   value;
    s32  flip;
    u8   flip8;
    s32  slot;
    u8** slotp;
    u8*  src;
    u8*  dst;
    u16  field;
    s32  offset;

    UI_DrawWindow((u16)(task->pos.x + 3), (u16)(task->pos.y + 3), 153, 154, task->unk_09, g_WindowStyle);
    value = func_801AFD10(&task->unk_0B, &row, &count, (u8*)&task->u.list.scroll) & BYTE_MASK;
    y     = task->pos.y + (s8)row;
    src   = D_801C893C[task->unk_0A] + value;
    dst   = D_801C8950[task->unk_0A] + value;
    for (i = 0; i < count + 9; i++) {
        byte = *src;
        if (byte != 0) {
            flag = 0;
            if (task->unk_09 != 0 || (func_801AF494(task->unk_08, g_CharSlot[g_PartyFieldOrder[D_80148656]], task->unk_0A, byte) & BYTE_MASK) == 0) {
                flag = 1;
            }
            visible = flag;
            flip    = (-visible) & 0x7;
            slot    = task->unk_0B + i;
            if (slot == task->flags) {
                flip = 2;
            }
            flip8 = flip;
            shade = 1;
            if (task->unk_0A != 4) {
                shade = *dst;
            }
            if (slot == task->flags || slot == task->unk_0C) {
                if (flip8 != 7) {
                    func_801AF800((task->pos.x + 7), (s16)(y + 0x1A), 7, task->unk_0A, *src, shade, 1);
                }
                func_801AF800((task->pos.x + 7), (s16)(y + 0x18), flip8, task->unk_0A, *src, shade, visible);
            } else {
                func_801AF800((task->pos.x + 7), (s16)(y + 0x1A), flip8, task->unk_0A, *src, shade, visible);
            }
        }
        src++;
        dst++;
        y += 13;
    }
    /* FAKE: retail reads g_WindowStyle as s8. */
    UI_DrawWindow((u16)(task->pos.x + 3), (u16)(task->pos.y + 3), 153, 20, task->unk_09, *(u8*)((s8*)&g_WindowStyle));
    UI_DrawWindow((u16)(task->pos.x + 3), (u16)(task->pos.y + 146), 153, 8, task->unk_09, *(u8*)((s8*)&g_WindowStyle));
    slotp  = &D_801C7C5C[task->unk_0A];
    value  = Game_ReadCommand(*slotp) & BYTE_MASK;
    offset = (value * 4) - 0x4E;
    UI_DrawText((task->pos.x - offset), (task->pos.y + 0x7), -(task->unk_09 != 0) & 7, 16, *slotp);
    TEXT_Format(g_UiFormatBuffer, D_80195858, Item_CountHeld(task->unk_0A) & BYTE_MASK, (task->unk_0A != 4) ? 0x80 : 0x20);
    UI_DrawGlyphString((task->pos.x + 85), (task->pos.y + 146), -(task->unk_09 != 0) & 0x7, g_UiFormatBuffer);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & 0x2) != 0 ? s_MenuLine1FlagRun : s_MenuLine1Run, 1);
    UI_DrawSpriteRun(task->pos.x, task->pos.y, (task->u.list.tabs & 0x1) != 0 ? s_MenuLine2FlagRun : s_MenuLine2Run, 1);
    field = task->u.list.tabs;
    if ((field & 0xF0) == 0) {
        task->u.list.tabs = 0;
    } else {
        task->u.list.tabs = field - 0x10;
    }
    for (i = 0; i < 10; i++) {
        UI_DrawSprite((task->pos.x + (i + 5) * 8), task->pos.y, 1, 1);
    }
    for (i = 0; i < 15; i++) {
        UI_DrawSprite(task->pos.x, (task->pos.y + (i + 3) * 8), 4, 1);
    }
    UI_DrawSprite((task->pos.x + 144), (task->pos.y + 24), 0x16, 1);
    for (i = 0; i < 12; i++) {
        UI_DrawSprite((task->pos.x + 144), (task->pos.y + (i + 5) * 8), 0x17, 1);
    }
    UI_DrawSprite((task->pos.x + 144), (task->pos.y + 136), 0x18, 1);
    UI_DrawSprite(task->pos.x, (task->pos.y + 144), 0x19, 1);
    for (i = 0; i < 9; i++) {
        UI_DrawSprite((task->pos.x + (i + 1) * 8), (task->pos.y + 144), 0x1A, 1);
    }
    UI_DrawSprite((task->pos.x + 80), (task->pos.y + 144), 0x1B, 1);
    for (i = 0; i < 6; i++) {
        UI_DrawSprite((task->pos.x + (i + 11) * 8), (task->pos.y + 144), 0x1C, 1);
    }
    UI_DrawSprite((task->pos.x + 136), (task->pos.y + 144), 0x1D, 1);
    func_801AFA1C(D_801C893C[task->unk_0A], task->unk_0B, (task->pos.x + 0x90), (task->pos.y + 0x18), 9, (task->unk_0A != 4) ? 0x80 : 0x20, 0x74);
}
