#include "start_08.h"

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s8  unk_08;
    s8  unk_09;
} __attribute__((packed)) Record10;

typedef struct {
    s32 unk_00;
    s32 unk_04;
    s8  unk_08;
    s8  unk_09;
    s8  unk_0A;
} __attribute__((packed)) Record11;

typedef struct {
    s32 unk_00;
    s8  unk_04;
    s8  unk_05;
} __attribute__((packed)) Record6;

typedef struct {
    s32 unk_00;
    s32 unk_04;
} __attribute__((packed)) Record8;

typedef struct {
    Record10 unk_00;
    u8       pad_0A[6];
    Record11 unk_10;
    u8       pad_1B[5];
    Record11 unk_20;
    u8       pad_2B[5];
    Record6  unk_30;
    u8       pad_36[2];
    Record8  unk_38;
    Record11 unk_40;
    u8       pad_4B[5];
    char*    strings[12];
} WorkFields;

typedef union {
    WorkFields fields;
    s32        words[32];
} WorkArea;

extern Record10 D_801D0DE0;
extern Record11 D_801D0DEC;
extern Record11 D_801D0DF8;
extern Record6  D_801D0E04;
extern Record8  D_801D0E0C;
extern Record11 D_801D0E14;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 49.08%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawOptionRow(s32 x, s32 y, s32 option_index, s32 select_step) {
    WorkArea work;
    s16      tmp0;
    s32      tmp1;
    s32      tmp2;
    LINE_F2* line;
    s32      val1;
    s32      val2;
    s32      val3;
    s32      val4;
    s32      val5;
    s32      val6;

    val2                    = x;
    val1                    = y;
    work.fields.unk_00      = D_801D0DE0;
    work.fields.unk_10      = D_801D0DEC;
    work.fields.unk_20      = D_801D0DF8;
    work.fields.unk_30      = D_801D0E04;
    work.fields.unk_38      = D_801D0E0C;
    work.fields.unk_40      = D_801D0E14;
    work.fields.strings[0]  = (char*)&work.fields.unk_00;
    work.fields.strings[1]  = (char*)&work.fields.unk_10;
    work.fields.strings[2]  = (char*)&work.fields.unk_20;
    work.fields.strings[3]  = (char*)&work.fields.unk_30;
    work.fields.strings[4]  = (char*)&work.fields.unk_38;
    work.fields.strings[5]  = (char*)&work.fields.unk_40;
    work.fields.strings[6]  = (char*)&work.fields.unk_00;
    work.fields.strings[7]  = (char*)&work.fields.unk_10;
    work.fields.strings[8]  = (char*)&work.fields.unk_20;
    work.fields.strings[9]  = (char*)&work.fields.unk_30;
    work.fields.strings[10] = (char*)&work.fields.unk_38;
    work.fields.strings[11] = (char*)&work.fields.unk_40;
    val5                    = val2;
    val4                    = select_step;
    tmp1                    = val4 & BYTE_MASK;
    val6                    = option_index;
    UI_DrawWindow(val5 & HALF_MASK, (val1 - tmp1) & HALF_MASK, 249, (tmp1 * 2) + 11, 0, CHARACTER_BLOCK->window_style);
    val3 = val1;
    if ((val4 & BYTE_MASK) == 3) {
        val6 &= BYTE_MASK;
        UI_DrawText((s16)((val2 + 58) - (strlen(work.fields.strings[val6]) * 4)), (s16)(val1 - 1), 0, 0xFFU,
                    work.fields.strings[val6]);
        if (D_80148652 != 1) {
            Menu_DrawCursorSprite((val2 + 4) & HALF_MASK, val3 & HALF_MASK, 0);
        }
    } else {
        val6 &= BYTE_MASK;
        UI_DrawTextString((s16)((val2 + 58) - (strlen(work.fields.strings[val6]) * 4)), (s16)(val1 + 2), 0, 0xFF,
                          work.fields.strings[val6]);
    }
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    tmp0     = val5 + 0x74;
    line->x1 = tmp0;
    line->x0 = tmp0;
    tmp2     = val4 & BYTE_MASK;
    line->y1 = (s16)(val3 + tmp2 + 9);
    line->y0 = (s16)((val3 + 1) - tmp2);
    setRGB0(line, 128, 128, 128);
    GFX_AddPrim(1U, 0x10U);
}
#else
/* The retail stack work area holds six packed records copied from D_801D0DE0 to D_801D0E14 and a 12-entry string table over them; the packed record types in this file are the blocker. */
INCLUDE_ASM(Menu_DrawOptionRow);
#endif
