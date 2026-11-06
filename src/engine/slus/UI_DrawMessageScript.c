#include "engine/slus/slus.h"

/* The window state block whose flags word sits at g_UiWindowChannel; the palette and
 * glyph deltas follow, then the x/y cursor the script advances. */
typedef struct GameUITextState {
    volatile u16 flags; /* 0x00 */
    u8           unk_02[0x12];
    u8           palette; /* 0x14 */
    u8           unk_15;  /* 0x15 */
    s8           dx;      /* 0x16 */
    s8           dy;      /* 0x17 */
    u16          x;       /* 0x18 */
    u16          y;       /* 0x1A */
} GameUITextState;

/* walks the message script at D_801490AC, drawing each glyph
 * through func_8014F800 until D_801490B9 characters were drawn.
 */
MATCH void UI_DrawMessageScript(void) {
    u8*              p;
    u8*              saved;
    u8*              base;
    u16*             cursor;
    GameUITextState* state;
    u8               flags;
    u8               count;
    u8               color;
    u8               drawn;

    flags             = 0;
    saved             = NULL;
    count             = 0;
    drawn             = 0;
    base              = (u8*)&D_801490AC;
    p                 = *(u8**)base;
    D_801490BC.text_x = D_801490BC.origin_x;
    D_801490BC.text_y = D_801490BC.origin_y;
    color             = 0;
    if (D_801490B9 != 0) {
        cursor = (u16*)(base + 0x10);
        state  = (GameUITextState*)(base - 8);
        do {
            if (flags & 1) {
                if (--count == 0) {
                    p = saved + 1;
                    flags &= 0xFE;
                }
            }
            switch (*p) {
                case STRING_SE:
                case STRING_BOX:
                case STRING_STYLE:
                case STRING_CHOICE:
                    p++;
                    break;
                case STRING_END:
                    if (flags & 1) {
                        p = saved++;
                        flags &= 0xFE;
                    }
                    break;
                case STRING_NEWLINE:
                    cursor[0] = cursor[2];
                    cursor[1] += 0xE;
                    break;
                case STRING_VAR:
                    flags |= 1;
                    p++;
                    saved = p;
                    count = 33;
                    p     = (u8*)&D_801490D7 + (*p << 5);
                    break;
                case STRING_GOTO:
                    flags |= 1;
                    saved = p;
                    count = 6;
                    p     = (u8*)&D_80144967 + g_CharSlot[D_80145F09] * 0xA4;
                    break;
                case STRING_INSERT:
                    flags |= 1;
                    p++;
                    saved = p;
                    count = 6;
                    p     = (u8*)&D_80144967 + *p * 0xA4;
                    break;
                case STRING_COLOR:
                    p++;
                    color = *p;
                    break;
                case STRING_NOCOLOR:
                    color = 0;
                    break;
                case STRING_LINK:
                    flags |= 1;
                    p++;
                    saved = p;
                    count = 17;
                    {
                        u8 index;

                        index = *p;
                        p     = (u8*)(D_80010004 + SLUS_LOAD_ADDRESS);
                        p += *(u16*)((index << 1) + (u32)p);
                    }
                    break;
                case STRING_PAGE:
                case STRING_NOP:
                case STRING_GAP:
                case STRING_STYLE_ALT:
                case STRING_WAIT:
                case STRING_BOXEND:
                    break;
                case STRING_OFFSET:
                    flags |= 0x20;
                    break;
                case STRING_CURSOR:
                    flags &= 0xDF;
                    break;
                default:
                    if (*p == STRING_BACKSPACE && cursor[0] == cursor[2]) {
                        cursor[0] -= 8;
                    }
                    /* The flagged path offsets the state cursor by its deltas; the
                     * other reads the cursor signed and its palette from the byte
                     * before it. */
                    if (flags & 0x20) {
                        if (state->flags & FRONTEND_FLAG_REQUEST_PENDING) {
                            UI_DrawGlyph(color, p);
                        } else {
                            UI_DrawText(state->x + state->dx, state->y + state->dy,
                                        (color + state->palette * 0x10) & BYTE_MASK, 1, p);
                        }
                    } else {
                        UI_DrawText(((s16*)cursor)[0], ((s16*)cursor)[1],
                                    (color + ((u8*)cursor)[-4] * 0x10) & BYTE_MASK, 1, p);
                    }
                    if (*p == STRING_SKIP || *p == STRING_SKIP_ALT || *p == STRING_NUM) {
                        p++;
                    }
                    drawn++;
                    cursor[0] += 8;
                    break;
            }
            p++;
        } while (D_801490B9 != (drawn & BYTE_MASK));
    }
}
