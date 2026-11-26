#include "start_08.h"

typedef struct {
    char* text[6];
} ConfigText;

typedef struct {
    Record10   unk_00;
    u8         pad_0A[6];
    Record11   unk_10;
    u8         pad_1B[5];
    Record11   unk_20;
    u8         pad_2B[5];
    Record6    unk_30;
    u8         pad_36[2];
    Record8    unk_38;
    Record11   unk_40;
    u8         pad_4B[5];
    ConfigText chosen;
    ConfigText all;
} ConfigRowLabels;

typedef union {
    ConfigRowLabels fields;
    s32             words[32];
} ConfigRow;

/* Draws one config-menu row: its window, the chosen setting's text, the cursor and a line. */
// clang-format off
MATCH void Menu_DrawConfigRow(x, y, option_index, select_step)
s16 x;
s16 y;
u8 option_index;
s32 select_step;
// clang-format on
{
    ConfigRow work;
    s16       line_x;
    LINE_F2*  line;

    work.fields.unk_00      = D_801D0DE0;
    work.fields.unk_10      = D_801D0DEC;
    work.fields.unk_20      = D_801D0DF8;
    work.fields.unk_30      = D_801D0E04;
    work.fields.unk_38      = D_801D0E0C;
    work.fields.unk_40      = D_801D0E14;
    work.fields.all.text[0] = (char*)&work.fields.unk_00;
    work.fields.all.text[1] = (char*)&work.fields.unk_10;
    work.fields.all.text[2] = (char*)&work.fields.unk_20;
    work.fields.all.text[3] = (char*)&work.fields.unk_30;
    work.fields.all.text[4] = (char*)&work.fields.unk_38;
    work.fields.all.text[5] = (char*)&work.fields.unk_40;
    work.fields.chosen      = work.fields.all;
    UI_WindowDraw(x & HALF_MASK, (y - (select_step & BYTE_MASK)) & HALF_MASK, 249, ((select_step & BYTE_MASK) * 2) + 11, 0, CHARACTER_BLOCK->window_style);
    if ((u8)select_step == 3) {
        UI_TextDraw((s16)(x + 58) - (strlen(work.fields.chosen.text[option_index]) * 4), (s16)(y - 1), 0, TEXT_LENGTH_MAX, work.fields.chosen.text[option_index]);
        if (g_MenuStep.state != 1) {
            UI_CursorDraw((x + 4) & HALF_MASK, y & HALF_MASK, 0);
        }
    } else {
        UI_TextDrawString((s16)(x + 58) - (strlen(work.fields.chosen.text[option_index]) * 4), (s16)(y + 2), 0, TEXT_LENGTH_MAX, work.fields.chosen.text[option_index]);
    }
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    line_x   = x + 0x74;
    line->x1 = line_x;
    setXY0(line, line_x, (s16)(y + 1) - (select_step & BYTE_MASK));
    line->y1 = (s16)(y + (select_step & BYTE_MASK) + 9);
    setRGB0(line, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}
