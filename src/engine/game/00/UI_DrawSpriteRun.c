#include "game_00.h"

MATCH void UI_DrawSpriteRun(s16 base_x, s16 base_y, const u8* record_table, u8 flags) {
    s16       x;
    s16       y;
    u16       shift;
    u8        id;
    const u8* rec;
    u8        terminator;
    int       tpage;

    tpage = 832;
    if (!(flags & 0x1)) {
        tpage = 896;
    }
    shift = GetTPage(0, 0, tpage, 256);
    GFX_AddDrawMode(shift);

    id = record_table[2];
    if (id == GAME_NONE) {
        return;
    }
    terminator = 0xFF;
    rec        = record_table + 2;
    for (;;) {
        shift = 0x15;
        x     = base_x + ((record_table[0] << 24) >> shift);
        y     = base_y + ((rec[-1] << 24) >> shift);
        UI_DrawSprite(x, y, id, flags);
        rec += 3;
        id = rec[0];
        record_table += 3;
        if (id == terminator) {
            break;
        }
    }
}
