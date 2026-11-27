#include "area008_13.h"

MATCH void func_801F3C2C(void) {
    Actor* scratch;
    char*  buf;

    Menu_DrawHeaderBar(120, 56, 70, 20, 1u);

    scratch = (Actor*)WORLD00_AREA008_SCRATCH_PTR;
    buf     = (char*)g_UITextFormatBuffer;
    TEXT_Format(buf, WORLD00_AREA008_D_801F2C04, scratch->tint.steps.delta.g, (scratch->tint.steps.delta.r * 100) / 30);

    UI_TextDrawAscii(0x86, 0x3B, 0, buf);

    buf[0] = STRING_PERIOD;
    buf[1] = STRING_END;

    UI_TextDraw(151, 53, 0, TEXT_LENGTH_MAX, buf);
    UI_TextDraw(151, 57, 0, TEXT_LENGTH_MAX, buf);
}
