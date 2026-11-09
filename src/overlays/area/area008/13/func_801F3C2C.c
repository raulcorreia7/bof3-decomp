#include "area008_13.h"

MATCH void func_801F3C2C(void) {
    Actor* scratch;
    char*  buf;

    Menu_DrawHeaderBar(0x78, 0x38, 0x46, 0x14, 1u);

    scratch = (Actor*)WORLD00_AREA008_SCRATCH_PTR;
    buf     = (char*)g_UiFormatBuffer;
    TEXT_Format(buf, WORLD00_AREA008_D_801F2C04, scratch->tint.signed_bytes.unk_5E, (scratch->tint.signed_bytes.unk_5D * 100) / 30);

    UI_DrawAsciiString(0x86, 0x3B, 0, buf);

    buf[0] = STRING_PERIOD;
    buf[1] = STRING_END;

    UI_DrawText(0x97, 0x35, 0, 0xFFu, buf);
    UI_DrawText(0x97, 0x39, 0, 0xFFu, buf);
}
